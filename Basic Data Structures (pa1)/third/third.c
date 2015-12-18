#include <stdio.h> 
#include <stdlib.h> 
#include "third.h"

int main (int argc, char **argv) {
	/* prints error if there are less than or greater than 2 args */
	FILE *fp; /* DECLARATIONS */
	char ch, buffer[100];
	int num;	


	if (argc != 2) {
		printf("error\n");
		exit(1);
	}
	/* This is the root of the linked list */
	/* struct Node *root = NULL; */
	/* root = malloc(sizeof(struct Node)*/

	fp = fopen(argv[1],"r");

	/* prints error if txt file DNE  */
	if (fp == NULL) {
		printf("error\n");
		exit(1);
	}
	
	num = -101101101;
	while ((ch = fgetc(fp)) != EOF && fscanf(fp, "%d", &num) != EOF) { 
		if (num == -101101101) { /* if num hasn't changed, then quit */
			printf("error\n");
			exit(1);
		}
		/* printf("%c %d\n", ch, num); TESTING */
		fgets(buffer,100,fp); /*skip to next line*/
		if (ch == 'i') { insert(num); }
		else if (ch == 'd') { delete(num); }
		else { /* prints error if format of txt is incorrect  */
			/*printf("%c is not found\n", ch); TESTING*/
			printf("error\n");
			exit(1);
		}
		num = -101101101;
	}	

	fclose(fp);

	/* display LL */
	display();

	return 0;
}

void display() {
	
	struct Node *ptr;
	ptr = root;
	/* if ptr is empty, print blank line */
	if (ptr == NULL) {
		printf("\n");
		return;
	}
	do {
		if (ptr->next == NULL)
			printf("%d\n", ptr->data);
		else
			printf("%d	",ptr->data);
	} while ((ptr = ptr->next) != NULL);

}

/* Should be correct */
void insert(int num) {
	/* Make new node with num as data */
	/*printf("Insert\n"); TESTING*/
	struct Node *newNode;
	struct Node *ptr;
	newNode = malloc(sizeof(struct Node));
	newNode->data = num;
	newNode->next = NULL;
	
	 /* Create ptr to traverse LL */
	ptr = root;

	/* if root is NULL, set insertion at root */
	if (root == NULL) {
		root = newNode;
		/*printf("root has %d\n", root->data); TESTING */
		return; 
	}

	/* traversal to the end */
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}

	/* insertion */
	ptr->next = newNode;
}

/* DONE? */
void delete(int num) {
	
	/* checks to see if root is NULL */
	/*printf("Delete\n"); TESTING*/
	/*printf("%d\n", root->data); TESTING*/
	struct Node* nextNode;
	struct Node *ptr, *prev;
	if (root == NULL) {
		return;
	}

	nextNode = NULL; /*keeps track of nextNode to be deleted*/ 

	/* checks to see if root is to be deleted */
	if (root->data == num) {
		nextNode = root->next; /*nextNode now contains everything except root*/
		free(root); /*Free root, because root needs to be deleted*/
		root = nextNode; /* new linked list initialized without initial root */
		return; 
	}
	
	/*ptr takes care of present, prev takes care of previous */
	ptr = root->next;
	prev = root;
	/* checks to see if root is in middle or at end */
	while (ptr != NULL) {
		
		if (ptr->data == num) { /* if ptr contains num, then delete it and free the deleted node */
			struct Node *deletedNode;
			deletedNode = ptr;
			prev->next = ptr->next;
			free(deletedNode);
			return;
		}
		ptr = ptr->next;
		prev = prev->next;
	
	}
	
	/* at this point, num DNE in the LL */

	return;
} 
