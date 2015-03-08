#include <stdio.h>
#include <stdlib.h>
#include "first.h"

int main(int argc, char *argv[])
{
	/* Ensures that the argc is only 2 */

	/*
	printf("Size: %d\n",size);
	printf("Third element: %s \n", argv[2]);
	Testing purposes only */

	int num;

	if (argc != 2)
	{
		printf("error\n");
		exit(1);
	}

	/* If argc is 2, then check if number is even or odd */
	num = atoi(argv[1]);
	isEven(num);

	return 0;
}

void isEven(int num) {

	switch(num%2)
	{	
		case 0:		printf("even\n");
		break;
		default:	printf("odd\n");
		break;
	}

}

