#include <stdio.h>
#include <string.h>
#include "hash_table.h"

#define HT_DEFAULT_SIZE 53

//initialize hash table
ht_hash_table *ht_init() {
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));

    ht->size = HT_DEFAULT_SIZE;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    
    return ht;
}

//add item to hash table
static ht_item *ht_add_item(const char *k, const char *v) {
    ht_item *i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

//remove item from hash table
static void ht_del_item(ht_item *i) {
    free(i->key);
    free(i->value); 
    free(i);
}

