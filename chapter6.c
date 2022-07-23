#include "chapter6.h"

char keywords[16][8] = {"char", "int", "long", "short", "const",
                        "enum", "auto", "volatile", "restrict", "float",
                        "double", "register", "static"};

void parseDecl(char *filepath, int chars) {
    char** statements = malloc(sizeof (char*) * 10000);
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
        return;

    readStatements(statements, file);

    puts("File read completely!");

}

char **readStatements(char **statements, FILE *file) {
    char *statement;
    int statementCnt = 0;

    while (fgetc(file) != '{') fgetc(file);

    while(true){
        //Allocate space for statement
        statement = malloc(sizeof(char) * 1000);
        readStatement(file, statement);
        if(feof(file)) break;   //Check EOF
        statements[statementCnt] = malloc(strlen(statement) * sizeof(char ));
        strcpy(statements[statementCnt++], statement);
        //Deallocate space for statement
        free(statement);
    }
}

void readStatement(FILE *file, char *resultingStatement) {
    int charCnt = 0;
    int isSingleSpace = false;
    char c;

    //skip any whitespaces and newlines
    while (c == ' ' || c == '\t' || c == '\n') c = fgetc(file);

    while (c != ';') {
        c = fgetc(file);
        if(feof(file)) return;

        //Ignore more than 1 continuous space
        if ((c == ' ' || c == '\t') && isSingleSpace) {
            continue;
        } else if ((c != ' ' && c != '\t'))
            isSingleSpace = false;
        else
            isSingleSpace = true;

        if (c == '{' || c == '}' || c == '\n') continue;  //Skip curly brackets if found

        resultingStatement[charCnt++] = c;

    }
    resultingStatement[charCnt] = '\0';
}

//void readStatement(FILE *file, char **resultingStatements) {
//    char *line = malloc(sizeof(char) * 1000);
//    char *lineStart = line;
//    char *resultingStatement = NULL;
//    int isSingleSpace = false;
//    int statementcnt = 0;
//    char c;
//    while (!feof(file)) {
//        while (fgetc(file) != '{');
//        c = fgetc(file);
//        while (c == ' ' || c == '\t' || c == '\n')
//            c = fgetc(file);
//        ungetc(c, file);
//        line = malloc(sizeof(char) * 1000);
//        lineStart = line;
//        for (c = fgetc(file); c != ';';) {
//            if ((c == ' ' || c == '\t') && isSingleSpace) {
//                continue;
//            } else if ((c != ' ' && c != '\t'))
//                isSingleSpace = false;
//            else
//                isSingleSpace = true;
//            *line++ = c;
//            resultingStatement =
//                    realloc(resultingStatement, (1 + line - lineStart) * sizeof(char));
//            resultingStatement[line - lineStart - 1] = c;
//            c = fgetc(file);
//        }
//        *(resultingStatement + (++line - lineStart)) = '\0';
//        char *placeHolderString = malloc(sizeof(char) * strlen(resultingStatement));
//        strcpy(placeHolderString, resultingStatement);
//        resultingStatements = realloc(resultingStatements, ++statementcnt * sizeof(char *));
//        resultingStatements[statementcnt - 1] = placeHolderString;
//        puts("Statement Parsed!");
//        free(resultingStatement);
//        resultingStatement = NULL;
//    }
//    puts("file read!");
//}