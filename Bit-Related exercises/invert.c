#include "invert.h"
#include "basic_operations_bit.h"
//10101010
unsigned invert(int x, int p, int n){
    return (~x & createMaskOfOnes(n, p)) | (x & ~createMaskOfOnes(n, p));
}