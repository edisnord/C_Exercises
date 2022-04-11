#include "chapter_3.h"

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
