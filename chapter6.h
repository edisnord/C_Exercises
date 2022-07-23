//
// Created by edish on 22-07-11.
//

#ifndef TEST_CHAPTER6_H
#define TEST_CHAPTER6_H

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define false 0
#define true 1

char **readStatements(char **statements, FILE *file);
void parseDecl(char *filepath, int chars);
void readStatement(FILE *file, char *resultingStatement);

#endif //TEST_CHAPTER6_H
