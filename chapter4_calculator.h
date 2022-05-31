//
// Created by edis on 22-05-29.
//

#ifndef TEST_CHAPTER4_CALCULATOR_H
#define TEST_CHAPTER4_CALCULATOR_H

#define BUFSIZE 1
#define MAXVAL 100
#define NUMBER '0'
#define NEGNUMBER '1'
#define END '\n'
#define MAXOP 100

#include "main.h"
#include "stdio.h"
#include "ctype.h"

int getch();
int checkLine(char s[]);
void ungetch(int c);
int getop(char s[], double* parsed);
void push(double f);
double pop();

#endif //TEST_CHAPTER4_CALCULATOR_H