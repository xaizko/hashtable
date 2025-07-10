//Key value pair structure for the hash table
typedef struct {
    char *key; 
    char *value;
} ht_item;

typedef struct {
    int size; 
    int count;
    ht_item **items;
} ht_hash_table;

//function to initialize hash table
ht_hash_table *ht_init();

//function to add item to hash table
static ht_item *ht_add_item(const char *k, const char *v);