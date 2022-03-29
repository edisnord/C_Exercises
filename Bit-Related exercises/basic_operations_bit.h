//
// Created by edish on 27.3.22.
//
#include "math.h"
#ifndef TEST_BASIC_OPERATIONS_BIT_H
#define TEST_BASIC_OPERATIONS_BIT_H
//Related to printing 8-bit variables
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

int pow2(int n, int val);

int createMaskOfOnes(int n, int p);

#endif //TEST_BASIC_OPERATIONS_BIT_H
