#pragma once

static constexpr int8_t LEVEL_09_VERTS[111] PROGMEM =
{
     -20,   +0,  +40,  -20,   +0,  +80,   +0,   +0,  +58,   -2,   +0,  +56,
      +0,   +0,  +62,   -2,   +0,  +64,   -6,   +0,  +56,   -8,   +0,  +58,
      -6,   +0,  +64,   -8,   +0,  +62,  -40,   +0,  +80,   +0,   +8,  +40,
     -80,  +24,   +0,  -40,   +0,  +40,  -80,   +0,  +40,  -80,   +0,  +80,
     -20,   +8,  +40,  -20,   +8,  +80,  -40,  +16,   +0,  -80,  +16,   +0,
     -40,  +16,  -40,   +0,  +16,   +0,   +0,  +16,  -40,  +40,   +0,   +0,
     +40,   +0,  -40,  +80,   +0,   +0,  +40,  +16,  +40,  +80,  +16,  +40,
     +40,  +16,  +80,   +0,   +0,  +40,   +0,   +0,  +80,   +0,   +8,  +80,
     -40,  +24,  -40,  +40,   +8,  -40,  +80,   +8,   +0,  +80,  +24,  +40,
     +40,  +24,  +80, 
};

static constexpr uint8_t LEVEL_09_FACES[111] PROGMEM =
{
      1,  16,   0,   1,  17,  16,   0,  11,  29,  30,  17,   1,
     27,  36,  28,  24,  34,  25,  19,  32,  20,   0,  16,  11,
     30,  31,  17,  27,  35,  36,  24,  33,  34,  19,  12,  32,
     13,  19,  18,  22,  23,  21,  25,  26,  23,  28,  29,  26,
     13,  14,  19,  22,  24,  23,  25,  27,  26,  28,  30,  29,
      9,   0,   7,  14,  10,  15,  18,  19,  20,  20,  21,  18,
     23,  24,  25,  26,  27,  28,   5,   4,  30,  30,   1,   8,
      1,   0,   9,  29,   2,   3,  29,   3,   6,   8,   5,  30,
      9,   8,   1,   0,  29,   6,   0,   6,   7,  14,  13,  10,
     20,  22,  21, 
};

#define LEVEL_09_NUM_FACES { 0, 2, 10, 8, 17, }
