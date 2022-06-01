#pragma once

static constexpr int8_t LEVEL_00_VERTS[126] PROGMEM =
{
     -20,   +0,  -56,  +20,   +0,  -56,  +20,   +0,  -72,  -20,   +0,  -72,
     +20,   +8,  -72,  -20,   +8,  -72,   +2,   +0,  -56,   +4,   +0,  -58,
      -2,   +0,  -56,   -4,   +0,  -58,   +4,   +0,  -62,   +2,   +0,  -64,
      -4,   +0,  -62,   -2,   +0,  -64,   +0,   +8,  -12,  -12,   +8,   +0,
      +0,   +8,  +12,  +12,   +8,   +0,  +12,   +0,   +0,   +0,   +0,  +12,
     -12,   +0,   +0,   +0,   +0,  -12,  +20,   +0,  +72,  -20,   +0,  +72,
     +36,   +0,  -20,  +36,   +0,  +20,  -36,   +0,  -20,  -36,   +0,  +20,
     -20,   +0,  +36,  +20,   +0,  +36,  +20,   +0,  -36,  -20,   +0,  -36,
     +20,   +8,  +72,  -20,   +8,  +72,  +36,   +8,  -20,  +36,   +8,  +20,
     -36,   +8,  -20,  -36,   +8,  +20,  -20,   +8,  +36,  +20,   +8,  +36,
     +20,   +8,  -36,  -20,   +8,  -36, 
};

static constexpr uint8_t LEVEL_00_FACES[174] PROGMEM =
{
      2,   5,   3,  20,  14,  21,  19,  17,  18,  24,  40,  30,
     31,  36,  26,   2,   4,   5,  20,  15,  14,  19,  16,  17,
     24,  34,  40,  31,  41,  36,  20,  16,  19,  21,  17,  18,
     25,  34,  24,  22,  39,  29,  28,  33,  23,   5,  31,   3,
     26,  37,  27,  30,   4,   2,  20,  15,  16,  21,  14,  17,
     25,  35,  34,  22,  32,  39,  28,  38,  33,   5,  41,  31,
     26,  36,  37,  30,  40,   4,  27,  38,  28,  29,  35,  25,
     14,  16,  17,  27,  37,  38,  29,  39,  35,  14,  15,  16,
     13,   3,   2,  28,  29,  19,   0,  31,  30,   9,   8,   0,
      2,   1,  10,   1,   6,   7,   1,   7,  10,   9,   0,  12,
      0,   3,  12,   2,  10,  11,  13,  12,   3,   2,  11,  13,
     20,  21,  31,  31,  26,  20,  26,  27,  20,  28,  23,  22,
     27,  28,  20,  28,  22,  29,  29,  25,  19,  25,  24,  18,
     19,  25,  18,  19,  20,  28,  31,  21,  30,  21,  18,  30,
     18,  24,  30,  30,   1,   0, 
};

#define LEVEL_00_NUM_FACES { 0, 10, 16, 6, 26, }
