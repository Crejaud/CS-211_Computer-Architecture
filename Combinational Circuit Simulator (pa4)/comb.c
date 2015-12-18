#include "comb.h"

int main(int argc, char **argv) {


	/* DECLARATIONS AT TOP */

	FILE* fp;
	struct node** outputs;
	struct node** inputs;
	int inputSize, outputSize, i, result;
	int* fpInputs;
	char* args;
	char command[12];

	/* Check num of args */
	if (argc == 1) {
		printf("error\n");
		exit(0);
	}

	/* SETUP TREE */
	fp = fopen(argv[1], "r");
	if (fp == NULL) /* if the txt file is empty, exit program */
		exit(0);
	/* GET INPUTVAR */
	if (fscanf(fp,"%s",command) == EOF) /* if the first command does not exist */
		exit(0);
	if (strcmp(command,"INPUTVAR") == 0) {
		fscanf(fp,"%d",&inputSize); /* get size */
		args = (char*) malloc(inputSize*sizeof(char));
		inputs = (struct node**) malloc(inputSize*sizeof(struct node*));
		for(i = 0;i < inputSize; i++) {
			args[i] = readPastSpaces(fp);
			/*fscanf(fp,"%c", &args[i]);*/
			inputs[i] = (struct node*) malloc(sizeof(struct node));
			inputs[i]->output = (char*) malloc(sizeof(char));
			inputs[i]->output[0] = args[i];
			inputs[i]->numDowns = 0;
			inputs[i]->numOutputs = 1;
			inputs[i]->command = (char*) malloc(strlen(command)*sizeof(char));
			strcpy(inputs[i]->command,command);
			inputs[i]->down = NULL;
		}
		/*free(args);*/
	}
	
	/* GET OUTPUTVAR */
	if (fscanf(fp, "%s", command) == EOF) /* if second command DNE */
		exit(0);
	if (strcmp(command,"OUTPUTVAR") == 0) {
			fscanf(fp,"%d",&outputSize);
			args = (char*) malloc(outputSize*sizeof(char));
			outputs = (struct node**) malloc(outputSize*sizeof(struct node*));
			for(i = 0;i < outputSize; i++) {
				args[i] = readPastSpaces(fp);
				outputs[i] = (struct node*) malloc(sizeof(struct node));
				outputs[i]->output = (char*) malloc(sizeof(char));
				outputs[i]->output[0] = args[i];
				outputs[i]->numOutputs = 1;
				outputs[i]->command = (char*) malloc(strlen(command)*sizeof(char));
				strcpy(outputs[i]->command,command);
				outputs[i]->down = NULL; /* down is NULL for now */
			}
			/*free(args);*/
		}
	
	setupTree(fp, inputSize, outputSize, inputs, outputs); /* set up the tree of each output circuit */ 
	/* inputs, inputSize, outputs, outputSize have been set accordingly */

	fclose(fp);	
	
	/* TAKE INPUTS, Traverse by L-R-V, get values of outputs */
	fp = fopen(argv[2], "r");
	if (fp == NULL) /* if the txt file is empty, exit program */
		exit(0);
	
	fpInputs = (int*) malloc(inputSize * sizeof(int));
	
	while (fscanf(fp, "%d", &fpInputs[0]) != EOF) {
		for (i = 1; i < inputSize; i++)
				fscanf(fp, "%d", &fpInputs[i]);
				
		for (i = 0; i < outputSize; i++) {
			result = traverse(fpInputs, outputs[i], inputs, inputSize, outputs[i]->output[0]);
			if (i == outputSize - 1) {
				printf("%d\n", result);
				continue;
			}
			/* OUTPUT */
			printf("%d ", result);
		}
	}

	return 0;

}

void setupTree(FILE* fp, int inputSize, int outputSize, struct node** inputs, struct node** outputs) {
	char* args;
	char command[12];
	int size, i, numVars;
	struct node** vars;
	vars = (struct node**) malloc(52*sizeof(struct node*)); /* assuming there's only 52 different possible vars */ 
	while(fscanf(fp,"%s",command) != EOF) {
		size = 0;
		if (strcmp(command,"AND") == 0 || strcmp(command,"OR") == 0) {
			args = (char*) malloc(3*sizeof(char));
			/*fgetc(fp);  skip white space */
			for (i = 0; i < 2; i++) {
				args[i] = readPastSpaces(fp);
				/*
				fscanf(fp,"%c",&args[i]);
				fgetc(fp);  skip white space 
				*/
			}
			args[2] = readPastSpaces(fp);
			/*fscanf(fp,"%c",&args[2]);*/
			vars[numVars] = (struct node*) malloc(sizeof(struct node));
			vars[numVars]->output = (char*) malloc(sizeof(char));
			vars[numVars]->output[0] = args[2];
			vars[numVars]->numDowns = 2;
			vars[numVars]->numOutputs = 1;
			vars[numVars]->command = (char*) malloc(strlen(command)*sizeof(char));
			strcpy(vars[numVars]->command,command);
			/* since it's and/or, it will have 2 inputs */

			/* Call setDowns */
			vars[numVars]->down = setDowns(vars, inputs, inputSize, numVars, 2, args);
			
			/* Check to see if vars[numVars]->output[0] exists in outputs
			   if true, set it as a child of outputs */
			outputs = findOutputs(vars, outputs, numVars, outputSize);

			numVars++;
		}
		else if (strcmp(command,"NOT") == 0) {
			args = (char*) malloc(2*sizeof(char));
			args[0] = readPastSpaces(fp);
			args[1] = readPastSpaces(fp);
			/*fgetc(fp);
			fscanf(fp,"%c",&args[0]);
			fgetc(fp);
			fscanf(fp,"%c",&args[1]);
			*/
			vars[numVars] = (struct node*) malloc(sizeof(struct node));
			vars[numVars]->output = (char*) malloc(sizeof(char));
			vars[numVars]->output[0] = args[1]; /* set the variable char to vars */
			vars[numVars]->numDowns = 1;
			vars[numVars]->numOutputs = 1;
			vars[numVars]->command = (char*) malloc(strlen(command)*sizeof(char));
			strcpy(vars[numVars]->command,command);
			
			/* call setDowns */
			vars[numVars]->down = setDowns(vars, inputs, inputSize, numVars, 1, args);

			/* Check to see if vars[numVars]->output[0] exists in outputs
			   if true, set it as a child of outputs */
			outputs = findOutputs(vars, outputs, numVars, outputSize);

			numVars++;
		}
		else if (strcmp(command,"DECODER") == 0) {
			fscanf(fp, "%d", &size);
			/* args holds inputs only */
			/* outputs will have to be 2^size */
			args = (char*) malloc(size*sizeof(char));
			
			/*fgetc(fp);*/
			for (i = 0; i < size; i++) {
				args[i] = readPastSpaces(fp);
				/*fscanf(fp, "%c", &args[i]);
				fgetc(fp);*/
			}
			
			vars[numVars] = (struct node*) malloc(sizeof(struct node));
			vars[numVars]->numDowns = size;
			vars[numVars]->command = (char*) malloc(strlen(command)*sizeof(char));
			strcpy(vars[numVars]->command,command);
			/* call setDowns for inputs */
			vars[numVars]->down = setDowns(vars, inputs, inputSize, numVars, size, args);
			/* then set args to hold the variables */

			size = Exp2(size);
			
			args = (char*) malloc(size*sizeof(char));
			
			vars[numVars]->output = (char*) malloc(size*sizeof(char));
			vars[numVars]->numOutputs = size;

			for (i = 0; i < size; i++) {
				args[i] = readPastSpaces(fp);
				/*fscanf(fp, "%c", &args[i]);*/
				vars[numVars]->output[i] = args[i];
				/*fgetc(fp);*/
			}
			

			/* Check all outputs with each vars[numVars]->output
			   Set as down for that specific output */
			outputs = findOutputs(vars, outputs, numVars, outputSize);
			
			numVars++;

			/* NOTE: does vars[numVars]->output (decoder) need to be allocated? */
		}
		else if (strcmp(command,"MULTIPLEXER") == 0) {
			fscanf(fp, "%d", &size);
			/* args holds inputs only */
			/* outputs will have to be log2(size) */
			args = (char*) malloc(size*sizeof(char));

			/*fgetc(fp);*/
			for (i = 0; i < size; i++) {
				args[i] = readPastSpaces(fp);
				/*
				fscanf(fp, "%c", &args[i]);
				fgetc(fp);
				*/
			}
			
			vars[numVars] = (struct node*) malloc(sizeof(struct node));
			vars[numVars]->numDowns = size;
			vars[numVars]->command = (char*) malloc(strlen(command)*sizeof(char));
			strcpy(vars[numVars]->command,command);
			/* call setDowns for inputs */
			vars[numVars]->down = setDowns(vars, inputs, inputSize, numVars, size, args);
			
			/* Next, on to the selectors */
			
			size = (int) Log2((double) size);
			args = (char*) malloc(size*sizeof(char));
			
			for (i = 0; i < size; i++) {
				args[i] = readPastSpaces(fp);
				/*
				fscanf(fp, "%c", &args[i]);
				fgetc(fp);
				*/
			}
			
			vars[numVars]->numSelectors = size;

			/* setDowns should work for selectors as well. Same concept */
			vars[numVars]->selector = setDowns(vars, inputs, inputSize, numVars, size, args);

			/* Next, on to the outputs */
			args = (char*) malloc(sizeof(char));
			args[0] = readPastSpaces(fp);
			/*fscanf(fp, "%c", &args[0]);*/
			
			vars[numVars]->output = (char*) malloc(sizeof(char));
			vars[numVars]->numOutputs = 1;
			vars[numVars]->output[0] = args[0];


			/* Check to see if vars[numVars]->output[0] exists in outputs
			   if true, then set it as a child of outputs */
			outputs = findOutputs(vars, outputs, numVars, outputSize);

			numVars++;
		}
		else {
			/* ERROR!, NONE OF THE ABOVE */
		}
	}
}

int Exp2(int A) {
	int i, sum = 1;
	for (i = 0; i < A; i++) {
		sum *= 2;
	}
	return sum;
}

double Log2(double A) {
	return log(A)/log(2.);
}

int AND(int A, int B) {
	return A*B;
}

int OR(int A, int B) {
	if ((A+B) == 2)
		return 1;
	return (A+B);
}

int NOT(int A) {
	if (A == 0)
		return 1;
	else
		return 0;
}

/* returns graycode to decimal index */
int DECODER(int inSize, int* inputs) {
	int i, index = 0;
	inputs = grayToBin(inSize, inputs); /* convert graycode to binary */
	for (i = 0; i < inSize; i++)
		index += inputs[inSize-1-i] * Exp2(i);
	
	return index;
}

/*
int* binToGray(int inSize, int* inputs) {
	if (inSize == 1)
		return inputs;
	int temp = inputs[inSize-1];
	int tempGray = 0;
	for (int i = inSize - 2; i >= 0; i--) {
		tempGray = XOR(inputs[i], temp);
		temp = inputs[i];
		inputs[i] = tempGray;
	}	
}
*/

int* grayToBin(int inSize, int* inputs) {
	int i;
	if (inSize == 1)
		return inputs;
	for (i = 0; i < inSize - 1; i++) {
		if (inputs[i+1] == 1)
			inputs[i+1] = NOT(inputs[i]);
		else
			inputs[i+1] = inputs[i];
	}
	return inputs;
}

/*
int XOR(int A, int B) {
	if ((A+B)==1)
		return 1;
	return 0;
}
*/

struct node** setDowns(struct node** vars, struct node** inputs, int inputSize, int numVars, int numArgs, char* args) {
	int i, j, k;
	int isAllDigits;	 /* if this becomse zero, then they're all digits */
	struct node** down = (struct node**) malloc(inputSize*sizeof(struct node*));
	isAllDigits = numArgs;
	/* If the inputs are 0 or 1, then set them accordingly  */
	for (i = 0; i < numArgs; i++) {
		if (isdigit(args[i])) {
			down[i] = (struct node*) malloc(sizeof(struct node));
			down[i]->value = args[i] - '0'; /* casts character to digit integer */
			down[i]->down = NULL;
			down[i]->output = NULL;
			down[i]->numOutputs = 0;
			down[i]->numDowns = 0;
			down[i]->command = (char*) malloc(6*sizeof(char));
			down[i]->command = "DIGIT";
			isAllDigits--; /* this is to check if all inputs are digits */
		}
	}

	/* if isAllDigits = 0, then don't bother checking if inputs are variables or from inputs[] */	

	if (isAllDigits != 0) {
	
		/* if it got this far, then the arguements were inputs or vars */
		for (i = 0; i < inputSize; i++) /* checks for inputs  */
			for (j = 0; j < numArgs; j++) 
				if (!isdigit(args[j]) && inputs[i]->output[0] == args[j]) 
					down[j] = inputs[i];

		for (i = 0; i < numVars; i++)
			for (j = 0; j < numArgs; j++)
				for (k = 0; k < vars[i]->numOutputs; k++) /* if decoder,it has multiple outputs  */
					if (!isdigit(args[j]) && vars[i]->output[k] == args[j])
						down[j] = vars[i];
	
	}

	/*free(args);*/

	return down;

}

/* This function sets the downs for each output in outputs from the outputs of each gate */
struct node** findOutputs(struct node** vars, struct node** outputs, int numVars, int outputSize) {
	int i, j;
	for (i = 0; i < outputSize; i++) {
		for (j = 0; j < vars[numVars]->numOutputs; j++) {
			if (vars[numVars]->output[j] == outputs[i]->output[0]) {
				outputs[i]->down = (struct node **) malloc(1 * sizeof(struct node*));
				outputs[i]->down[0] = vars[numVars];
				outputs[i]->numDowns = 1;
			}
		}
	}

	return outputs;
}

int traverse(int* fpInputs, struct node* root, struct node** inputs, int inputSize, char prevVar) {
	int i;
	int* selectors;
	int* muxIn;
	if (root->down == NULL) {
		/* check root to see if exists in inputs */
		if (strcmp(root->command, "INPUTVAR") == 0) {
			for (i = 0; i< inputSize; i++) {
				if (root->output[0] == inputs[i]->output[0]) {
					root->value = fpInputs[i];
					break;
				}
			} 
		}
		return root->value;
	}
	if (strcmp(root->command, "OUTPUTVAR") == 0) {
		return traverse(fpInputs, root->down[0], inputs, inputSize, root->output[0]);
	}
	else if (strcmp(root->command, "AND") == 0) {
		return AND(traverse(fpInputs, root->down[0], inputs, inputSize, root->output[0]), traverse(fpInputs, root->down[1], inputs, inputSize, root->output[0]));
	}
	else if (strcmp(root->command, "OR") == 0) {
		return OR(traverse(fpInputs, root->down[0], inputs, inputSize, root->output[0]), traverse(fpInputs, root->down[1], inputs, inputSize, root->output[0]));
	}
	else if (strcmp(root->command, "NOT") == 0) {
		return NOT(traverse(fpInputs, root->down[0], inputs, inputSize, root->output[0]));
	}
	else if (strcmp(root->command, "DECODER") == 0) {
		selectors = (int*) malloc(root->numDowns * sizeof(int));
		for (i = 0; i < root->numDowns; i++) {
			selectors[i] = traverse(fpInputs, root->down[i], inputs, inputSize, root->output[0]);
		}
		i = DECODER(root->numDowns, selectors);
		if (root->output[i] == prevVar) {
			return 1;
		} else {
			return 0;
		}
	}
	else if (strcmp(root->command, "MULTIPLEXER") == 0) {
		selectors = (int*) malloc(root->numSelectors * sizeof(int));
		for (i = 0; i < root->numSelectors; i++) {
			selectors[i] = traverse(fpInputs, root->selector[i], inputs, inputSize, root->output[0]);
		}
		muxIn = (int*) malloc(root->numDowns * sizeof(int));
		for (i = 0; i < root->numDowns; i++) {
			muxIn[i] = traverse(fpInputs, root->down[i], inputs, inputSize, root->output[0]);
		}
		return muxIn[DECODER(root->numSelectors, selectors)];
	}
	else {
		return 0;
	}
}

char readPastSpaces(FILE* fp) {
	char c = ' ';
	while((c = fgetc(fp)) != EOF) {
		if (!isspace(c))
			break;
	}
	return c;	
}
