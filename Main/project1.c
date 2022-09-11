#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TABLESIZE 21

//struct for the user inputs
typedef struct inputs {
    char name;
    int key

} inputs; //end struct

inputs *HashTable[TABLESIZE];

//hash function
int hash(char *name, int key) {
    int hashValue = 0;
    hashValue = key % TABLESIZE;
    return hashValue;
} //end hash

//creates the hash table
void initializeHashTable() {
    int i;
    for (i = 0; i < TABLESIZE; i++) {
        HashTable[i] == NULL;
    }

    return;
} //end initializeHashTable

//prints the table
void printTable() {
    int i;
    for (i = 0; i < TABLESIZE; i++) {
        if (HashTable[i] == NULL) {
            printf("%d\t___\n", i);
        } else {
            printf("%d\t%s\n", i, HashTable[i]->name);
        }
    }

    return;
}


int main() {

    //initializes and prints the current table
    initializeHashTable();
    printTable();

    return 0;
}
