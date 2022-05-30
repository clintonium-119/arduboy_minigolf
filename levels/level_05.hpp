#pragma once

static constexpr int8_t LEVEL_05_VERTS[126] PROGMEM =
{
     +24,   +0,  -12,  +40,   +0,  -12,  +40,   +0,  -24,  +24,   +0,  -24,
     +40,   +4,   +8,  +40,   +4,  -12,  +33,   +0,  -12,  +34,   +0,  -13,
     +31,   +0,  -12,  +30,   +0,  -13,  +34,   +0,  -15,  +33,   +0,  -16,
     +30,   +0,  -15,  +31,   +0,  -16,  -40,   +0,  +24,  -24,   +0,  +24,
     -20,   +2,  -18,   +0,   +0,   -8,   +0,   +2,  +18,  +20,   +6,  +24,
     -40,   +0,  +12,  -24,   +0,  +12,  +40,   +6,  +24,   +0,   +6,  +24,
     +40,   +2,  +18,  -40,   +4,   -8,  -40,   +2,  -18,  +20,   +2,  +18,
      +0,   +6,  -24,  -40,   +6,  -24,  -20,   +6,  -24,   +0,   +2,  -18,
     +16,   +0,   +8,  +16,   +0,   -8,  -16,   +0,   +8,  -24,   +0,   -8,
      +0,   +0,   +8,  -16,   +0,   -8,  -40,   +0,   -8,  +24,   +0,   +8,
     -40,   +4,  +12,  +40,   +0,   +8, 
};

static constexpr uint8_t LEVEL_05_FACES[126] PROGMEM =
{
     18,  19,  27,  31,  30,  16,  16,  29,  26,  27,  22,  24,
      1,   4,  41,  38,  40,  20,  18,  23,  19,  31,  28,  30,
     16,  30,  29,  27,  19,  22,   1,   5,   4,  38,  25,  40,
     37,  31,  16,  27,  24,  39,  26,  38,  35,  37,  17,  31,
     26,  35,  16,  35,  37,  16,  24,  41,  39,  39,  32,  27,
     32,  36,  18,  27,  32,  18,  39,   1,  41,  13,   2,  11,
     21,  14,  15,  36,  33,  17,  37,  36,  17,  21,  38,  20,
     39,   0,   1,   9,   8,   0,   0,   3,  12,   3,   2,  13,
      1,   6,   7,   1,   7,  10,  12,   9,   0,  13,  12,   3,
      2,   1,  10,   2,  10,  11,  21,  20,  14,  36,  32,  33,
     37,  34,  36,  21,  35,  38, 
};

#define LEVEL_05_NUM_FACES { 0, 0, 12, 10, 20, }
