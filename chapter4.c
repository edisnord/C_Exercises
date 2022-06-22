//
// Created by edish on 22-05-11.
//

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "chapter4.h"

int strindex(const char s[], const char t[]) {
    for (int i = strlen(s); i >= 0; --i) {
        for (int j = 0; t[j] == s[j + i]; ++j) {
            if (t[j + 1] == '\0') return i;
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

void recursiveitoa(char a[], int num, int count) {
    if (num == 0) {
        count--;
        for (int i = 0; i < count / 2; ++i) {
            char temp = a[count - i];
            a[count - i] = a[i];
            a[i] = temp;
        }
        a[++count] = '\0';
        return;
    } else {
        a[count++] = (num % 10) + '0';
        num = num / 10;
        recursiveitoa(a, num, count);
    }
}

void reverse(char **string) {
    int len1 = strlen(*string);
    int len2 = strlen(*string + len1 + 1);
    //Termination condition
    if (!len1) {
        //Shift 1 char to the right
        *string = *string + 1;
        return;
    }
    //Make the string dynamically allocated so we can expand it using
    //realloc
    char *temp = (char *) malloc((len1 + len2) * sizeof(char));
    strcpy(temp, *string);
    strcpy(temp + len1 + 1, *string + len1 + 1);
    free(*string);
    *string = temp;

    //Krijo placeholder per string mbrapa string
    char *string2 = (char *) malloc((len2 += 2) * sizeof(char));
    strcpy(string2 + 1, *string + len1 + 1);

    //Merr elementin e fundit te stringut, vendose ne fund te string2
    string2[0] = '0';
    string2[len2 - 1] = (*string)[len1 - 1];
    (*string)[len1 - 1] = '\0';
    string2[len2] = '\0';

    //concatenate string2 string1
    strcat(*string, string2);
    int totalLen = strlen(*string);
    //hiq placeholder 0
    (*string)[totalLen - len2] = '\0';

    reverse(string);

}