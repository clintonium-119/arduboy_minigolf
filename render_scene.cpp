#include "game.hpp"

#define PERFDOOM 0

static constexpr uint8_t MAX_CLIP_FACES = 32;

static constexpr int16_t ZNEAR = 256 * 0.5;  // near

static array<uint8_t, MAX_FACES> face_order;
static array<uint8_t, MAX_CLIP_FACES * 4> clip_faces;
static array<dvec2, MAX_VERTS> vs;

// camera look angle (roll not supported)
uint8_t yaw = 0;
uint8_t pitch = 0;

// camera position
int16_t cx = 0;
int16_t cy = 256 * 1;
int16_t cz = -256 * 8;

static dvec2 interpz(dvec2 a, int16_t az, dvec2 b, int16_t bz)
{
    dvec2 r;
    r.x = interp(az, ZNEAR, bz, a.x, b.x);
    r.y = interp(az, ZNEAR, bz, a.y, b.y);
    return r;
}

void render_scene(
    int8_t const* verts,
    uint8_t num_verts,
    uint8_t const* faces,
    uint8_t num_faces)
{

    pitch = (uint8_t)tclamp<int8_t>(int8_t(pitch), -64, 64);

    mat3 m;
    rotation(m, yaw, pitch);

#if PERFDOOM
    for(int i = 0; i < PERFDOOM; ++i) {
#endif

    uint8_t nv = 0;
    uint8_t nf = 0;
    uint8_t nclipf = 0;

    // translate and rotate vertices
    for(uint8_t j = nv = 0; nv < num_verts; ++nv, j += 3)
    {
        dvec3 dv;
        dv.x = (int8_t)pgm_read_byte(&verts[j + 0]) << 8;
        dv.y = (int8_t)pgm_read_byte(&verts[j + 1]) << 8;
        dv.z = (int8_t)pgm_read_byte(&verts[j + 2]) << 8;

        // translate
        dv.x -= cx;
        dv.y -= cy;
        dv.z -= cz;

        // vertex distance
        fd.vdist[nv] = tabs(dv.x) + tabs(dv.y) + tabs(dv.z);

        // rotate
        dv = matvec(m, dv);

        // save vertex
        vs[nv] = { dv.x, dv.y };
        fd.vz[nv] = dv.z;
    }

    // assemble faces and clip them to near plane
    for(uint8_t i = 0; i < num_faces; ++i)
    {
        uint8_t j = i << 2;
        uint8_t i0 = pgm_read_byte(&faces[j + 0]);
        uint8_t i1 = pgm_read_byte(&faces[j + 1]);
        uint8_t i2 = pgm_read_byte(&faces[j + 2]);
        int16_t z0 = fd.vz[i0];
        int16_t z1 = fd.vz[i1];
        int16_t z2 = fd.vz[i2];

        uint8_t behind = 0;
        if(z0 < ZNEAR) behind |= 1;
        if(z1 < ZNEAR) behind |= 2;
        if(z2 < ZNEAR) behind |= 4;

        // discard if fully behind near plane
        if(behind == 7) continue;

        // face distance
        uint16_t fdist = fd.vdist[i0] + fd.vdist[i1] + fd.vdist[i2];

        // clip: exactly two vertices behind near plane
        if((behind & (behind - 1)) != 0)
        {
            dvec2 newv0, newv1;
            int16_t splitz;
            uint8_t ibase;

            // adjust the two near vertices.
            if(!(behind & 1))
            {
                ibase = i0;
                splitz = z0;
                newv0 = interpz(vs[i1], z1, vs[i0], z0);
                newv1 = interpz(vs[i2], z2, vs[i0], z0);
            }
            else if(!(behind & 2))
            {
                ibase = i1;
                splitz = z1;
                newv0 = interpz(vs[i0], z0, vs[i1], z1);
                newv1 = interpz(vs[i2], z2, vs[i1], z1);
            }
            else
            {
                ibase = i2;
                splitz = z2;
                newv0 = interpz(vs[i0], z0, vs[i2], z2);
                newv1 = interpz(vs[i1], z1, vs[i2], z2);
            }

            // add vertices
            vs[nv] = newv0;
            fd.vz[nv] = ZNEAR;
            ++nv;
            vs[nv] = newv1;
            fd.vz[nv] = ZNEAR;
            ++nv;

            // add clip face
            face_order[nf] = MAX_FACES + (nclipf >> 2);
            fd.fdist[nf] = fdist;
            ++nf;
            clip_faces[nclipf + 0] = ibase;
            clip_faces[nclipf + 1] = nv - 1;
            clip_faces[nclipf + 2] = nv - 2;
            clip_faces[nclipf + 3] = pgm_read_byte(&faces[j + 3]);
            nclipf += 4;

            continue;
        }

        // clip: exactly one vertex behind near plane
        else if(behind != 0)
        {
            uint8_t ia, ib, ic; // winding order indices
            dvec2 newv0, newv1;
            int16_t splitz0;
            int16_t splitz1;
            if(behind & 1)
            {
                ia = i0, ib = i1, ic = i2;
                newv0 = interpz(vs[i0], z0, vs[i1], z1);
                newv1 = interpz(vs[i0], z0, vs[i2], z2);
                splitz0 = z1;
                splitz1 = z2;
            }
            else if(behind & 2)
            {
                ia = i1, ib = i2, ic = i0;
                newv0 = interpz(vs[i1], z1, vs[i2], z2);
                newv1 = interpz(vs[i1], z1, vs[i0], z0);
                splitz0 = z2;
                splitz1 = z0;
            }
            else
            {
                ia = i2, ib = i0, ic = i1;
                newv0 = interpz(vs[i2], z2, vs[i0], z0);
                newv1 = interpz(vs[i2], z2, vs[i1], z1);
                splitz0 = z0;
                splitz1 = z1;
            }

            // add new vertices
            vs[nv] = newv0;
            fd.vz[nv] = ZNEAR;
            ++nv;
            vs[nv] = newv1;
            fd.vz[nv] = ZNEAR;
            ++nv;

            face_order[nf] = MAX_FACES + (nclipf >> 2);
            fd.fdist[nf] = fdist;
            ++nf;
            face_order[nf] = MAX_FACES + (nclipf >> 2) + 1;
            fd.fdist[nf] = fdist;
            ++nf;

            uint8_t pat = pgm_read_byte(&faces[j + 3]);

            // TODO: backface culling issue here!

            clip_faces[nclipf + 0] = nv - 2;
            clip_faces[nclipf + 1] = ib;
            clip_faces[nclipf + 2] = ic;
            clip_faces[nclipf + 3] = pat;
            nclipf += 4;

            clip_faces[nclipf + 0] = nv - 2;
            clip_faces[nclipf + 1] = ic;
            clip_faces[nclipf + 2] = nv - 1;
            clip_faces[nclipf + 3] = pat;
            nclipf += 4;

            continue;
        }

        face_order[nf] = i;
        fd.fdist[nf] = fdist;
        ++nf;
    }

    // project vertices
    for(uint8_t i = 0; i < nv; ++i)
    {
        dvec3 dv = { vs[i].x, vs[i].y, fd.vz[i] };

        // multiply x and y by 4/z
        {
            uint16_t zs = uint16_t(dv.z) >> 4;
            uint16_t f;
            if(zs >= 256)
                f = inv8(uint8_t(uint16_t(dv.z) >> 8)) >> 6;
            else
                f = inv8((uint8_t)zs) >> 2;
            int32_t nx = int32_t(f) * dv.x;
            int32_t ny = int32_t(f) * dv.y;
            nx = tclamp<int32_t>(nx, (int32_t)INT16_MIN * 240, (int32_t)INT16_MAX * 240);
            ny = tclamp<int32_t>(ny, (int32_t)INT16_MIN * 240, (int32_t)INT16_MAX * 240);
            dv.x = int16_t(nx >> 8);
            dv.y = int16_t(ny >> 8);
        }

        // center in framebuffer
        dv.x += (FBW / 2 * 16);
        dv.y = (FBH / 2 * 16) - dv.y;

        // save vertex
        vs[i] = { dv.x, dv.y };
    }

    // order faces
#if 1
    {
        uint8_t i = 1;
        while(i < nf)
        {
            int16_t d = fd.fdist[i];
            uint8_t f = face_order[i];
            uint8_t j = i;
            while(j > 0 && fd.fdist[j - 1] < d)
            {
                fd.fdist[j] = fd.fdist[j - 1];
                face_order[j] = face_order[j - 1];
                j -= 1;
            }
            fd.fdist[j] = d;
            face_order[j] = f;
            i += 1;
        }
    }
#endif

    // finally, render
    clear_buf(); // buf mem was used during setup
    for(uint8_t i = 0; i < nf; ++i)
    {
        uint8_t t = face_order[i];
        uint8_t i0, i1, i2, pt;
        uint16_t j = uint16_t(t) * 4;
        if(t < MAX_FACES)
        {
            i0 = pgm_read_byte(&faces[j + 0]);
            i1 = pgm_read_byte(&faces[j + 1]);
            i2 = pgm_read_byte(&faces[j + 2]);
            pt = pgm_read_byte(&faces[j + 3]);
        }
        else
        {
            i0 = clip_faces[j - MAX_FACES * 4 + 0];
            i1 = clip_faces[j - MAX_FACES * 4 + 1];
            i2 = clip_faces[j - MAX_FACES * 4 + 2];
            pt = clip_faces[j - MAX_FACES * 4 + 3];
        }
        draw_tri(vs[i0], vs[i1], vs[i2], pt);
    }

#if PERFDOOM
    }
#endif
}
