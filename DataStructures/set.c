//
// Created by Edis Hasaj on 7/26/2022.
//

#include "set.h"

node *getSetRoot(set *set);

void freeSet(set *set) {
    freeTree(set->tree);
    free(set->tree);
    free(set);
}

set *newSet(comparator comparator, unsigned long valSize) {
    set *set = malloc(sizeof(struct set));
    *set = (struct set) { 0,
                     (struct set_vtable) {insertSet, searchSet, freeSet},
                     newRBTree(comparator, valSize)};
    return set;
}

int insertSet(set *set, void *val, unsigned long sizeOfDatatype, int arrLen) {
    return insertRBTree(set->tree, val, arrLen);
}

int searchSet(set *set, void *value) {
    return searchRBTree(set->tree, value);
}
