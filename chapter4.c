//
// Created by edish on 22-05-11.
//

#include <string.h>
#include <ctype.h>
#include "chapter4.h"

int strindex(const char s[], const char t[]){
    for (int i = strlen(s); i >= 0; --i) {
        for (int j = 0; t[j] == s[j + i]; ++j) {
            if(t[j + 1] == '\0') return i;
        }
    }
    return -1;
}

//float atof(char s[]){
//    double val, power;
//    int i, sign, sign2, pow10;
//    for(i = 0; isspace(s[i]); i++);
//    sign = (s[i] == '-') ? -1 : 1;
//    if(s[i] == '+' || s[i] == '-') i++;
//    for(val = 0.0; isdigit(s[i]); i++)
//        val =  10.0 * val + (s[i] - '0');
//    if(s[i] == '.')
//        i++;
//    for(power = 1.0; isdigit(s[i]); i++){
//        val =  10.0 * val + (s[i] - '0');
//        power /= 10;
//    }
//    if(s[i] == 'e' || s[i] == 'E'){
//        sign2 = (s[++i] == '-') ? -1 : 1;
//        if(s[i] == '+' || s[i] == '-') i++;
//        for (pow10 = 0 ; isdigit(s[i]) ; i++) {
//            pow10 =  10 * val + (s[i] - '0');
//        }
//        power = (sign2 < 0) ? power / pow10 : power * pow10;
//    }
//    return sign * val * power;
//}

