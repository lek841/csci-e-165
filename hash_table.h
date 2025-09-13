#ifndef CS165_HASH_TABLE 
// This is a header guard. 
// It prevents the header from being included more than once.
#define CS165_HASH_TABLE  

typedef int keyType;
typedef int valType;

typedef struct n_t {
    keyType key;
    valType value;
    struct n_t *next;
} node_t;

typedef int param_t;

typedef struct hashtable {
    // define the components of the hash table here
    // (e.g. the array, bookkeeping for number of elements, etc)
    int elems;
    int slots;
    struct n_t **arr; 
    int (*hash) (keyType, param_t);
} hashtable;

int allocate(hashtable** ht, int size);
int put(hashtable* ht, keyType key, valType value);
int get(
    hashtable* ht, keyType key, valType *values, 
    int num_values, int* num_results);
int erase(hashtable* ht, keyType key);
int deallocate(hashtable* ht);
int hash_modulo(keyType key, param_t param);

#endif

