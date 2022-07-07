#ifndef TEST_CHAPTER6_H
#define TEST_CHAPTER6_H
#include <bits/types/FILE.h>
//6-2



void parseVars(char* pathToFile, int upTo);
void readStatementsf(FILE* file, char** statements );
void handleWhitespaces(char* statement);
void getTokens(char* statement, char** tokens);
int isDeclaration(char** tokens);
int isType(char* token);
int isQualifier(char* token);
int isModifier(char* token)
//end of 6-2

#endif //TEST_CHAPTER6_H
