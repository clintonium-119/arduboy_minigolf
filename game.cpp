#include "game.hpp"

static constexpr uint8_t STARTING_LEVEL = 0;

// alternative yaw for non camera uses
// (like aiming, tracking ball velocity)
uint16_t yaw_aim;

uint8_t power_aim;
static constexpr uint8_t MIN_POWER = 2;
static constexpr uint8_t MAX_POWER = 128;

static dvec3 prev_ball;

static uint8_t practice;
static uint8_t aim_wait;

st state;
uint8_t nframe;
static uint16_t yaw_level;

static uint8_t graphic_offset;
static constexpr uint8_t GRAPHIC_OFFSET_MAX = 32;

static uint8_t prev_btns;

uint8_t shots[18];

static void draw_nframe_progress(uint8_t oy, uint8_t n)
{
    constexpr uint8_t R = 9;
    int8_t fs = 0;
    int8_t fc = 127;
    dvec2 vc;
    vc.x = 117 * 16;
    vc.y = oy * 16;
    dvec2 v0;
    v0.x = vc.x + R * 16;
    v0.y = vc.y;
    draw_ball_filled(vc, (R + 1) * 16, 0xffff);
    draw_ball_filled(vc, (R - 1) * 16, 0x0000);
    for(uint8_t j = 1; j <= n; ++j)
    {
        dvec2 v1;
        v1.x = vc.x + div16s(fmuls(fcos(j * 8), R));
        v1.y = vc.y + div16s(fmuls(fsin(j * 8), R));
        draw_tri(vc, v0, v1, 4);
        v0 = v1;
    }
}

static void reset_ball()
{
    memcpy_P(&ball, &current_level->ball_pos, sizeof(ball));
    ball_vel = {};
    ball_vel_ang = {};
}

void set_level(uint8_t index)
{
    leveli = index;
    current_level = &LEVELS[index];
    reset_ball();
    nframe = 0;
    yaw_level = 0;
    yaw_aim = 0;
    power_aim = 32;
    state = st::LEVEL;
}

static void reset_to_title()
{
    set_level(0);
    for(auto& s : shots) s = 0;
    state = st::TITLE;
    cam = { 3331, 1664, -3451 };
    yaw = 57344;
    pitch = 3840;
    graphic_offset = GRAPHIC_OFFSET_MAX;
    update_camera_reset_velocities();
}

void game_setup()
{
    reset_to_title();
}

void move_forward(int16_t amount)
{
    int16_t sinA = mul_f15_s16(amount, fsin16(yaw));
    int16_t cosA = mul_f15_s16(amount, fcos16(yaw));
    cam.x += sinA;
    cam.z -= cosA;
}

void move_right(int16_t amount)
{
    int16_t sinA = mul_f15_s16(amount, fsin16(yaw));
    int16_t cosA = mul_f15_s16(amount, fcos16(yaw));
    cam.x += cosA;
    cam.z += sinA;
}
void move_up(int16_t amount)
{
    cam.y += amount;
}

void look_up(int16_t amount)
{
    pitch -= amount;
    pitch = tclamp<int16_t>(pitch, -64 * 256, 64 * 256);
}
void look_right(int16_t amount)
{
    yaw += amount;
}

bool ball_in_hole()
{
    dvec3 flag;
    memcpy_P(&flag, &current_level->flag_pos, sizeof(flag));
    flag.x = tabs(flag.x - ball.x);
    flag.y = tabs(flag.y - ball.y);
    flag.z = tabs(flag.z - ball.z);
    return flag.x < 256 && flag.y < 256 && flag.z < 256;
}

static void draw_scorecard(uint8_t r, uint8_t i)
{
    constexpr uint8_t OX = 0;
    uint8_t y = r * 8;
    for(uint8_t x = 0; x <= 104; x += 2)
    {
        set_pixel(x + OX, y + 9);
        set_pixel(x + OX, y + 17);
        set_pixel(x + OX, y + 25);
    }
    uint8_t* b = &buf[0] + (r + 1) * FBW + OX;
    for(uint8_t x = 0; x <= 90; x += 10)
        b[x] = b[x + FBW] = 0xaa;
    b[104] = b[104 + FBW] = 0xaa;
    uint8_t tpar = 0;
    uint16_t tshot = 0;
    for(uint8_t n = 1, x = OX + 2; n <= 9; ++n, x += 10)
    {
        set_number2(n + i, r, x);
        uint8_t t = shots[n + i - 1];
        tshot += t;
        if(t != 0)
        {
            set_number2(t, r + 2, x);
            t = pgm_read_byte(&PARS[n + i - 1]);
            tpar += t;
            set_number2(t, r + 1, x);
        }
    }
    if(tpar != 0)
    {
        set_number3(tpar, r + 1, OX + 92);
        set_number3(tshot, r + 2, OX + 92);
    }
}

void game_loop()
{
    uint8_t btns = poll_btns();
    uint8_t pressed = btns & ~prev_btns;
    prev_btns = btns;

    ++nframe;

    if(state == st::TITLE)
    {
#if 0
        // enable this block to adjust camera view at title screen

        uint8_t btns = poll_btns();

        if(btns & BTN_A)
        {
            // look
            if(btns & BTN_UP) look_up(256);
            if(btns & BTN_DOWN) look_up(-256);
            if(btns & BTN_LEFT) look_right(-256);
            if(btns & BTN_RIGHT) look_right(256);

            pitch = tclamp<int16_t>(pitch, -64 * 256, 64 * 256);
        }
        else if(btns & BTN_B)
        {
            // rise and fall
            if(btns & BTN_UP) move_up(64);
            if(btns & BTN_DOWN) move_up(-64);
        }
        else
        {
            // move and strafe
            int8_t sinA = fsin(yaw) / 4;
            int8_t cosA = fcos(yaw) / 4;
            if(btns & BTN_UP) move_forward(64);
            if(btns & BTN_DOWN) move_forward(-64);
            if(btns & BTN_LEFT) move_right(-64);
            if(btns & BTN_RIGHT) move_right(64);
        }
#else
        if(pressed & BTN_A)
            set_level(STARTING_LEVEL);
        else if(pressed & (BTN_LEFT | BTN_RIGHT))
            practice ^= 1;
#endif
        render_scene();
        draw_graphic(GFX_TITLE, 1, 50, 2, 77, GRAPHIC_OVERWRITE);
        draw_graphic(GFX_SUBTITLE, 4, 50, 1, 77, GRAPHIC_OVERWRITE);

        uint8_t x0 = 49, x1 = 73;
        if(practice)
            x0 = 81, x1 = 127;
        while(x0 <= x1)
        {
            for(uint8_t y = 32; y <= 40; ++y)
                inv_pixel(x0, y);
            ++x0;
        }
        return;
    }
    else if(state == st::LEVEL)
    {
        update_camera_look_at_fastangle(
            { 0, 0, 0 }, yaw_level, 6000, 256 * 25, 64, 64);
        yaw_level += 256;
        if(practice & 1)
        {
            if(pressed & BTN_LEFT)
                leveli = (leveli == 0 ? NUM_LEVELS - 1 : leveli - 1);
            if(pressed & BTN_RIGHT)
                leveli = (leveli == NUM_LEVELS - 1 ? 0 : leveli + 1);
            if(pressed & BTN_A)
                state = st::AIM, practice = 2, aim_wait = 0;
            if(pressed & BTN_B)
                reset_to_title();
            current_level = &LEVELS[leveli];
            reset_ball();
            render_scene();
            draw_graphic(GFX_INFO_BAR, 6, 0, 2, 28, GRAPHIC_OVERWRITE);
            set_number2(leveli + 1, 6, 18);
            set_number2(pgm_read_byte(&PARS[leveli]), 7, 18);
            return;
        }
        else
        {
            if(graphic_offset < GRAPHIC_OFFSET_MAX)
                ++graphic_offset;
            if(nframe == 255 || (pressed & BTN_B))
                state = st::AIM, aim_wait = 0;
        }
    }
    else if(state == st::AIM)
    {
        dvec3 above_ball = ball;
        above_ball.y += (256 * 2);
        int16_t pitch = 4096;
        uint16_t dist = 256 * 6;
        update_camera_look_at_fastangle(
            above_ball, yaw_aim, pitch, dist, 64, 64);

        uint8_t btns = poll_btns();
        if(btns & BTN_LEFT ) yaw_aim -= 128;
        if(btns & BTN_RIGHT) yaw_aim += 128;

        if(btns & BTN_UP  ) power_aim += 2;
        if(btns & BTN_DOWN) power_aim -= 2;
        power_aim = tclamp(power_aim, MIN_POWER, MAX_POWER);

        if(graphic_offset > 0)
            --graphic_offset;

        if(aim_wait < 32)
            ++aim_wait;
        else if(btns & BTN_A)
        {
            int16_t ys = fsin16(yaw_aim);
            int16_t yc = -fcos16(yaw_aim);
            prev_ball = ball;
            ball_vel.x = mul_f8_s16(ys, power_aim);
            ball_vel.z = mul_f8_s16(yc, power_aim);
            state = st::ROLLING;
        }

        if(pressed & BTN_B)
        {
            yaw_level = yaw_aim;
            nframe = 0;
            state = st::LEVEL;
        }
    }
    else if(state == st::ROLLING)
    {
        if(physics_step())
        {
            yaw_aim = yaw_to_flag();
            shots[leveli] += 1;
            state = st::AIM;
        }
        else if(ball.y < (256 * -20))
        {
            ball = prev_ball;
            ball_vel = {};
            ball_vel_ang = {};
            shots[leveli] += 2; // penalty
            state = st::AIM;
        }
        else if(ball_in_hole())
        {
            shots[leveli] += 1;
            state = st::HOLE;
            yaw_aim = yaw;
            nframe = 0;
        }
        update_camera_follow_ball(256 * 12, 64, 16);
        if(graphic_offset < GRAPHIC_OFFSET_MAX)
            ++graphic_offset;
    }
    else if(state == st::HOLE)
    {
        dvec3 flag;
        memcpy_P(&flag, &current_level->flag_pos, sizeof(flag));
        update_camera_look_at_fastangle(flag, yaw_aim, 6000, 256 * 20, 64, 64);
        yaw_aim += 256;
        if(nframe == 255)
            state = st::SCORE;
        if(graphic_offset < GRAPHIC_OFFSET_MAX)
            ++graphic_offset;
    }
    else if(state == st::SCORE)
    {
        draw_scorecard(0, 0);
        draw_scorecard(4, 9);
        if(btns & (BTN_A | BTN_B))
        {
            if(nframe == 32)
            {
                if(practice || (btns & BTN_B) || leveli == sizeof(LEVELS) / sizeof(LEVELS[0]) - 1)
                    practice >>= 1, reset_to_title();
                else
                    set_level(leveli + 1);
            }
        }
        else
            nframe = 0;
        uint8_t proga = 0, progb = 0;
        if(     btns & BTN_A) proga = nframe;
        else if(btns & BTN_B) progb = nframe;
        if(!practice)
        {
            draw_nframe_progress(21, proga);
            draw_graphic(GFX_NEXT, 2, 110, 1, 15, GRAPHIC_SET);
        }
        draw_nframe_progress(21 + 24, progb);
        draw_graphic(GFX_QUIT, 5, 110, 1, 15, GRAPHIC_SET);
        return;
    }

    render_scene();

    draw_graphic(GFX_INFO_BAR, 5, -graphic_offset, 3, 28, GRAPHIC_OVERWRITE);
    {
        uint8_t nx = 18 - graphic_offset;
        set_number2(leveli + 1, 5, nx);
        set_number2(pgm_read_byte(&PARS[leveli]), 6, nx);
        set_number2(shots[leveli] + 1, 7, nx);
    }

    if(graphic_offset < 5)
    {
        uint8_t* b = &buf[0] + (FBW - 6) + graphic_offset;
        uint8_t t = 6 - graphic_offset;
        for(uint16_t y = 0; y < FBW * 8; y += FBW)
        {
            for(uint8_t x = 0; x < t; ++x)
                b[y + x] = 0;
            b[y + 1] = 0xff;
        }
        t = 125 + graphic_offset;
        for(uint8_t y = 64 - (power_aim >> 1); y < 64; ++y)
            for(uint8_t x = t; x < 128; ++x)
                set_pixel(x, y);
    }
    draw_graphic(GFX_POWER, 7, 100 + graphic_offset, 1, 24, GRAPHIC_OVERWRITE);
}
