#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    int n;
    int (*hashFunc)(int, int);
    Entry* table;
} HashTable;

int mi_Mod(int x, int n) {
    return x % n;
}

int randomFn(int x, int n) {
    return rand() % n;
}

HashTable* createHashTable(int n, int (*hashFunc)(int, int)) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->n = n;
    ht->hashFunc = hashFunc;
    ht->table = (Entry*)malloc(n * sizeof(Entry));
    for (int i = 0; i < n; ++i) {
        ht->table[i].key = -1; 
    }
    return ht;
}

void insert(HashTable* ht, int key, int value) {
    int index = ht->hashFunc(key, ht->n);
    while (ht->table[index].key != -1) {
        index = (index + 1) % ht->n; 
    }
    ht->table[index].key = key;
    ht->table[index].value = value;
}

int find(HashTable* ht, int key) {
    int index = ht->hashFunc(key, ht->n);
    while (ht->table[index].key != -1) {
        if (ht->table[index].key == key) {
            return ht->table[index].value;
        }
        index = (index + 1) % ht->n;
    }
    return -1; 
}

void delete(HashTable* ht, int key) {
    int index = ht->hashFunc(key, ht->n);
    while (ht->table[index].key != -1) {
        if (ht->table[index].key == key) {
            ht->table[index].key = -1;
            ht->table[index].value = -1; 
            return;
        }
        index = (index + 1) % ht->n;
    }
}

int main() {
    srand(42); 

    HashTable* ht1 = createHashTable(10, mi_Mod);
    insert(ht1, 52, 1234567);
    printf("Found key 52: %d\n", find(ht1, 52)); 
    delete(ht1, 52);
    printf("Found key 52 after deletion: %d\n", find(ht1, 52)); 

    HashTable* ht2 = createHashTable(10, randomFn);
    insert(ht2, 52, 123);
    printf("Found key 52: %d\n", find(ht2, 52)); 

    free(ht1->table);
    free(ht1);
    free(ht2->table);
    free(ht2);

    return 0;
}