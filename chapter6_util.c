//
// Created by edish on 22-09-19.
//

#include "chapter6_util.h"

void trim(char **string) {
    while (isspace(**string))
        *string = *string + 1;
    for (unsigned long int i = strlen(*string) - 1; isspace(*(*string + i)); --i)
        *(*string + i) = '\0';
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
    strcpy(*name, clean);
    free(clean);
    return 1;
}

char *substring(char *string, int start, int end) {
    if (end >= strlen(string) || end < 0) {
        puts("substring: end parameter out of bounds");
        end = strlen(string) - 1;
    } else if (start >= strlen(string) || start < 0) {
        puts("substring: start parameter out of bounds");
        return NULL;
    } else if (string == NULL) {
        puts("substring: string reference is null");
        return NULL;
    }

    char *finalString = malloc((end - start + 1) * sizeof(char));
    strncpy(finalString, string + start, end - start + 1);
    finalString[end+1] = '\0';
    return finalString;
}

void sortNamesAscending(char ***names, int num) {
    qsort(*names, num, sizeof(char *), utilComparator);
}

int utilComparator(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}