//
// Created by Edis Hasaj on 9/20/2022.
//

#ifndef TEST_HASHMAP_H
#define TEST_HASHMAP_H

#include "RBTree.h"
#include "stdlib.h"

typedef struct hashMap hashMap;

typedef struct kvPair kvPair;

int insertHashMap(hashMap *hashMap, void *val);

void * getHashMap(hashMap* hashMap, void *value);

void freeHashMap(hashMap *hashMap);

hashMap *newHashMap(size_t keySize, size_t valSize, comparator comparator);

#endif //TEST_HASHMAP_H
