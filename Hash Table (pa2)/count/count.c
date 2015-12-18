#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "count.h"

int main(int argc, char** argv) {
	/* DECLARATIONS */
	int count;
	/*double decimal;*/
	size_t decimal;
	FILE *fp;

	/* Ensure that there are only two arguments */
	if (argc != 2) {
		printf("error\n");
		exit(0);
	}

	fp = fopen(argv[1], "r");
	/* txt DNE  */
	if (fp == NULL) {
		printf("error\n");
		exit(0);
	}

	/* allocate memory just enough for a 64-bit hex string */
	/*hex = (char *) malloc(16*sizeof(char));*/
	/* allocate memory for hashTable and set size */
	/*
	size = 1000;
	hashTable = (struct node**) malloc(size*sizeof(struct node*));
	*/
	for(count = 0; count < size; count++) {
		/*
		hashTable[count] = (struct node*) malloc(sizeof(struct node));
		hashTable[count]->data = "-1";
		hashTable[count]->next = NULL;
		*/
		hashTable[count] = NULL;
	}
		
	count = 0;

	while(fscanf(fp, "%lx", &decimal) != EOF) {
		/*printf("%lu\n", decimal);*/
		count += insertHash(decimal);
	}
	/* Close txt */
	fclose(fp);
	
	/* OUTPUT */
	printf("%d\n", count);

	return 0;
}

int insertHash(size_t decimal) {
	/* DECLARATIONS */
	int index;
	struct node *ptr, *prev;

	/*printf("hex inside insertHash = %s\n", hex);*/

	if (decimal == -1) {/* indicates that the string was not valid */
		/*printf("decimal is = to -1 /n/n/n");*/
		return 0;
	}

	/* index is the hashFunction */
	/*index = fmod(decimal, size);*/
	index = decimal % size;
	/*
	printf("index is %d\n", index);
	*/
	ptr = hashTable[index]; /*pointer to hashTable at a certain index*/

	/* If index does not have a LL, add the root */
	if (hashTable[index] == NULL) {
		/* printf("This index has no root"); */
		/*printf("hashTable[32] is %s\n", hashTable[32]->data);*/
		hashTable[index] = (struct node*) malloc(sizeof(struct node));
		/*
		hashTable[index]->data = (char *) malloc(16*sizeof(char));
		strcpy(hashTable[index]->data, hex);
		*/
		hashTable[index]->data = decimal;
		hashTable[index]->next = NULL;
		/*
		printf("hashTable root holds %s\n", hashTable[index]->data);
		printf("hashTable[32]-data holds %s\n", hashTable[32]->data);
		printf("COUNTER ++ \n\n\n");
		*/
		return 1;
	}
	/*
	printf("hashTable[index]->data = %s\n", hashTable[index]->data);

	printf("hashTable[93]->data = %s\n", hashTable[93]->data);
	*/

	/*Check if hex already exists in LL */
	while(ptr != NULL) {
		/*
		if(strcmp(ptr->data,hex) == 0)
			return 0;
		*/
		if(ptr->data == decimal)
			return 0;
		prev = ptr;
		ptr = ptr->next;
	}

	/*Add the new node */
	prev->next = (struct node*) malloc(sizeof(struct node));
	prev = prev->next;
	/*strncpy(prev->data, hex, 16);*/
	/*
	prev->data = (char *) malloc(16*sizeof(char));
	strcpy(prev->data, hex);
	*/
	prev->data = decimal;
	prev->next = NULL;
	/*
	printf("prev holds %s\n", prev->data);
	printf("COUNTER ++ \n\n\n");
	*/
	return 1;
}

/*
void hexToDec(char *hex, double *decimal) {
	int exponent, numValue;
	int  i;
	exponent = strlen(hex);  gets string length 
	if (exponent < 2) {  64 bit hex string must have size of 14 
		*decimal = -1;
		return; 
	}

	exponent -= 3;
	hex[1] = tolower(hex[1]);
	if (hex[0] != '0' || hex[1] != 'x') {  confirms that it's a hex string 
		*decimal = -1;
		return;
	}
		
	for(i = 2; hex[i] != '\0'; i++) {
		
		numValue = 0;  sets to 0 if value is unrecognizable 

		if (hex[i] == '0')
			numValue = 0;
		else if (hex[i] == '1')
			numValue = 1;
		else if (hex[i] == '2')
			numValue = 2;
		else if (hex[i] == '3')
			numValue = 3;
		else if (hex[i] == '4')
			numValue = 4;
		else if (hex[i] == '5')
			numValue = 5;
		else if (hex[i] == '6')
			numValue = 6;
		else if (hex[i] == '7')
			numValue = 7;
		else if (hex[i] == '8')
			numValue = 8;
		else if (hex[i] == '9')
			numValue = 9;
		else {
			hex[i] = tolower(hex[i]); change the letter to lower case
			if (hex[i] == 'a')
				numValue = 10;
			else if (hex[i] == 'b')
				numValue = 11;
			else if (hex[i] == 'c')
				numValue = 12;
			else if (hex[i] == 'd')
				numValue = 13;
			else if (hex[i] == 'e')
				numValue = 14;
			else if (hex[i] == 'f')
				numValue = 15;
			else {
				*decimal = -1;
				return;
				ERROR 
			}
		}
		
		add to decimal 
		*decimal += pow(16, exponent) * numValue;
		exponent--;
	}
}
*/
