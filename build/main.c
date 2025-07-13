#include "hash_table.h"
#include <stdio.h>

int main() {
    // Initialize hash table
    ht_hash_table *ht = ht_init();
    
    // Insert key-value pairs
    ht_insert(ht, "username", "alice123");
    ht_insert(ht, "email", "alice@example.com");
    ht_insert(ht, "role", "admin");
    
    // Search for values
    char *username = ht_search(ht, "username");
    if (username) {
        printf("Username: %s\n", username);
    }
    
    // Check if key exists
    char *role = ht_search(ht, "role");
    if (role) {
        printf("User has role: %s\n", role);
    }
    
    // Delete entries
    ht_delete(ht, "email");
    
    // Always cleanup when done
    ht_del_hash_table(ht);
    return 0;
}