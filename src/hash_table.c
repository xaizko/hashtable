#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"
#include "prime.h"

#define HT_DEFAULT_SIZE 53
#define HT_PRIME_1 167
#define HT_PRIME_2 199 

static ht_item HT_DELETED_ITEM = {NULL, NULL};

//initialize hash table
ht_hash_table *ht_init() {
   return ht_new_sized(HT_DEFAULT_SIZE); 
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
static int ht_hash(const char *s, const int a, const int m) {
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

//insert into hash table
void ht_insert(ht_hash_table *ht, const char *key, const char *value) {
    const int load = ht->count *100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }

    ht_item *item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item *cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        if(cur_item != &HT_DELETED_ITEM) {
            if (!strcmp(cur_item->key, key)) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

//function to search hash table
char *ht_search(ht_hash_table *ht, const char *key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item != NULL) { 
        if (item != &HT_DELETED_ITEM) {
            if (!strcmp(item->key, key)){
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

//function to delete from hash table
void ht_delete(ht_hash_table *ht, const char *key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }

    int index = ht_get_hash(key, ht->size, 0);
    ht_item *item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (!strcmp(item->key, key)) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

//function to create a new hash table with a specified base size
static ht_hash_table *ht_new_sized(const int base_size) {
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);
    
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

//function to resize the hash table
static void ht_resize(ht_hash_table *ht, const int base_size) {
    if (base_size < HT_DEFAULT_SIZE) {
        return;
    }
    ht_hash_table *new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item *item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table *ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void ht_resize_down(ht_hash_table *ht) {
    const int new_size = ht->base_size /2;
    ht_resize(ht, new_size);
}