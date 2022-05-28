#pragma once

static constexpr phys_box LEVEL_09_BOXES[14] PROGMEM =
{
    { { 160, 0, 248 }, { 0, 0, 10 }, 0, 0 },
    { { 72, 0, 16 }, { -22, 0, -56 }, 0, 0 },
    { { 72, 0, 16 }, { 22, 0, -56 }, 0, 0 },
    { { 160, 0, 24 }, { 0, 0, -66 }, 0, 0 },
    { { 160, 16, 0 }, { 0, 4, -72 }, 0, 0 },
    { { 0, 16, 72 }, { -40, 4, -54 }, 0, 0 },
    { { 0, 16, 72 }, { 40, 4, -54 }, 0, 0 },
    { { 32, 16, 0 }, { 0, 4, 0 }, 0, 0 },
    { { 32, 16, 0 }, { -32, 4, -16 }, 0, 0 },
    { { 32, 16, 0 }, { 32, 4, -16 }, 0, 0 },
    { { 32, 16, 0 }, { 0, 4, -32 }, 0, 0 },
    { { 45, 16, 0 }, { -32, 4, 16 }, 32, 0 },
    { { 45, 16, 0 }, { 32, 4, 16 }, 224, 0 },
    { { 48, 0, 19 }, { 0, 2, 32 }, 0, 19 },
};
static constexpr dvec3 LEVEL_09_BALL_POS = { 0, 128, 3840 };
static constexpr dvec3 LEVEL_09_FLAG_POS = { 0, -256, -3584 };
