#pragma once

static constexpr phys_box LEVEL_16_BOXES[21] PROGMEM =
{
    { { 80, 0, 120 }, { -20, 0, 50 }, 0, 0 },
    { { 160, 0, 80 }, { 40, 0, 40 }, 0, 0 },
    { { 120, 0, 80 }, { 50, -12, -20 }, 0, 0 },
    { { 80, 0, 160 }, { 20, 12, -40 }, 0, 0 },
    { { 80, 0, 160 }, { -20, 0, -40 }, 0, 0 },
    { { 16, 0, 80 }, { -60, 12, -60 }, 0, 0 },
    { { 16, 0, 32 }, { -68, 12, -48 }, 0, 0 },
    { { 16, 0, 32 }, { -68, 12, -72 }, 0, 0 },
    { { 16, 0, 80 }, { -76, 12, -60 }, 0, 0 },
    { { 0, 16, 80 }, { -80, 16, -60 }, 0, 0 },
    { { 80, 16, 0 }, { -20, 4, -80 }, 0, 0 },
    { { 0, 16, 80 }, { 0, 16, -20 }, 0, 0 },
    { { 114, 16, 0 }, { -20, 4, 40 }, 32, 0 },
    { { 114, 16, 0 }, { 60, 4, 40 }, 32, 0 },
    { { 114, 16, 0 }, { 60, -8, -20 }, 224, 0 },
    { { 114, 16, 0 }, { -20, 4, -20 }, 224, 0 },
    { { 114, 16, 0 }, { 20, 16, -60 }, 224, 0 },
    { { 80, 0, 47 }, { 60, -6, 10 }, 0, -22 },
    { { 80, 0, 47 }, { 20, 6, 10 }, 0, 22 },
    { { 80, 0, 47 }, { 10, -6, -20 }, 64, 22 },
    { { 80, 0, 41 }, { -48, 6, -60 }, 64, 26 },
};
static constexpr dvec3 LEVEL_16_BALL_POS = { -1280, 128, 4608 };
static constexpr dvec3 LEVEL_16_FLAG_POS = { -4352, 512, -3840 };
