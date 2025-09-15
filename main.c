#include <stdlib.h>      // malloc()
#include <stdio.h>       // 

#include "hash_table.h"


int menu(void);

// This is where you can implement your own tests for the hash table
// implementation. 
int main(void) {

//    menu();
//    return 0;

  hashtable *ht = NULL;
  int size = 10;
  allocate(&ht, size);

  int key = 0;
  int value = -1;

  put(ht, key, value);
  put(ht, 1, -2);
  put(ht, 11, -3);
  put(ht, 1, -4);

  erase(ht, 1);

  int num_values = 2;

  valType* values = malloc(2 * sizeof(valType));

  int *num_results = NULL;
  num_results = malloc(sizeof(int));

  key = 1;
  get(ht, key, values, num_values, num_results);
  if ((*num_results) > num_values) {
    values = realloc(values, (*num_results) * sizeof(valType));
    get(ht, 0, values, num_values, num_results);
  }

  for (int i = 0; i < (*num_results); i++) {
    printf("value of %d is %d \n", i, values[i]);
  }
  free(values);

  erase(ht, 0);

  free(num_results);
  deallocate(ht);
  return 0;
}

int menu(void) {

    hashtable *ht = NULL;
    int size = 10;
    allocate(&ht, size);

    fprintf(stdout, "Hash table allocated.\n");
    
    int key, value, status;   // Assume that both are integers.
    char opt; 
    fprintf(stdout, "p: put K V, g: get K, e: erase K, q: quit\n");
    while ((opt = getchar()) != 'q') {
        if (opt == 'p') {
            // Put.
            scanf(" %d %d", &key, &value);
            status = put(ht, (keyType) key, (valType) value);
            if (0 == status) {
                fprintf(stdout, "Put key %d, value %d in hash table.\n", 
                    key, value);
            }
            else {
                fprintf(stdout, "Put operation returned error.\n");
            }
        }
        else if (opt == 'e') {
            // Erase.
           scanf(" %d", &key);
           status = erase(ht, key);
           if (0 == status) {
               fprintf(stdout, "Erase values with key %d\n", key);
           } 
           else {
               fprintf(stdout, "Erase operation returned error.\n");
           }              
        }
        else if (opt == 'd') {
            // Display hash table.
            for (int i = 0; i < ht->slots; ++i) {
                struct n_t *cur = ht->arr[i];
                fprintf(stdout, "Slot %d : ", i);
                while (cur) {
                    fprintf(stdout, "(%d, %d) | ", cur->key, cur->value); 
                    cur = cur->next;
                }
                fputc('\n', stdout); 
            }
        }
    }
    return 0;
}
