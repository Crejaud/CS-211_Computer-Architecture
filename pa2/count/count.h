
struct node {
	size_t data;
	struct node* next;
};

int insertHash(size_t);

#define size 1000

struct node *hashTable[size];
