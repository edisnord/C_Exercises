//
// Created by edish on 22-09-23.
//

#include "chapter_6-3&4.h"

#define BUF_LEN 1000


void countWords(HashMap* map, char* line, int lineCnt);

void printCount(HashMap* map);

void wordOccurrences(const char *filePath) {
    int lineCnt = 0;
    const size_t buflen = BUF_LEN;
    FILE *file = fopen(filePath, "r");
    HashMap *map = newHashMap(sizeof(char), SIZE_OF_DLL, (comparator) strcmp);

    if (file == NULL) {
        perror("wordOccurrences");
        return;
    }

    do {
        char *line = malloc(BUF_LEN * sizeof(char));
        getline(&line, (size_t *) buflen, file);
        if (!feof(file))
            lineCnt++;
        else break;
        countWords(map, line, lineCnt);
    } while (true);

    printCount(map);
}

void countWords(HashMap *map, char *line, int lineCnt) {
    for (char *i = strtok(line, " "); i != NULL; i = strtok(NULL, " ")) {
        if(strcmp(i, "and") == 0 || strcmp(i, "so") == 0 || strcmp(i, "the,") == 0)
            continue;
        size_t wordLength = strlen(i);
        if (i[wordLength - 1] == '\n')
            i[wordLength-- - 1] = '\0';
        KvPair *kv = getHashMapMut(map, i);
        if (kv == NULL) {
            DoublyLinkedList *val = newDLL(sizeof(char), (comparator) strcmp);
            appendDLL(val, i, wordLength + 1);
            insertHashMap(map, i, &lineCnt, (int) wordLength + 1, 1);
        } else {
            appendDLL((DoublyLinkedList *) kv->value, i, wordLength + 1);
        }
        free(i);
    }
}

void printCount(HashMap *map) {
    DoublyLinkedList *list = flattenHashMap(map);
    int listLen = lengthDLL(list);

    for (int i = 0; i < listLen; ++i) {
        DoublyLinkedList *element = ((KvPair *)getDLL(list, i))->value;
        char* word = ((KvPair *)getDLL(list, i))->key;
        printf("Word: %s, Lines occurred: ", word);
            for (int j = 0; j < lengthDLL(element); ++j) {
                printf("%d ", *(int*)getDLL(list, j));
            }
        putc('\n', stdout);
    }
}
