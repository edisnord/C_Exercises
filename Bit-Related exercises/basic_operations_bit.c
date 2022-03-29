#include "basic_operations_bit.h"

int pow2(int n, int val){
    if(n == -1){
        return val;
    }
    return pow2(n-1, val += pow(2, n));
}

int createMaskOfOnes(int n, int p){
    return (pow2(n - 1, 0) << (p+1 - n));
}
