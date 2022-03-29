#include "rightRot.h"

unsigned rightRot(int x, int n){
    return (x >> 2*n << n) |
            (((x << (8 - n)) + (x >> (8 - n))));
}