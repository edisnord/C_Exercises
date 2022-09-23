//
// Created by edish on 22-07-11.
//

#ifndef TEST_CHAPTER6_EX2_H
#define TEST_CHAPTER6_EX2_H

#include "DataStructures/HashMap.h"
#include "DataStructures/DoublyLinkedList.h"
#include <ctype.h>
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define makeArray malloc(sizeof(char *) * 200)

#define false 0
#define true 1

char **readStatements(char **statements, FILE *file);

void parseDecl(char *filepath, int chars);

void readStatement(FILE *file, char *resultingStatement);

long getVariableNames(char **statements, char ***names);

int isKeyword(int l, int r, char *x);

int isValidNameChar(char ch);

int getNames(char **tokens, char **names);

void seeMatching(char **names, int num, int matching);

#endif //TEST_CHAPTER6_EX2_H
