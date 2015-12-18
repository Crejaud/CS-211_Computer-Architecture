#include <stdio.h>
#include <stdlib.h>
#include "second.h"

int main (int argc, char **argv)
{
	int num;
	/* Ensures that argc must be 2 to continue */
	if (argc != 2) 
	{
		printf("error\n");
		exit(1); 
	}

	/* Prime is defined as an integer (in this case >0) that is only divisibly by 1 or itself */	
	num = atoi(argv[1]);
	isPrime(num);
	return 0;
}

void isPrime(int num) {

	int divisor = 2;
	int isPrime = 1; /*0 is false, else if true */
	/* check to see if num is 2 or 1 */
	if (num == 1) { isPrime = 0; }
	if (num == 2) { isPrime = 2; }
	while (isPrime == 1 && num > divisor)
	{
		if (num % divisor == 0)
		{
			isPrime = 0;
			break;
		}
		divisor++;
	}
	
	if (isPrime == 0) { printf("no\n"); }
	else { printf("yes\n"); }

}

