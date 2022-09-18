#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*********************************
 * HASHTABLE IMPLEMENTATION FOR  *
 * PASS I ASSEMBLY               *
 *				 *
 * Date Due: 9/18/2022		 *
 * By: Vincent Almeda N01473764  *
 ********************************/

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
            //printf("%s found at location %d with a value of %d\n", HashTable[index]->name, index, HashTable[index]->key);
	    printf("ERROR: %s already exists at location %d\n", HashTable[index]->name, index);
            return false;
        } else {
		printf("Collision occured\n");
		return false;
	}	
        return false;
    }

    //if no one is there, it will insert the new person
    HashTable[index] = person;
    printf("Stored %s %d at location %d\n", person->name, person->key, index);
    return true;

} //end hashInsert

inputs *hashSearch (char *nameSearch) {
	int index = hash(nameSearch);
	if (HashTable[index] != NULL && strncmp(HashTable[index]->name, nameSearch, 256) == 0) {
		return HashTable[index];
	} else {
		return NULL;
	} //end if
} //end hashSearch

//prints the table
void printTable() {
    int i;
    for (i = 0; i < TABLESIZE; i++) {
        if (HashTable[i] == NULL) {
            printf("%d\t___\n", i);
        } else {
            printf("%d\t%s\tKEY: %d\n", i, HashTable[i]->name, HashTable[i]->key);
        }
    }

    return;
}


int main(int argc, char *argv[]) {
	
	initializeHashTable();

	char filename[100];
	strcpy(filename, argv[1]);
	
	//printf("name of file: %s\n", filename);

	FILE *inputfile = fopen(filename, "r");
	if (inputfile == NULL) {
		perror("Unable to open the file");
		exit(1);
	} else if (!(argc == 2)) {
		printf("invalid arguments in command line.");
		exit(1);
	}

	//initialization of values for hash insertions and checks
	int inputcount = 0;
	int tempkey;
	char tempLine[256];
	int searchIndex;
	inputs intohash[1000];

	//file traversal
	while (fgets(tempLine, sizeof(tempLine), inputfile)) {
		
		//copies name in file to name in struct inputs
		char *nametoken = strtok(tempLine, " ");
		//printf("current name is: %s\n", nametoken);
		strcpy(intohash[inputcount].name, nametoken);

		//checks if there is a key value, if there is, it will hash into table
		//otherwise, it will search the table for the name
		char *keytoken = strtok(NULL, " ");
		if (!(keytoken == NULL)) {
			tempkey = atoi(keytoken);
			//printf("current key is: %d\n", tempkey);
			intohash[inputcount].key = tempkey;

			hashInsert(&intohash[inputcount]);

		}else{ //need to write else statement for searching
			nametoken[strlen(nametoken) - 2] = '\0';
			searchIndex = hash(nametoken);

			inputs *tmp = hashSearch(nametoken);
			if (tmp == NULL) {
				printf("ERROR %s not found\n", nametoken);
			} else {
				printf("%s found at location %d with a value of %d\n", nametoken, searchIndex, tmp->key);
			}
		}	
		inputcount++;
	} //end while

	fclose(inputfile);
	//printTable();
    return 0;
}
