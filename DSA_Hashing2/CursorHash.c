#include <stdio.h>
#include "CursorHash.h"


VSpace newVSpace(int max)
{
	VSpace tempSpace;
	
	tempSpace.max = max % 2 == 0 ? max : max + 1;
	tempSpace.count = 0;
	tempSpace.data = malloc(sizeof(Data) * tempSpace.max);
	tempSpace.avail = tempSpace.max / 2;
	
	int i;
	for(i = 0; i < tempSpace.avail; ++i)
		{
			tempSpace.data[i].elem = EMPTY;
			tempSpace.data[i].next = -1;
		}
	
	for(; i < tempSpace.max - 1; ++i)
		{
			tempSpace.data[i].elem= EMPTY;
			tempSpace.data[i].next = i + 1;
		}
		
	tempSpace.data[i].elem = EMPTY;
	tempSpace.data[i].next = -1;
	
	return tempSpace;
}

int allocSpace(VSpace *vs)
{
	int temp = (*vs).avail;
	(*vs).avail = vs->data[(*vs).avail].next;
	
	return temp;
}

//void freeSpace(VSpace *vsm int loc);
bool addElement(VSpace *vs, int elem)
{
	bool inserted = false;
	int index, temp, ptr;
	float packing = 0.70 * vs->max; 
	
	if(vs->count >= packing)
		{
			if(rehash(vs))
				{
					printf("\nSUCCESSFULLY REHASHED");
				}
		}
		
		index = Hash(elem, vs->max);
		
		if(vs->data[index].elem == EMPTY)
			{
				vs->data[index].elem = elem;
				vs->count++;
				return true;
			}
			
		else if(vs->data[index].elem != elem || vs->data[index].elem == DELETED)
			{ 
			int loc = index;
			bool ptrval = false;
			
			while(vs->data[loc].elem != elem && loc != -1) //this will traverse the whole link
				{
						//check if there is a link already
					if(vs->data[loc].next != -1 && vs->data[loc].elem != elem)
							{
								loc = vs->data[loc].next;
							}
					if(loc == -1)
							{
								inserted = true;
								break;
							}
					if(vs->data[loc].next == -1)
							{
								ptrval = true;
								break;
							}
				}
				
				if(inserted || ptrval)
				{
					int tempval = allocSpace(vs); // the index is stored in tempval
					vs->data[tempval].elem = elem;
					
					ptr = vs->data[loc].next; //mastore si negative 1
					vs->data[loc].next = tempval;
					vs->data[tempval].next = ptr;
					vs->count++;
					return true;
				}			
			}
	
	
	
	return false;
}

bool removeElement(VSpace *vs, int elem)
{
	bool deleted = false;
	int index = Hash(elem, vs->max);
	int temp = index, beforeIndex, loc;
	
		if(vs->count > 0) //not empty
			{
			if(vs->data[temp].elem == elem && vs->data[temp].next == -1)
				{
					if(vs->data[temp].next == -1)
						{
							vs->data[temp].elem = EMPTY;
						}
					else
						{
							vs->data[temp].elem = DELETED;
						}
					vs->count--;
					return true;
				}
				
			else
				{
				loc = temp;
				while(vs->data[loc].elem != elem) //traverse the list
					{
						if(vs->data[loc].elem != elem)
							{
								beforeIndex = loc;
							}
						loc = vs->data[loc].next;
					}
				}	
			}
			
			if(vs->data[loc].elem == elem)
			{
					if(vs->data[loc].next == -1)
							{
								vs->data[loc].elem = EMPTY;
							}
					else
							{
								vs->data[loc].elem = DELETED;
							}
										
								vs->data[beforeIndex].next = vs->data[loc].next;
								deallocSpace(vs, loc);
								vs->count--;
								return true;
			}
			
			
	return false;	
}

void deallocSpace(VSpace *vs, int temp)
{
	int loc;
	loc = vs->avail;
	vs->avail = temp;
	vs->data[vs->avail].next = loc;
}

void visualize(VSpace vs)
{
	int i, half = vs.max / 2;
	printf("%5s | %5s | %5s %10s %5s | %5s | %5s \n", "INDEX", "DATA", "LINK", "", "INDEX", "DATA", "LINK");
	printf("-------------------------------------------------------\n");
	
	for(i = 0; i < half; ++i)
		{
			printf("%5d | %5d | %5d %10s %5d | %5d | %5d", i, vs.data[i].elem, vs.data[i].next, "", i + half , vs.data[i + half].elem, vs.data[i + half].next);
			printf("\n");
		}
	printf("-------------------------------------------------------\n");
}

int Hash(int data, int size)
{
	int val;
	
	val = data % (size / 2);
	return val;
}
void display(VSpace vs)
{
	int i, temp;
	if(vs.avail != 0)
		{
			printf("\n%5s | %10s | %15s\n", "INDEX", "ELEMENT", "SYNONYM");
			printf("-----------------------------------\n");
				for(i = 0; i < (vs.max / 2); i++)
					{
						temp = i;
						printf("%5d | ", i);
							while(temp != -1)
								{
									if(vs.data[temp].elem != EMPTY)
										{
											printf(" %10d | ", vs.data[temp].elem);
										}
									
									else
										{
											printf(" %10s | ", "EMPTY");
										}
									temp = vs.data[temp].next;
								}
						printf("\n");
					}
			printf("-----------------------------------\n");
		}
}

bool rehash(VSpace *vs)
{
	VSpace newRehashedSpace = newVSpace(vs->max * 2);
	newRehashedSpace.count = vs->count;
	
	//transfer elements
	int i, temp;
	if(vs->count > 0)
		{
				for(i = 0; i < (vs->max / 2); i++)
					{
						temp = i;
							while(temp != -1)
								{
									if(vs->data[temp].elem != EMPTY)
										{
											addElement(&newRehashedSpace, vs->data[temp].elem);
										}
							
									temp = vs->data[temp].next;
								}
					}
			free(vs->data);
			*vs = newRehashedSpace;
			return true;
		}
	
	return false;

}
