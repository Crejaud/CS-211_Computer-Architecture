#include <stdio.h>
#include <stdlib.h>
#include "fifth.h"

int main (int argc, char **argv) {

	/* DECLARATIONS */
	FILE *fp;
	int **matrix;
	int i;

	if (argc != 2) { /* more than 2 args */
		printf("error\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");

	if (fp == NULL) { /* file DNE */
		printf("error\n");
		exit(1);
	}

	/* int m, n;  m is rows, n is columns (mxn matrix)  */
	fscanf(fp, "%d	%d", &m, &n);

	/* m and n now have their values, time to declare 2-D array */
	matrix = malloc(m*sizeof(int*));
	for (i = 0; i < m; i++)
		matrix[i] = malloc(n*sizeof(int));

	matrixAddition((int **) matrix, fp); /* scan file and add two arrays */

	fclose(fp); /* no longer need fp */

	output((int **) matrix); /* outputs array in correct format */
		
	return 0;
}

void matrixAddition(int **matrix, FILE *fp) {

	int i, j, temp;
	/* let i take care of the rows */
	/* let j take care of the columns */
	/* initialize first matrix into matrix[][] */
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			
			fscanf(fp, "%d", &temp);
			matrix[i][j] = temp;
	
		}
	}

	/* add the second matrix to first */
	for (i = 0; i <m; i++) {
		for (j=0; j < n; j++) {
			
			fscanf(fp, "%d", &temp);
			matrix[i][j] += temp;

		}
	}
}

void output(int **matrix) {

	int i, j;
	/* let i take care of the rows */
	/* let j take care of the columns */
	/* output whole matrix */
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			
			if (j == n - 1) {
				printf("%d\n", matrix[i][j]);
			}
			else {
				printf("%d	", matrix[i][j]);
			}
		
		}
	}

}
