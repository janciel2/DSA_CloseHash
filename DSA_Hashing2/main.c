#include <stdio.h>
#include <stdlib.h>

#include "CursorHash.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	bool addTry, deleteTry;
	int size, elem;
	printf("[INPUT SIZE OF THE DICTIONARY]: ");
	scanf("%d", &size);
	VSpace space = newVSpace(size);
	
	int choice = 1,i,ch;

	String menu[4] = {"Add new Element", "Remove Element", "Display", "Visualize"};
	
	printf("\nMENU\n");
	printf("--------------------\n");
	while(choice != 0)
		{
			system("cls");
			for(i = 0; i < 4; i++)
				{
					printf("[%d] %s\n", i + 1, menu[i]);
				}	
			printf("\n[INPUT YOUR CHOICE <0 TO EXIT THE PROGRAM>]: ");
			scanf("%d", &ch);
				switch(ch)
					{
						case 1:	printf("\nADD NEW ELEMENT\n");
								printf("------------------\n");
								printf("\n[INPUT AN ELEMENT]: ");
								scanf("%d", &elem);
								addTry = addElement(&space, elem);
								
									if(addTry)
										{
											printf("\nSUCCESSFUL\n");

										}
									else
										{
											printf("\nUNSUCCESSFUL\n");
										}
								break;
						
						case 2:	printf("\nREMOVE ELEMENT\n");
								printf("------------------\n");
								printf("\n[INPUT THE ELEMENT YOU WANT TO DELETE]: ");
								scanf("%d", &elem);
								
								deleteTry = removeElement(&space, elem);
								if(deleteTry)
										{
											printf("\nSUCCESSFUL\n");

										}
									else
										{
											printf("\nUNSUCCESSFUL\n");
										}
								
								break;
						
						case 3:	printf("\nDISPLAY\n");
								printf("------------------\n"); 
								display(space);
								break;
						
						case 4:	printf("\nVISUALIZE\n");
								printf("------------------\n");
								visualize(space);
								break;
						
						case 0: choice = 0;
								break;
						default: printf("\nINVALID OPTION . . . \n");
					}
			system("pause");
		}
	return 0;
}
