//Key value pair structure for the hash table
typedef struct {
    char *key; 
    char *value;
} ht_item;

typedef struct {
    int size; 
    int count;
    int base_size;
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
static int ht_hash(const char *s, const int a, const int m);

//function to double hash to avoid collision
static int ht_get_hash(const char *s, int num_buckets, const int attempt);

//function to insert into hash table
void ht_insert(ht_hash_table *ht, const char *key, const char *value);

//function to search hash table
char *ht_search(ht_hash_table *ht, const char *key);

//function to delete from hash table
void ht_delete(ht_hash_table *ht, const char *key);

//function to create a new hash table with a specified base size
static ht_hash_table *ht_new_sized(const int base_size);

//function to resize the hash table
static void ht_resize(ht_hash_table *ht, const int base_size);

//function to resize the hash table when it grows
static void ht_resize_up(ht_hash_table *ht);


//function to resize the hash table when it shrinks
static void ht_resize_down(ht_hash_table *ht);