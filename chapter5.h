//
// Created by Edis Hasaj on 6/21/2022.
//

#ifndef TEST_CHAPTER5_H
#define TEST_CHAPTER5_H
#include "stdio.h"

//5-1 & 5-2 are boring

//5-3 strcat
char* strcat_edis(char* a, char* b);

//5-4 strend
int strend_edis(char* s, char* t);

//5-5 strncpy, strncat, strncmp
void strncpy_edis(char* destination, char* source, int n);
void strncat_edis(char* a, char* b, int n);
int strncmp_edis(char* a, char* b, int n);

//5-6
//reverse already uses pointers in the recursive version
int strindex_ptr(char s[], char t[]);
int getline_ptr(char s[],int lim);

//5-7 & 5-8 are boring

//5-9
void month_day(int year, int yearday, int *pmonth, int *pday);
int day_of_year(int year, int month, int day);

#endif //TEST_CHAPTER5_H
