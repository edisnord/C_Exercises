//
// Created by edish on 22-07-11.
//

#ifndef TEST_CHAPTER6_H
#define TEST_CHAPTER6_H

#include <ctype.h>
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#define makeArray malloc(sizeof(char *) * 10000)

#define false 0
#define true 1

char **readStatements(char **statements, FILE *file);
void parseDecl(char *filepath, int chars);
void readStatement(FILE *file, char *resultingStatement);
void trim(char **string);
void getVariableNames(char** statements, char** variables);
int isKeyword( int l, int r, char* x);
int isValidNameChar(char ch);
int cleanName(char** name);
int getNames(char** tokens, char** names);


#endif //TEST_CHAPTER6_H
