# 🗂️ Hash Table Library

A lightweight and efficient hash table utility library for C projects, featuring dynamic resizing and collision resolution through double hashing.

## 📋 Features

- ✨ **Dynamic Resizing**: Automatically resizes when load factor exceeds 70% or drops below 10%
- 🔧 **Collision Resolution**: Uses double hashing for efficient collision handling
- 🔍 **Fast Lookup**: O(1) average time complexity for insert, search, and delete operations
- 🧮 **Prime Number Sizing**: Uses prime numbers for optimal hash distribution
- 🗑️ **Memory Management**: Proper cleanup and deletion handling
- 📦 **Lightweight**: Minimal dependencies, easy to integrate

## 📁 Library Files

```
src/
├── hash_table.h    # Main header file - include this in your project
├── hash_table.c    # Core hash table implementation
├── prime.h         # Prime number utilities header
└── prime.c         # Prime number utilities implementation
```

## 🚀 Integration

### Including in Your Project

1. Copy the source files to your project directory
2. Include the header in your C files:

```c
#include "hash_table.h"
```

3. Compile with your project:

```bash
gcc your_program.c hash_table.c prime.c -o your_program
```

## 📚 API Reference

### 🏗️ Initialization
```c
ht_hash_table *ht = ht_init();  // Create new hash table
```

### ➕ Insert
```c
ht_insert(ht, "key", "value");  // Insert key-value pair
```

### 🔍 Search
```c
char *value = ht_search(ht, "key");  // Returns value or NULL
```

### ❌ Delete
```c
ht_delete(ht, "key");  // Remove key-value pair
```

### 🗑️ Cleanup
```c
ht_del_hash_table(ht);  // Free memory
```

## ⚡ Performance

- **Load Factor**: Maintains optimal performance by keeping load factor between 10-70%
- **Hash Function**: Uses polynomial rolling hash with prime multipliers
- **Collision Resolution**: Double hashing minimizes clustering

## 🛠️ Implementation Details

- **Default Size**: 53 (prime number)
- **Hash Primes**: 167 and 199 for double hashing
- **Resize Factor**: 2x up, 0.5x down
- **Memory Safety**: Proper allocation and deallocation

## 📝 Usage Examples

### Basic Operations

```c
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
```

### Advanced Usage

```c
// Using hash table for configuration storage
ht_hash_table *config = ht_init();

// Store configuration values
ht_insert(config, "max_connections", "100");
ht_insert(config, "timeout", "30");
ht_insert(config, "debug_mode", "true");

// Retrieve and use values
char *max_conn = ht_search(config, "max_connections");
int max_connections = max_conn ? atoi(max_conn) : 50; // default fallback

// Cleanup
ht_del_hash_table(config);
```

## ⚠️ Important Notes

- **Memory Management**: Always call `ht_del_hash_table()` to prevent memory leaks
- **String Handling**: The library stores copies of keys and values, so original strings can be safely modified
- **Thread Safety**: This implementation is not thread-safe; use external synchronization if needed
- **Null Handling**: Functions gracefully handle NULL inputs but always check return values

## 🔧 Customization

The library uses default prime numbers and sizing strategies that work well for most use cases. To customize:

- Modify `HT_INITIAL_BASE_SIZE` in `hash_table.h` for different initial sizes
- Adjust load factor thresholds in the resize logic
- Replace hash functions for specialized use cases

## �️ Requirements

- **C Standard**: C99 or later
- **Dependencies**: Standard library only (`stdlib.h`, `string.h`, `math.h`)
- **Platform**: Cross-platform compatible

## 📄 License

This hash table library is provided as-is for educational and commercial use.

---

💡 **Tip**: This library is perfect for caching, configuration management, symbol tables, and any scenario requiring fast key-value lookups in C projects.
