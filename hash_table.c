#include <stdlib.h>      // malloc(), free()

#include "hash_table.h"

/* purpose: hash function that finds the module of the given
 *          key
 *    args: keyType, key
 *          param_t, slots, array size of the hash table
 *    rets: slot where the head of the linked list is
 *   notes: simple hash function 
 */
int hash_modulo(keyType key, param_t slots) {
    return (key % slots);
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
    
    (*ht)->arr = malloc(size * sizeof(struct n_t *));
  
    if (*ht == NULL) {
        return -1;
    }

    (*ht)->slots = size;
    (*ht)->hash = hash_modulo;

    for (int slot = 0; slot < (*ht)->slots; ++slot) {
        (*ht)->arr[slot] = NULL;
    }
     
    return 0;
}

// This method inserts a key-value pair into the hash table.
// It returns an error code, 0 for success and -1 otherwise 
// (e.g., if malloc is called and fails).
int put(hashtable *ht, keyType key, valType value) {
    
    // Find the appropriate slot.
    int slot = ht->hash(key, ht->slots);

    // Insert node.
    struct n_t *cur, *new;
    
    new = malloc(sizeof(*new));
    if (new == NULL) {
        return -1;
    }
    
    new->key = key;
    new->value = value;
    new->next = NULL;

    if (ht->arr[slot] == NULL) {
        // Empty list.
        ht->arr[slot] = new;
    }
    else {
        // List not empty; insert at head.
        cur = ht->arr[slot];
        ht->arr[slot] = new;    
        new->next = cur;
    }
        
    return 0;
}

// This method retrieves entries with a matching key and stores the 
// corresponding values in the values array. 
// The size of the values array is given by the parameter num_values. 

// If there are more matching entries than num_values, 
// they are not stored in the values array to avoid a buffer overflow. 

// The function returns the number of matching entries using the num_results 
// pointer. 

// If the value of num_results is greater than num_values, the caller can 
// invoke this function again (with a larger buffer) to get values that it 
// missed during the first call. 

// This method returns an error code, 0 for success and -1 otherwise 
// (e.g., if the hashtable is not allocated).

/* purpose: retrieves all values when for the key that matches
 *    args: ht, hashtable ptr
 *          key, value pair
 *          values, ptr to array to store matching values
 *          num_values, the values array can hold this many
 *    rets: num_results, number of values that matched)
 *   notes: when num_results gt num_values, the caller will decide if it wants
 *          a bigger buffer to retrieve all values
 */
int get(
    hashtable* ht, keyType key, valType *values, 
    int num_values, int *num_results
) {
    if (ht == NULL) {
        return -1;
    }

    // Init.
    *num_results = 0;

    // Find the appropriate slot.
    int slot = ht->hash(key, ht->slots);

    // Iterate the list. 
    struct n_t *cur = ht->arr[slot];
    while (cur) {
        if (cur->key == key) {
            // Requested key match.
            if (num_values) {
                // Have space for return values.
                *values = cur->value;
                --num_values;
                ++values;
                ++(*num_results);
            }
            else {
                // Reached return value capacity. 
                ++num_results;
            }
        }
        cur = cur->next; 
    }    
    return 0;
}

// This method erases all key-value pairs with a given key from the 
// hash table.
// It returns an error code, 0 for success and -1 otherwise 
// (e.g., if the hashtable is not allocated).
int erase(hashtable* ht, keyType key) {

    if (ht == NULL) {
        return -1;
    }
   
    int slot = ht->hash(key, ht->slots); 

    struct n_t *cur = ht->arr[slot];
    struct n_t *temp;
    struct n_t *prev = cur;
    
    while (cur) {
        // Found a match.   
        if (key == cur->key) {
            if (prev == cur) {
                // List head.
                if (cur->next == NULL) {
                    free(cur);
                    ht->arr[slot] = NULL;
                    break;
                }
                else {
                    // Copy next
                    cur->key = cur->next->key;
                    cur->value = cur->next->value;
                    temp = cur->next;
                    cur->next = cur->next->next;
                    // Free next
                    free(temp);
                }
            } 
            else {
                // Unlink and free node's memory.
                prev->next = cur->next;
                temp = cur; 
                cur = prev;
                free(temp);
            }
        }
        prev = cur;
        cur = cur->next;
    }
    
    return 0;
}

// This method frees all memory occupied by the hash table.
// It returns an error code, 0 for success and -1 otherwise.
int deallocate(hashtable* ht) {
    struct n_t *cur, *prev;
    for (int slot = 0; slot < ht->slots; ++slot) {
        if (ht->arr[slot] != NULL) {
            cur = ht->arr[slot];
            while (cur) {
                prev = cur;                
                cur = cur->next;
                free(prev);
            }
        }
    }
    free(ht->arr);
    free(ht);
    return 0;
}
