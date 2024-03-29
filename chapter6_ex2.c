#include <ctype.h>
#include "chapter6_ex2.h"
#include "chapter6_util.h"

char keywords[14][8] = {"auto", "char", "const", "double", "enum", "float", "int", "long",
                        "register", "restrict", "short",
                        "static", "void", "volatile"};

void parseDecl(char *filepath, int chars) {
    char **statements = makeArray;
    char **names = makeArray;
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        perror("parseDecl");
        return;
    }

    readStatements(statements, file);
    puts("File read completely!");
    long numberOfNames = getVariableNames(statements, &names);
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
            names[j] = malloc(50 * sizeof(char));
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
        statement = malloc(sizeof(char) * 300);
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

void tokenizeStatement(char *statement, char **tokens) {
    char *temp;
    int tokcnt = 0;
    for (char *i = strtok(statement, " "); i != NULL; i = strtok(NULL, " ")) {
        tokens[tokcnt] = malloc(30 * sizeof(char));
        temp = malloc((strlen(i)+1) * sizeof(char));
        strcpy(temp, i);
        strcpy(tokens[tokcnt++], temp);
        free(temp);
    }
    tokens[tokcnt] = NULL;
}

long getVariableNames(char **statements, char ***names) {
    char **tokens = malloc(sizeof(char *) * 100);
    char **namesInc = *names;

    do {
        tokenizeStatement(*statements, tokens);
        namesInc = namesInc + getNames(tokens, namesInc);
        free(tokens);
        tokens = malloc(sizeof(char *) * 200);
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

//Keys are strings in this case so strcmp should suffice
int comparatorKey(const void *first, const void *next) {
    KvPair *key1 = (KvPair *) first;
    KvPair *key2 = (KvPair *) next;

    return strcmp(key1->key, key2->key);
}

//Hashmap 1 has { substrings : DLL}
//Hashmap 2 has { DLL of names }
void seeMatching(char **names, int num, int matching) {
    HashMap *hashMap = newHashMap(sizeof(char), SIZE_OF_DLL, comparatorKey);

    for (int i = 0; i < num; ++i) {
        char *substr = substring(names[i], 0, matching - 1);
        KvPair *kv = getHashMapMut(hashMap, substr);
        if (kv == NULL) {
            DoublyLinkedList *val = newDLL(sizeof(char), (comparator) strcmp);
            appendDLL(val, names[i], strlen(names[i]));
            insertHashMap(hashMap, substr, val, (int) strlen(substr), 1);
        } else {
            appendDLL((DoublyLinkedList *) kv->value, names[i], strlen(names[i]));
        }
        free(substr);
        free(names[i]);
    }
    free(names);

    DoublyLinkedList *list = flattenHashMap(hashMap);
    int listLen = lengthDLL(list);

    for (int i = 0; i < listLen; ++i) {
        DoublyLinkedList *element = ((KvPair *)getDLL(list, i))->value;
        char* value = getDLL(element,0);
        if (lengthDLL(element) > 1) {
            for (int j = 0; j < lengthDLL(element); ++j)
                puts(getDLL(element, j));
        }
    }

}
