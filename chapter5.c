//
// Created by Edis Hasaj on 6/21/2022.
//

#include "chapter5.h"
#include "string.h"

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

//5-3 strcat
char* strcat_edis(char* a, char* b)
{
    char* i = a;
    a = a + strlen(a);
    while (*b){
        *(a++) = *b++;
    }
    *(++a) = '\0';
    a = a - (a - i);
    return a;
}

int strend_edis(char* s, char* t){
    int len2= strlen(t);
    s = s + strlen(s);
    t = t + len2;
    while (*--s == *--t){
        len2--;
        if(len2 == 0){
            return 1;
        }
    }
    return 0;
}

void strncpy_edis(char* destination, char* source, int n){
    while (*destination && n > 0){
        *destination++ = *source++;
        n--;
    }
}

void strncat_edis(char* a, char* b, int n){
    char* i = a;
    a = a + strlen(a);
    while (*b && (n > 0)){
        n--;
        *(a++) = *b++;
    }
    *(++a) = '\0';
}

int strncmp_edis(char* a, char* b, int n){
   while((*a++ == *b++) & (n > 0)){
       n--;
   }
    return n == 0 ? 0 : *--a < *--b ? 1 : -1;
}

int strindex_ptr(char s[], char t[]) {
    char* init = s;
    while(*s){
        char* temp = t;
        while(*s++ == *t++){
            if(*s == '\0') return (s - init) - (t - temp);
        }
        t = temp;
    }
    return -1;
}

int getline_ptr(char s[],int lim)
{
    int c, i;
    char* init = s;
    while ((c=getchar())!=EOF && c!='\n')
        *s++ = c;
    if (c == '\n') {
        *s++ = c;
        ++i;
    }
    *s = '\0';
    s = s - (s - init);
    return i;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    char* initDays = *(daytab + leap);
    char* days = *(daytab + leap);
    while (yearday > *days)
        yearday -= *days++;
    *pmonth = days - initDays;
    *pday = yearday;
}

int day_of_year(int year, int month, int day)
{
    int leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    char* days = *(daytab + leap);
    char* topDays = *(daytab+leap) + month;
    while (days != topDays)
        day += *days++;
    return day;
}