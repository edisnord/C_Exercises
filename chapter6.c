#include <ctype.h>
#include "chapter6.h"

char keywords[13][8] = {"auto", "char", "int", "long", "short", "const",
                        "enum", "volatile", "restrict" ,"float", "double", "register",
                        "static"};

void parseDecl(char *filepath, int chars) {
    char **statements = makeArray;
    char **variables = makeArray;
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
        return;

    readStatements(statements, file);
    puts("File read completely!");
    getVariableNames(statements, variables);

}

int getNames(char** tokens, char** names){
    int i;
    int j;
    for (i = 0; tokens[i] != NULL; ++i) {
        if(!isKeyword(0, 12, tokens[i])){
            if(i == 0)
                return 0;
            else
                break;
        }
    }

    for(j = 0; tokens[i] != NULL; ++i){
        if(!strcmp(*(tokens+i), "=")) break;
        cleanName(tokens+i);
        if(strlen(*(tokens+i)) == 0) continue;
        names[j] = malloc(1000 * sizeof(char));
        strcpy(names[j++], tokens[i]);
    }

    return j;

}

char **readStatements(char **statements, FILE *file) {
    char *statement;
    int statementCnt = 0;

    while (fgetc(file) != '{') fgetc(file);

    while (true) {
        //Allocate space for statement
        statement = malloc(sizeof(char) * 1000);
        readStatement(file, statement);
        if (feof(file)) break;   //Check EOF
        statements[statementCnt] = malloc(strlen(statement) * sizeof(char));
        trim(&statement);
        strcpy(statements[statementCnt++], statement);
    }
}

void readStatement(FILE *file, char *resultingStatement) {
    int charCnt = 0;
    int isSingleSpace = false;
    int isParenth = false;
    int is2ndParenth = false;
    char c = 0;

    //skip any whitespaces and newlines
    while (c == ' ' || c == '\t' || c == '\n') c = fgetc(file);

    while (c != ';' || (c == ';' && isParenth)) {
        c = fgetc(file);
        if (feof(file)) return;

        if (c == '(' && !isParenth) {
            isParenth = true;
        } else if (c == '(' && isParenth) {
            is2ndParenth = true;
        } else if (c == ')' && isParenth) {
            isParenth = is2ndParenth;
        }

        //Ignore more than 1 continuous space
        if ((c == ' ' || c == '\t') && isSingleSpace) {
            continue;
        } else if ((c != ' ' && c != '\t'))
            isSingleSpace = false;
        else
            isSingleSpace = true;

        if (c == '}' || c == '\n') continue;    //Skip curly brackets if found
        else if (c == '{') break;    //Mark { as end of statement

        resultingStatement[charCnt++] = c;

    }
    resultingStatement[charCnt] = '\0';
}

void trim(char **string) {
    while (isspace(**string))
        *string = *string + 1;
    for (unsigned long int i = strlen(*string) - 1; isspace(*(*string+i)); --i)
        *(*string+i) = '\0';
}

void tokenizeStatement(char* statement, char** tokens){
    char* temp;
    int tokcnt = 0;
    for(char* i = strtok(statement, " "); i != NULL ; i = strtok(NULL, " ")){
        tokens[tokcnt] = malloc(1000 * sizeof(char));
        temp = malloc(1000 * sizeof(char));
        strcpy(temp, i);
        strcpy(tokens[tokcnt++], temp);
    }
}

void getVariableNames(char **statements, char **variables) {
    char** tokens = makeArray;
    char** names = makeArray;
    char** namesFirst = names;
    do{
        tokenizeStatement(*statements, tokens);
        names = names + getNames(tokens, names);

    }while(*(statements++ + 1) != NULL );

    puts("all names read!");

}


//Binary search to see if token is keyword
int isKeyword( int l, int r, char* x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (strcmp(keywords[mid], x) == 0)
            return true;

        if (strcmp(keywords[mid], x) < 0)
            return isKeyword(l, mid - 1, x);

        return isKeyword(mid + 1, r, x);
    }
    return false;
}

int isValidNameChar(char ch) {
    return (isalnum(ch) || ch == '_')?true:false;
}

int cleanName(char** name){
    int j = 0;
    char* clean = malloc(strlen(*name) * sizeof(char));
    for (int i = 0; i < strlen(*name); ++i) {
        if(isValidNameChar(*(*name+i)))
            clean[j++] = *(*name+i);
    }
    clean[j] = '\0';
    *name = clean;
}

