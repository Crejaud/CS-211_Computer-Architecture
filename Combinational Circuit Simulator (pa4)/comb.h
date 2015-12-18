#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct node {
        int value;
        char* output;
        int numDowns;
        int numOutputs;
        int numSelectors;
        char* command;
        struct node** down;
        struct node** selector;
};

int Exp2(int);
double Log2(double);
int AND(int, int);
int OR(int, int);
int NOT(int);
int DECODER(int, int*);
int* grayToBin(int, int*);
void setupTree(FILE*, int, int, struct node **, struct node **);
struct node** setDowns(struct node**, struct node**, int, int, int, char*);
struct node** findOutputs(struct node **, struct node **, int, int);
int traverse(int*, struct node *, struct node **, int, char);
char readPastSpaces(FILE*);
