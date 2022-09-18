#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLESIZE 101

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
    //checks if there is no input
    if (person == NULL) {
        printf("NULL POINTER\n");
        return false;
    }
    int index = hash(person->name);
    
    //checks if the person already exists
    if ((HashTable[index] != NULL)) {
        if ((strncmp(HashTable[index]->name, person->name, 256) == 0)) {
            printf("%s found at location %d with a value of %d\n", HashTable[index]->name, index, HashTable[index]->key);
            return false;
        } 
        return false;
    }

    //if no one is there, it will insert the new person
    HashTable[index] = person;
    printf("Stored %s %d at location %d\n", person->name, person->key, index);
    return true;

} //end hashInsert

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
    inputs jacob2 = {.name="Jacob"};

    hashInsert(&jacob);
    hashInsert(&jackie);
    hashInsert(&chelsea);
    hashInsert(&jacob2);

    //printTable();

    return 0;
}
