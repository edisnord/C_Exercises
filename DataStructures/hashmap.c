//
// Created by Edis Hasaj on 9/20/2022.
//

#include <memory.h>
#include "hashmap.h"
#include "DoublyLinkedList.h"

struct kvPair {
    void* key;
    void* value;
};



struct hashMap {
    rbTree* tree;
    int count;
    size_t valSize;
    size_t keySize;
};

kvPair* newKeyValuePair(hashMap *map, void* key, void* value, int keyLen, int valLen ){
    kvPair* pair = malloc(sizeof(kvPair));
    pair->key = malloc(map->keySize * keyLen);
    memcpy(pair->key, key, map->keySize * keyLen);
    pair->value = malloc(map->valSize * keyLen);
    memcpy(pair->value, value, map->valSize * valLen);
    return pair;
}

int insertHashMap(hashMap *hashMap, void *val) {
    return 0;
}

void * getHashMap(hashMap *hashMap, void *value) {
    return NULL;
}

void freeHashMap(hashMap *hashMap) {
    freeTree(hashMap->tree);

}

hashMap *newHashMap(size_t keySize, size_t valSize, comparator comparator) {
    return NULL;
}
