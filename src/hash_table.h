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

//function to delete hash table
void ht_del_hash_table(ht_hash_table *ht);

//function to add item to hash table
static ht_item *ht_new_item(const char *k, const char *v);

//function to remove item from hash table
static void ht_del_item(ht_item *i);

//function to hash
static int ht_hash(char *s, const int a, const int m);

//function to double hash to avoid collision
static int ht_get_hash(const char *s, int num_buckets, const int attempt);

//function to insert into hash table
void ht_insert(ht_hash_table *ht, const char *key, const char *value);