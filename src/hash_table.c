#include <stdio.h>
#include <string.h>
#include "hash_table.h"

static ht_item *ht_add_item(const char *k, const char *v) {
    ht_item *i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}