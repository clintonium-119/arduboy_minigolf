#include "game.hpp"

static constexpr int8_t SINE_QUAD[65] PROGMEM =
{
      0,   3,   6,   9,  12,  15,  18,  21,
     24,  27,  30,  34,  37,  39,  42,  45,
     48,  51,  54,  57,  60,  62,  65,  68,
     70,  73,  75,  78,  80,  83,  85,  87,
     90,  92,  94,  96,  98, 100, 102, 104,
    106, 107, 109, 110, 112, 113, 115, 116,
    117, 118, 120, 121, 122, 122, 123, 124,
    125, 125, 126, 126, 126, 127, 127, 127,
    127,
};

int8_t fsin(uint8_t angle)
{
    uint8_t i = angle & 0x3f;
    if(angle & 0x40) i = 64 - i;
    int8_t r = (int8_t)pgm_read_byte(&SINE_QUAD[i]);
    if(angle & 0x80) r = -r;
    return r;
}

int8_t fcos(uint8_t angle)
{
    return fsin(angle + 0x40);
}

static constexpr int16_t SINE_QUAD_16[65] PROGMEM =
{
        0,   804,  1608,  2410,  3212,  4011,  4808,  5602,
     6393,  7179,  7962,  8739,  9512, 10278, 11039, 11793,
    12539, 13279, 14010, 14732, 15446, 16151, 16846, 17530,
    18204, 18868, 19519, 20159, 20787, 21403, 22005, 22594,
    23170, 23731, 24279, 24811, 25329, 25832, 26319, 26790,
    27245, 27683, 28105, 28510, 28898, 29268, 29621, 29956,
    30273, 30571, 30852, 31113, 31356, 31580, 31785, 31971,
    32137, 32285, 32412, 32521, 32609, 32678, 32728, 32757,
    32767,
};

static int16_t fsin16_helper(uint8_t angle)
{
    uint8_t i = angle & 0x3f;
    if(angle & 0x40) i = 64 - i;
    int16_t r = (int16_t)pgm_read_word(&SINE_QUAD_16[i]);
    if(angle & 0x80) r = -r;
    return r;
}

int16_t fsin16(uint16_t angle)
{
    uint8_t angle_hi = uint8_t(angle >> 8);
    int16_t s0 = fsin16_helper(angle_hi    );
    int16_t s1 = fsin16_helper(angle_hi + 1);
    uint8_t f1 = uint8_t(angle);
    uint8_t f0 = 255 - f1;
    int16_t t = int16_t(u24(s24(s0) * f0 + s24(s1) * f1 + s0) >> 8);
    return t;
}

int16_t fcos16(uint16_t angle)
{
    return fsin16(angle + 0x4000);
}

static constexpr uint16_t ATAN_TABLE[33] PROGMEM =
{
        1,  1304,  2605,  3900,  5189,  6467,  7733,  8985,
    10221, 11439, 12637, 13814, 14968, 16100, 17206, 18288,
    19344, 20374, 21378, 22355, 23305, 24230, 25128, 26001,
    26848, 27669, 28467, 29240, 29990, 30717, 31422, 32105,
    32767,
};

int16_t atan2(int16_t x, int16_t y)
{
    uint8_t f = 0;
    if(y < 0)
    {
        f |= 1;
        y = -y;
    }
    if(x < 0)
    {
        f |= 2;
        x = -x;
    }
    if(x < y)
    {
        f |= 4;
        swap(x, y);
    }

    uint16_t ratio;
    if(x < 256)
    {
        uint16_t invx = inv8(uint8_t(uint16_t(x) >> 8));
        ratio = uint16_t((uint32_t(invx) * uint16_t(y)) >> 18);
    }
    else
    {
        uint16_t invx = inv16(uint16_t(x));
        ratio = uint16_t((uint32_t(invx) * uint16_t(y)) >> 26);
    }

    uint8_t i = uint8_t(ratio >> 8);
    uint8_t f1 = uint8_t(ratio);
    uint8_t f0 = 255 - f1;
    uint16_t t0 = pgm_read_byte(&ATAN_TABLE[i]);
    uint16_t t1 = pgm_read_byte(&ATAN_TABLE[i + 1]);

    uint16_t t = int16_t(u24(u24(t0) * f0 + u24(t1) * f1 + t0) >> 8);

    if(f & 1) t = -t;
    if(f & 2) t = 32768 - t;
    if(f & 4) t = 16384 - t;

    return t;
}
