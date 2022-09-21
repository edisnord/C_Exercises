//
// Created by Edis Hasaj on 9/20/2022.
//

#include <memory.h>
#include "hashmap.h"
#include "DoublyLinkedList.h"

struct HashMap {
    rbTree *tree;
    int count;
    size_t valSize;
    size_t keySize;
    DoublyLinkedList *KVlist;
};

KvPair *newKeyValuePair(HashMap *map, void *key, void *value, int keyLen, int valLen) {
    KvPair *pair = malloc(sizeof(KvPair));
    pair->key = malloc(map->keySize * keyLen);
    memcpy(pair->key, key, map->keySize * keyLen);
    pair->value = malloc(map->valSize * keyLen);
    memcpy(pair->value, value, map->valSize * valLen);
    return pair;
}

bool insertHashMap(HashMap *hashMap, void *key, void *val, int keyLen, int valLen) {
    KvPair *keyval = newKeyValuePair(hashMap, key, val, keyLen, valLen);
    appendDLL(hashMap->KVlist, keyval, 1);
    return insertRBTree(hashMap->tree, keyval, 1);
}

void *getHashMap(HashMap *hashMap, void *value) {
    KvPair *pair = getRBTree(hashMap->tree, value);
    return pair->value;
}

KvPair *getHashMapMut(HashMap *hashMap, void *value) {
    KvPair *pair = getRBTree(hashMap->tree, value);
    return pair;
}

void freeHashMap(HashMap *hashMap) {
    freeRBTree(hashMap->tree);
    freeDLL(hashMap->KVlist);
    free(hashMap);
}

HashMap *newHashMap(size_t keySize, size_t valSize, comparator comparator) {
    HashMap *hm = malloc(sizeof(HashMap));
    int (*doesntCompareShit)(const void *, const void *) = NULL;
    *hm = (struct HashMap) {
            newRBTree(comparator, keySize),
            0,
            valSize,
            keySize,
            newDLL(sizeof(KvPair), doesntCompareShit)};
    return hm;
}
