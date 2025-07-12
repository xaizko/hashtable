#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define HT_DEFAULT_SIZE 53
#define HT_PRIME_1 167
#define HT_PRIME_2 199 

//initialize hash table
ht_hash_table *ht_init() {
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));

    ht->size = HT_DEFAULT_SIZE;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    
    return ht;
}

//add item to hash table
static ht_item *ht_new_item(const char *k, const char *v) {
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

//delete hash table
void ht_del_hash_table(ht_hash_table *ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item *item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }

    free(ht->items);
    free(ht);
}

//hashing function
/*
s is the string, a is a prime number larger than the size of the alphabet
m is the desired bucket array length
*/
static int ht_hash(char *s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

//function to get hash
static int ht_get_hash(const char *s, int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}