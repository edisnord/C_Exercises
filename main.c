#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"
#include "chapter4_calculator.h"
#include "chapter4.h"
#include "chapter5.h"
#include "math.h"

int main(){
    int a, b;
    month_day(1988, 60, &a, &b);
    printf("%d", day_of_year(1988, 2, 2));
}

