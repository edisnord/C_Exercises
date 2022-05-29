//
// Created by edis on 22-05-29.
//

#ifndef TEST_CHAPTER4_CALCULATOR_H
#define TEST_CHAPTER4_CALCULATOR_H

#define BUFSIZE 100
#define MAXVAL 100
#define NUMBER '0'
#define NEGNUMBER '1'
#define END '\n'
#define MAXOP 100

#include "main.h"
#include "stdio.h"
#include "ctype.h"

int getch();
void ungetch(int c);
int getop(char s[]);
void push(double f);
double pop();

#endif //TEST_CHAPTER4_CALCULATOR_H