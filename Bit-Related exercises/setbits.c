#include "setbits.h"
#include "basic_operations_bit.h"

unsigned setBits(int x, int p, int n, int y){
    return (x & ~(pow2(n - 1, 0) << (p+1 - n))) | (y & (pow2(n - 1, 0) << (p+1 - n)));
}

