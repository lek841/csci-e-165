#include <stdlib.h>      // malloc()

#include "hash_table.h"

/* purpose: hash function that finds the module of the given
 *          key
 *    args: keyType, key
 *          param_t, slots, array size of the hash table
 *    rets: slot where the head of the linked list is
 *   notes: simple hash function 
 */
int hash_modulo(keyType key, param_t slots) {
    return (key % (slots -1 ));
}

// Initialize the components of a hashtable.
// The size parameter is the expected number of elements to be inserted.
// This method returns an error code, 0 for success and -1 otherwise
// (e.g., if the parameter passed to the method is not null, if malloc 
// fails, etc).
int allocate(hashtable** ht, int size) {

    if (*ht != NULL) {
        return -1;
    }

    *ht = malloc(sizeof(**ht));
    if (*ht == NULL) {
        return -1;
    }
    
    (*ht)->arr = malloc(size * sizeof(struct n_t));
  
    if (*ht == NULL) {
        return -1;
    }

    (*ht)->slots = size;
    (*ht)->hash = hash_modulo;
     
    return 0;
}

// This method inserts a key-value pair into the hash table.
// It returns an error code, 0 for success and -1 otherwise 
// (e.g., if malloc is called and fails).
int put(hashtable* ht, keyType key, valType value) {
    
    // Find the appropriate slot.
    int slot = ht->hash(key, ht->slots);

    // Insert the node.
    struct n_t *cur;
    if (ht->arr[slot].next == NULL) {
        // Empty list.
        ht->arr[slot].key = key;
        ht->arr[slot].value = value;
        ht->arr[slot].next = NULL;
    }
    else {
        cur = &ht->arr[slot];  
        ht->arr[slot].key = key;
        ht->arr[slot].value = value;
        ht->arr[slot].next = cur;
    }
        
    return 0;
}

// This method retrieves entries with a matching key and stores the 
// corresponding values in the
// values array. The size of the values array is given by the parameter
// num_values. If there are more matching entries than num_values, 
// they are not
// stored in the values array to avoid a buffer overflow. 
// The function returns
// the number of matching entries using the num_results pointer. 
// If the value of num_results is greater than
// num_values, the caller can invoke this function again 
// (with a larger buffer)
// to get values that it missed during the first call. 
// This method returns an error code, 0 for success and -1 otherwise 
// (e.g., if the hashtable is not allocated).
int get(
    hashtable* ht, keyType key, valType *values, 
    int num_values, int* num_results
) {
    (void) ht;
    (void) key;
    (void) values;
    (void) num_values;
    (void) num_results;
    return 0;
}

// This method erases all key-value pairs with a given key from the 
// hash table.
// It returns an error code, 0 for success and -1 otherwise 
// (e.g., if the hashtable is not allocated).
int erase(hashtable* ht, keyType key) {
    (void) ht;
    (void) key;
    return 0;
}

// This method frees all memory occupied by the hash table.
// It returns an error code, 0 for success and -1 otherwise.
int deallocate(hashtable* ht) {
    // This line tells the compiler that we know we haven't used the 
    // variable
    // yet so don't issue a warning. You should remove this line once 
    // you use
    // the parameter.
    (void) ht;
    return 0;
}
