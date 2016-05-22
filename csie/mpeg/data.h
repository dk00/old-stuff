#ifndef _DATA_H
#define _DATA_H
#include<stdint.h>
const uint8_t intra_quant_def[] = {
   8, 16, 19, 22, 26, 27, 29, 34,
  16, 16, 22, 24, 27, 29, 34, 37,
  19, 22, 26, 27, 29, 34, 34, 38,
  22, 22, 26, 27, 29, 34, 37, 40,
  22, 26, 27, 29, 32, 35, 40, 48,
  26, 27, 29, 32, 35, 40, 48, 58,
  26, 27, 29, 34, 38, 46, 56, 69,
  27, 29, 35, 38, 46, 56, 69, 83   
};

enum vlc_tables {
  B1, B2, B2c, B3, B4, B5, B5b, B5c
};

const bool mb_quant[][11] = {
  {},
  {0, 1}, 
  {0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}
}, mb_mfw[][11] = {
  {},
  {0, 0}, 
  {1, 0, 1, 0, 1, 0, 0},
  {1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0}
}, mb_mbw[][11] = {
  {},
  {0, 0}, 
  {0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0}
}, mb_pattern[][11] = {
  {},
  {0, 0}, 
  {1, 1, 0, 0, 1, 1, 0},
  {1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0}
}, mb_intra[][11] = {
  {},
  {1, 1}, 
  {0, 0, 0, 1, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}
};



const int cbp[] = {15, 8, 4, 2, 1, 12, 3, 10, 5, 14, 13, 11, 7, 32, 47, 16, 31, 6, 9, 48, 63, 40, 36, 34, 33, 24, 20, 18, 17, 56, 52, 50, 49, 44, 35, 42, 37, 28, 19, 26, 21, 60, 51, 58, 53, 38, 41, 22, 25, 46, 45, 43, 39, 30, 29, 27, 23, 62, 61, 59, 55, 54, 57},
_level[] = {
  1,  2,  3,  4,  5,  6,  7,  8,
   9, 10, 11, 12, 13, 14, 15, 16,
  17, 18, 19, 20, 21, 22, 23, 24,
  25, 26, 27, 28, 29, 30, 31, 32,
  33, 34, 35, 36, 37, 38, 39, 40,
   1,  2,  3,  4,  5,  6,  7,  8,
   9, 10, 11, 12, 13, 14, 15, 16,
  17, 18,  1,  2,  3,  4,  5,  1,
   2,  3,  4,  1,  2,  3,  1,  2,
   3,  1,  2,  3,  1,  2,  1,  2,
   1,  2,  1,  2,  1,  2,  1,  2,
   1,  2,  1,  2,  1,  2,  1,  2,
   1,  1,  1,  1,  1,  1,  1,  1,
   1,  1,  1,  1,  1,  1,  1 }, 
_run[] = {
 0,  0,  0,  0,  0,  0,  0,  0,
 0,  0,  0,  0,  0,  0,  0,  0,
 0,  0,  0,  0,  0,  0,  0,  0,
 0,  0,  0,  0,  0,  0,  0,  0,
 0,  0,  0,  0,  0,  0,  0,  0,
 1,  1,  1,  1,  1,  1,  1,  1,
 1,  1,  1,  1,  1,  1,  1,  1,
 1,  1,  2,  2,  2,  2,  2,  3,
 3,  3,  3,  4,  4,  4,  5,  5,
 5,  6,  6,  6,  7,  7,  8,  8,
 9,  9, 10, 10, 11, 11, 12, 12,
13, 13, 14, 14, 15, 15, 16, 16,
17, 18, 19, 20, 21, 22, 23, 24,
25, 26, 27, 28, 29, 30, 31};

#endif
