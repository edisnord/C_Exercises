//
// Created by Edis Hasaj on 9/20/2022.
//

#ifndef TEST_HASHMAP_H
#define TEST_HASHMAP_H

#include "RBTree.h"
#include "stdlib.h"

typedef struct HashMap HashMap;

typedef struct KvPair {
    void *key;
    void *value;
} KvPair;

const int size_hashmap = 40;

void *getHashMap(HashMap *hashMap, void *value);

KvPair *getHashMapMut(HashMap *hashMap, void *value);

bool insertHashMap(HashMap *hashMap, void *key, void *val, int keyLen, int valLen);

void freeHashMap(HashMap *hashMap);

HashMap *newHashMap(size_t keySize, size_t valSize, comparator comparator);

#endif //TEST_HASHMAP_H
