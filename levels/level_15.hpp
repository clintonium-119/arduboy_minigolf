#pragma once

static constexpr int8_t LEVEL_15_VERTS[126] PROGMEM =
{
      -8,   +0,  -30,   -8,   +0,  -10,   +2,   +0,  -21,   +1,   +0,  -22,
      +2,   +0,  -19,   +1,   +0,  -18,   -1,   +0,  -22,   -2,   +0,  -21,
      -1,   +0,  -18,   -2,   +0,  -19,  +10,   +4,  +40,   +2,   +0,  -30,
      +2,   +0,  -10,  +10,   +4,  +30,  -10,   +4,  +30,  -10,   +4,  +40,
     -20,   -4,  -10,  -20,   -4,  -30,   +8,   +0,  -10,  +20,   -4,  -30,
     +20,   -4,  -10,   +8,   +0,  -30,  -40,   +4,  +10,  +40,   -4,  -10,
     -40,   -4,  -10,  -20,   +4,  +10,  +20,   +4,  +10,  +40,   +4,  +10,
     +20,   +4,  +30,   +0,   +4,  +30,   +0,   +4,  +10,  -20,   +4,  +30,
      +8,   +4,  -30,   -8,   +4,  -30,  -20,   +0,  -30,  +20,   +0,  -30,
     -40,   +8,  +10,  +40,   +0,  -10,  -40,   +0,  -10,  +40,   +8,  +10,
     +20,   +8,  +30,  -20,   +8,  +30, 
};

static constexpr uint8_t LEVEL_15_FACES[120] PROGMEM =
{
     21,  33,  32,  31,  36,  22,  23,  35,  19,  24,  34,  17,
     28,  39,  27,  21,   0,  33,  31,  41,  36,  23,  37,  35,
     24,  38,  34,  28,  40,  39,   0,  16,  17,  18,  19,  21,
     16,  22,  24,  20,  27,  23,   0,   1,  16,  18,  20,  19,
     16,  25,  22,  20,  26,  27,   9,   0,   7,  13,  15,  14,
     12,  21,  11,  19,  20,  23,  17,  16,  24,  27,  26,  28,
     22,  25,  31,  26,  29,  28,  25,  29,  31,   5,   4,  12,
     12,   1,   8,   1,   0,   9,  11,   2,   3,  11,   3,   6,
      8,   5,  12,   9,   8,   1,   0,  11,   6,   0,   6,   7,
     13,  10,  15,  12,  18,  21,  26,  30,  29,  25,  30,  29,

};

#define LEVEL_15_NUM_FACES { 0, 0, 10, 8, 22, }
