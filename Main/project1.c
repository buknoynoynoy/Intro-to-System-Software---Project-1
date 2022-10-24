#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*********************************
 * HASHTABLE IMPLEMENTATION FOR  *
 * PASS I ASSEMBLY               *
 *				     			 *
 * Date Due: 9/18/2022			 *
 * By: Vincent Almeda N01473764  *
 ********************************/

#define TABLESIZE 101

//struct for the user inputs
typedef struct inputs {
    char name[256];
	char nameTwo[256];
	char nameThree[256];
    int key;

} inputs; //end struct

//struct for opcode
typedef struct opcode {
	char name[256];
	int value;
} opcode;

opcode opcodes[256] = {
	{"+LDB",0x68}, {"MULR",0x98}, {"+SSK",0xEC}, 
	{"WD",0xDC}, {"*STK",0x10}, {"*OR",0x44},
	{"AND",0x40}, {"*LDA",0x00}, {"+JGT",0x34},
	{"+STL",0x14}, {"*WD",0xDC}, {"+STI",0xD4},
	{"LPS",0xD0}, {"+LDT",0x74}, {"*LDCH",0x50},
	{"*LDL",0x08}, {"TIXR",0xB8}, {"SUBF",0x5C},
	{"STA",0x0C}, {"LDA",0x00}
};

typedef struct address {
	int start;
	int current;
	int final;
} address;

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
        HashTable[i] = NULL;
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
	for (int i = 0; i < TABLESIZE; i++) {
		int try = (i + index) % TABLESIZE;
		if (HashTable[try] == NULL) {
			HashTable[try] = person;
			printf("Stored %s %d at location %d\n", person->name, person->key, index);
			return true;
		}
	}
/**
    //checks if the person already exists
    if ((HashTable[index] != NULL)) {
        if ((strncmp(HashTable[index]->name, person->name, 256) == 0)) {
	    	printf("ERROR: %s already exists at location %d\n", HashTable[index]->name, index);
            return false;
        } else {
		printf("Collision occured\n");
		return false;
	}	
        return false;
    }
**/
    //printf("Stored %s %d at location %d\n", person->name, person->key, index);
    return false;

} //end hashInsert

inputs *hashSearch (char *nameSearch) {
	int index = hash(nameSearch);
	for (int i = 0; i < TABLESIZE; i++) {
		int try = (i + index) % TABLESIZE;
		if (HashTable[try] != NULL && strncmp(HashTable[try]->name, nameSearch, 256) == 0) {
		return HashTable[try];
		} //end if
	}

	return NULL;
/**
	if (HashTable[index] != NULL && strncmp(HashTable[index]->name, nameSearch, 256) == 0) {
		return HashTable[index];
	} else {
		return NULL;
	} //end if
**/
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

//void performPassOne()


int main(int argc, char *argv[]) {
	
	initializeHashTable();
	address addresses = {0x00, 0x00, 0x00};

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

	char tempLine[256];
	char nameOne[256];
	char nameTwo[256];
	char nameThree[256];

	while (!feof(inputfile)) {

		fscanf(inputfile, "%s\t%s\t%s", nameOne, nameTwo, nameThree);


		printf("String 1: %s\n", nameOne);
		printf("String 2: %s\n", nameTwo);
		printf("String 3: %s\n\n", nameThree);

		printf("Complete String: %s\t%s\t%s\n", nameOne, nameTwo, nameThree);
	}
/**
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
		strcpy(intohash[inputcount].name, nametoken);

		//checks if there is a key value, if there is, it will hash into table
		//otherwise, it will search the table for the name
		char *keytoken = strtok(NULL, " ");
		if (!(keytoken == NULL)) {
			tempkey = atoi(keytoken);
			//printf("current key is: %d\n", tempkey);
			intohash[inputcount].key = tempkey;

			hashInsert(&intohash[inputcount]);

		//search part of the function
		}
		else {
			//assigns the last space to null terminator
			nametoken[strlen(nametoken) - 1] = '\0'; //to remove whitespace for searches
			searchIndex = hash(nametoken);			//find the location index where the key is at

			inputs *tmp = hashSearch(nametoken);
			if (tmp == NULL) {
				printf("ERROR %s not found\n", nametoken);
			} else {
				printf("%s found at location %d with a value of %d\n", nametoken, searchIndex, tmp->key);
			}
		}	
		inputcount++;
	} //end while
**/
	fclose(inputfile);
	//printTable();
    return 0;
}
