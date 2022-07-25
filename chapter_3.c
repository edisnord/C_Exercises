#include "chapter_3.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

void reverseIterative(char s[]) {
    int c, i, j; //ABAP aaaaaa
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void escape(char s[], char t[]){
    int i = 0;
    int j = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        switch (s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                break;
            default:
                t[j++] = s[i];
        }
    }
    t[++j] = '\0';
}

void unescape(char s[], char t[]){
    int i = 0;
    int j = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        switch (s[i]) {
            case '\\':
                switch (s[i + 1]) {
                    case 'n':
                        t[j++] = '\n';
                        i++;
                        break;
                    case 't':
                        t[j++] = '\t';
                        i++;
                        break;
                }
                break;
            default:
                t[j++] = s[i];
        }
    }
    t[++j] = '\0';
}

int binarySearch(int x, int v[], int n){
    int low, mid, high;

    low = 0;
    high = n-1;
    for(mid = (low+high)/2; low <= high && v[mid] != x; mid = (low+high)/2){
        if(x < v[mid]){
            high = mid + 1;
        }else
            low = mid + 1;

    }

    if(low <= high)
    return mid;
    else return -1;

    }

void expand(char s1[], char s2[]){
    int s2index = 0;
    for (int i = 0; i < strlen(s1); ++i) {
        if(s1[i+1] != '-') {
            s2[s2index++] = s1[i];
        } else {
            char upperbound;
            int milti = 0;
            for (int j = i + 1; s1[j] == '-'; j = j + 2) {
                milti += 1;
                upperbound = s1[j + 1];
            }
            if(!milti) upperbound = s1[i];
            i=i + 2 * milti;
            for (int j = s1[i - 2 * milti]; j <= upperbound; ++j) {
                s2[s2index++] = j;
            }

        }
    }
    s2[s2index] = '\0';
}

void itob(int n, char s[], int b){
    int helper, values, remainder;
    helper = b;
    do{ values++; }while ((helper *= b) < n) ;
    for (int i = values; i >= 0 ; --i) {
        if(i == values) {
            remainder = n / pow((double)b, i);
            s[values - i] = remainder + '0';
            n = n % (int)pow((double)b, i);
            continue;
        }
        s[values - i] = n / (int)pow((double)b, i) + '0';
        n = n % (int)pow((double)b, i);
    }
    s[values+1] = '\0';
}

void itoa2(int n, char s[], int fieldWidth){
    int i, sign;
    i = 0;
    sign = n;
    do{
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);

    if(sign < 0){
        s[i++] = '-';
    }
    if(i < fieldWidth){
        while(i < fieldWidth){
            s[i++] = ' ';
        }
    }
    //reverse(s);
    s[strlen(s)] = '\0';
}