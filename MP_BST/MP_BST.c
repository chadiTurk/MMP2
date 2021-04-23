#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"
#include <time.h>
int main (void)
{
	srand(time(0));
	//Create Bst
	bst* set1 = create();
	bst* set2 = create();
	bst* set3 = create();
	int option,value, i=0, max=10, min=0;
	
	for(; i<5; i++){
		insert(set1, rand() % (max + 1 - min) + min); //generates random number that ranges from 0 - 10
		
		insert(set2, rand() % (max + 1 - min) + min); //generates random number that ranges from 0 - 10
	}
	
	print(set1->pRoot);
	printf("\n");
	print(set2->pRoot);
	printf("\n\n");
	
	//Union 
	set3 = unionSet(set1, set2);
	print(set3->pRoot);
	
	//Intersect
	free(set3);
	set3 = create();
	set3=intersect(set1->pRoot, set2, set3);
	print(set3->pRoot);
	
	return 0;
}
