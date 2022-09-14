#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define TABLESIZE 21

//struct for the user inputs
typedef struct inputs {
    char name[256];
    int key;

} inputs; //end struct

inputs *HashTable[TABLESIZE];

//hash function
int hash(char *name) {
    int hashValue = 0;
    int nameLength = strnlen(name, 256);
    for (int i = 0; i < nameLength; i++) {
        hashValue = (hashValue + name[i]) % TABLESIZE;
    }
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

bool hashInsert(inputs *person) {
    if (person == NULL) {
        printf("NULL POINTER\n");
        return false;
    }
    int index = hash(person->name);


    if (HashTable[index] != NULL) {
        printf("Collision Occured\n");
        return false;
    }

    HashTable[index] = person;
    printf("Stored %s %d at location %d\n", person->name, person->key, index);
    return true;

    
}

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

    //initializes the table
    initializeHashTable();

    inputs jacob ={.name="Jacob", .key=25};
    inputs jackie ={.name="Jackie", .key=45};
    inputs chelsea ={.name="Chelsea", .key=30};

    hashInsert(&jacob);
    hashInsert(&jackie);
    hashInsert(&chelsea);

    printTable();

    return 0;
}
