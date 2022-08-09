#include <ctype.h>
#include "chapter6.h"

char keywords[14][8] = {"auto", "char", "const", "double", "enum", "float", "int", "long",
                        "register", "restrict", "short",
                        "static", "void", "volatile"};

void parseDecl(char *filepath, int chars) {
    char **statements = makeArray;
    char **names = makeArray;
    FILE *file = fopen(filepath, "r");

    if (file == NULL)
        return;

    readStatements(statements, file);
    puts("File read completely!");
    long numberOfNames = getVariableNames(statements, &names);
    sortNamesAscending(&names, (int) numberOfNames);
    puts("names sorted");
    seeMatching(names, (int) numberOfNames, chars);
}

int getNames(char **tokens, char **names) {
    int i;
    int j;
    for (i = 0; tokens[i] != NULL; ++i) {
        if (!isKeyword(0, 13, tokens[i])) {
            if (i == 0)
                return 0;
            else
                break;
        }
        free(tokens[i]);
    }

    for (j = 0; tokens[i] != NULL; ++i) {
        if (!strcmp(*(tokens + i), "=")) break;
        if (cleanName(tokens + i)) {
            if (strlen(*(tokens + i)) == 0) continue;
            names[j] = malloc(1000 * sizeof(char));
            strcpy(names[j++], tokens[i]);
        } else {
            break;
        }
        free(tokens[i]);
    }

    return j;

}

char **readStatements(char **statements, FILE *file) {
    char *statement;
    int statementCnt = 0;
    char c;

    while (fgetc(file) != '{');

    while (true) {
        //Allocate space for statement
        statement = malloc(sizeof(char) * 1000);
        readStatement(file, statement);
        if (feof(file)) break;   //Check EOF
        if (statement[0] == '\0') continue;
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
    int isString = false;
    int isComment = false;
    int slashCnt = 0;
    char c = 0;

    //skip any whitespaces and newlines
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0') c = fgetc(file);
    ungetc(c, file);

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

        if (c == '"') {
            isString = !isString;
        }

        if (c == '/' && !isString) {
            slashCnt++;
        }

        if (slashCnt == 2) {
            resultingStatement[0] = '\0';
            while (fgetc(file) != '\n');
            break; //Comment in the beginning indicates lack of statement
        }

        resultingStatement[charCnt++] = c;
    }
    resultingStatement[charCnt] = '\0';
}

void trim(char **string) {
    while (isspace(**string))
        *string = *string + 1;
    for (unsigned long int i = strlen(*string) - 1; isspace(*(*string + i)); --i)
        *(*string + i) = '\0';
}

void tokenizeStatement(char *statement, char **tokens) {
    char *temp;
    int tokcnt = 0;
    for (char *i = strtok(statement, " "); i != NULL; i = strtok(NULL, " ")) {
        tokens[tokcnt] = malloc(1000 * sizeof(char));
        temp = malloc(1000 * sizeof(char));
        strcpy(temp, i);
        strcpy(tokens[tokcnt++], temp);
    }
    tokens[tokcnt] = NULL;
}

long getVariableNames(char **statements, char ***names) {
    char **tokens = makeArray;
    char **namesInc = *names;

    do {
        tokenizeStatement(*statements, tokens);
        namesInc = namesInc + getNames(tokens, namesInc);
        free(tokens);
        tokens = makeArray;
    } while (*(statements++ + 1) != NULL);

    puts("all names read!");

    return namesInc - *names;
}


//Binary search to see if token is keyword
int isKeyword(int l, int r, char *x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        cleanName(&x);

        if (strcmp(x, keywords[mid]) == 0)
            return true;

        if (strcmp(x, keywords[mid]) < 0)
            return isKeyword(l, mid - 1, x);

        return isKeyword(mid + 1, r, x);
    }
    return false;
}

int isValidNameChar(char ch) {
    return (isalnum(ch) || ch == '_') ? true : false;
}

int cleanName(char **name) {
    int j = 0;
    char *clean = malloc(strlen(*name) * sizeof(char));
    for (int i = 0; i < strlen(*name); ++i) {
        if (isValidNameChar(*(*name + i)))
            clean[j++] = *(*name + i);
        else if (*(*name + i) == '(' && (i != 0 || *(*name + i - 1) != '*'))
            return 0;
        else if (*(*name + i) == '[')
            break;
    }
    clean[j] = '\0';
    *name = clean;
    return 1;
}

void seeMatching(char **names, int num, int matching) {
    char **finalnames = makeArray;






//    int index = 0;
//    for (int i = 0; i < matching; i++) {
//        struct charCount {
//            char character;
//            int count;
//        } cnt;
//        cnt.character = names[i][0];
//        for (int j = 0; j < num; j++) {
//            if (names[j][i] == cnt.character) {
//                cnt.count++;
//            } else {
//                if (cnt.count > 1 &&
//                        ( finalnames[index - 1][i - i ? 1 : 0] == names[j][i - i ? 1 : 0] || index == 0 ) )
//                    finalnames[index++] = names[j - 1];
//                cnt.count = 1;
//                cnt.character = names[j][i];
//            }
//        }
//        if (cnt.count == 1) names[num - 1][0] = '\0';
//
//        memcpy(names, finalnames, (index + 1) * sizeof(char **));
//        memset(finalnames, 0, (index + 1) * sizeof(char **));
//        num = index;
//        index = 0;
//
//    }
//    for (int j = 0; j < num; j++) puts(finalnames[j]);

}

void sortNamesAscending(char ***names, int num) {
    qsort(*names, num, sizeof(char *), comparator);
}

int comparator(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}