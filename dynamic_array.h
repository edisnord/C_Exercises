
#ifndef TEST_DYNAMIC_ARRAY_H
#define TEST_DYNAMIC_ARRAY_H

struct arrayList {
    char* array;
    int length;
    void (*add) (char*, char, int*);
};

char* create_space();
char removeLast(char* arr, int* lenLoc);
void addAndReallocate(char* arr, char new, int*);
void clear(char* clear);
#endif //TEST_DYNAMIC_ARRAY_H
