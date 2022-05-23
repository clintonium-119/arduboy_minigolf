#include "game.hpp"

uint8_t const INFO_BAR[76] PROGMEM =
{
    0xfa, 0x22, 0xfa, 0x02, 0x72, 0x8a, 0x72, 0x02,
    0xfa, 0x82, 0x82, 0x02, 0xfa, 0xaa, 0x8a, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0xfc, 0x02, 0xfa, 0x2a, 0x12, 0x02,
    0xf2, 0x2a, 0xf2, 0x02, 0xfa, 0x2a, 0xd2, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xfc, 0x02,
    0x92, 0xaa, 0x4a, 0x02, 0xfa, 0x22, 0xfa, 0x02,
    0x72, 0x8a, 0x72, 0x02, 0x0a, 0xfa, 0x0a, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0xfc, 0x00,
};

void draw_graphic(uint8_t const* p, uint8_t r, uint8_t c, uint8_t h, uint8_t w)
{
    uint8_t* br = &buf[r * FBW + c];
    for(uint8_t y = 0; y < h; ++y, br += 128)
    {
        uint8_t* bc = br;
        for(uint8_t x = 0; x < w; ++x, ++bc)
            *bc = pgm_read_byte(p++);
    }
}

void set_graphic(uint8_t const* p, uint8_t r, uint8_t c, uint8_t h, uint8_t w)
{
    uint8_t* br = &buf[r * FBW + c];
    for(uint8_t y = 0; y < h; ++y, br += 128)
    {
        uint8_t* bc = br;
        for(uint8_t x = 0; x < w; ++x, ++bc)
            *bc |= pgm_read_byte(p++);
    }
}

static uint8_t const NUMBERS[3 * 10] PROGMEM =
{
    0x70, 0x88, 0x70, 0x90, 0xf8, 0x80, 0xc8, 0xa8,
    0x90, 0x88, 0xa8, 0x50, 0x38, 0x20, 0xf8, 0xb8,
    0xa8, 0x48, 0x70, 0xa8, 0x40, 0x08, 0xc8, 0x38,
    0x50, 0xa8, 0x50, 0x10, 0xa8, 0x70,
};

void set_number(uint8_t n, uint8_t r, uint8_t c)
{
    set_graphic(&NUMBERS[n * 3], r, c, 1, 3);
}
