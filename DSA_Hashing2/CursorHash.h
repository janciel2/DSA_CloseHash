#ifndef MYHEADER_H
#define MYHEADER_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define DELETED -1

typedef char String[50];

typedef struct{
	int elem;
	int next;
} Data;

typedef struct{
	Data *data;
	int avail;
	int max;
	int count;
} VSpace;

VSpace newVSpace(int max);
int allocSpace(VSpace *vs);
void freeSpace(VSpace *vs , int loc);
bool addElement(VSpace *vs, int elem);
bool removeElement(VSpace *vs, int elem);
void visualize(VSpace vs);
int Hash(int data, int size);
void display(VSpace vs);

void deallocSpace(VSpace *vs, int temp);
bool rehash(VSpace *vs);

#endif
