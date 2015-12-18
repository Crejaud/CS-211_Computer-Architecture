#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fourth.h"

int main (int argc, char **argv) {
	
	/* DECLARATIONS */
	FILE *fp;
	int num, i, isEmpty;
	int *hashTable;
	char ch, buffer[100];


	if (argc != 2) { /* If num of args is not 2, print error */
		printf("error\n");
		exit(1);
	}

	/* for a hash table of size of 1000, it is suggested to use the hash constant below */
	/* hash constant approx = 0.618 */
	/* sqrt is part of math.h and returns double */
	/* A hash function for 1000 numbers would be floor(size * fmod(num * hashConstant, 1)) */
	hashTable = malloc(size * sizeof(int)); /* declare hashTable array */

	/* INITIALIZATIONS */
	/* put -1 in each as sentinel key */
	for (i = 0; i < size; i++)
		hashTable[i] = -1;
	

	fp = fopen(argv[1], "r"); /* open file */
	if (fp == NULL) { /* file DNE */
		printf("error\n");
		exit(1);
	}
	
	isEmpty = 1; /*1 if it is empty */
	num = -1; /* num will remain -1 if there is no number after char */
	/* iterate through txt file, and insert or search appropriately */
	while ((ch = fgetc(fp)) != EOF && fscanf(fp, "%d", &num) != EOF) {
		isEmpty = 0; /* it is not empty */
		if (num == -1) {
			printf("error\n");
			continue;
		}
		fgets(buffer, 100, fp); /*skips to next line*/
		if (ch == 'i') { insert(hashTable, num); } /* if ch == 'i', insert the number into hashtable */
		else if (ch == 's') { search(hashTable, num); } /* if ch == 's' search the number in hashtable */
		else { printf("error\n"); } /* neither s or i, so print error */
		num = -1; /* reset num to -1 */
	}

	if (isEmpty == 1)
		printf("\n");

	fclose(fp);

	return 0;
	
}

void insert(int *hashTable, int num) {

	int hashFunction = size * fmod((num * hashConstant), 1); /* hash function */
	/* hashFunction will direct us to the index that num should reside at in hashTable array */
	/* 0 indicates that the index is empty */
	int counter = 0;
	while (hashTable[hashFunction] != -1) {
		if (hashTable[hashFunction] == num) { /* if num is already in hashTable, print duplicate */
			printf("duplicate\n");
			return;
		}
		hashFunction++;
		hashFunction = hashFunction % size;
		counter++;
		if (counter == size+1) { /* once linear probing does a full loop, needs to be rehashed */
			printf("error\n");
			return;
		}

	}
	
	hashTable[hashFunction] = num; /* insert num in hashTable */
	printf("inserted\n");
	return;
}

void search(int *hashTable, int num) {

	int hashFunction = size * fmod((num * hashConstant), 1); /* hash function */
	int counter = 0;
	while (hashTable[hashFunction] != num) {
	
		hashFunction++;
		hashFunction = hashFunction % size;
		counter++;
		if (counter == size+1) {
			printf("absent\n");
			return;
		} 

	}

	/* if while loop breaks, then num has been found */
	printf("present\n");
	return;
	
}
