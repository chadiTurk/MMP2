/*
MMP2 - Dynamic Memory Management and Data Type
ESCALONA, HACINAS, TURK
CSADPRG S12
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//use as pointer
typedef struct Set{
	int val;
	struct Set *s;
}Set;

//Function Prototypes
Set *create();
Set *add(Set *s, int val);
Set *unionSet(Set *a, Set *b);
Set *intersect(Set *a, Set *b);
Set *difference(Set *a, Set *b);
void print(Set *s);

int main()
{
	srand(time(0)); //seed RNG
	
	Set *s1, *s2, *s3;
	int i=0, min=0, max=10;

	s1 = create();
	s2 = create();
	s3 = create();
	
	for(; i<5; i++){
		s1 = add(s1, rand() % (max + 1 - min) + min); //generates random number that ranges from 0 - 10
		
		s2= add(s2, rand() % (max + 1 - min) + min); //generates random number that ranges from 0 - 10
	}
	
	printf("Set 1: ");
	print(s1);
	
	printf("Set 2: ");
	print(s2);
	
	printf("\nUnion: ");
	print(unionSet(s1, s2));
	
	printf("\nIntersect: ");
	print(intersect(s1,s2));
	
	printf("\nDifference: ");
	print(difference(s1,s2));
	
	return 0;
}


//create function; returns null valued set
Set *create(){
	Set *newSet = malloc(sizeof(Set)); //allocate memory for the 'newSet'
	newSet->s = NULL;
	newSet->val = NULL;
	return newSet;
}

Set *add(Set *s, int val){
	if(s -> val == NULL){//for head node
		s->val = val;
		return s;	
	}else{ //for child/subsequent nodes
		Set *traversal = s;
		do{
			//check if val < head
			if(val < traversal->val){
				Set *newHead = create();
				newHead->val = val;
				newHead->s = traversal;
				return newHead;
			}
			
			//check if curr->val < val && val < curr->s->val && curr->s != NULL
			if(traversal->s != NULL)
				if(traversal->val < val && val < traversal->s->val){
					Set *newSet = create();
					newSet->val = val;
					newSet->s = traversal->s;
					traversal->s = newSet;
					break;
				}
			
			//check if curr->val < val && curr->s == NULL
			if(traversal->val < val && traversal->s == NULL){
				Set *newLast = create();
				newLast->val = val;
				traversal->s = newLast;
				break;
			}
			
			traversal = traversal->s;
		}while(traversal != NULL);
		return s;
	}
}

//union is a reserved word for c; 
//refer to this: https://www.tutorialspoint.com/cprogramming/c_unions.htm
Set *unionSet(Set *a, Set *b){ 
	Set *newUnionSet = create();
	
	//simultaneous adding of values
	while(a != NULL && b != NULL){
		if(a->val < b->val){
			newUnionSet = add(newUnionSet, a->val);
			a = a->s;			
		}else{
			newUnionSet = add(newUnionSet, b->val);
			b = b->s;	
		}
	}
	
	
	//adding of remaining values
	while(a != NULL){
		newUnionSet = add(newUnionSet, a->val);
		a = a->s;
	}
	while(b != NULL){
		newUnionSet = add(newUnionSet, b->val);
		b = b->s;
	}
	
	return newUnionSet;
}

//common values between 2 sets; ascending
Set *intersect(Set *a, Set *b){
	Set *newIntersectSet = create();
	Set *temp = b;
	
	while(a!=NULL){
		while(temp!=NULL){
			if(a->val == temp->val){
				newIntersectSet = add(newIntersectSet,a->val);
			}
			temp = temp->s;
		}
		temp = b;
		a = a->s;
	}
	
	return newIntersectSet;
}

//non-common values between 2 sets; ascending
Set *difference(Set *a, Set *b){
	Set *newDifferenceSet = create();
	Set *temp = intersect(a, b);
	while(a != NULL){
		
		
		while(temp!=NULL){
			if(a->val == temp->val){
				break;
			}

			temp = temp->s;
			if(temp == NULL){
				newDifferenceSet = add(newDifferenceSet,a->val);
			}
		}
				
		temp = b;
		a = a->s;
	}
	
	return newDifferenceSet;
}

//traverse and print
void print(Set *s){
	
	if(s->val == NULL){
		printf("empty\n");
	}
	else{
		while(s != NULL){
		printf("%d ", s->val);
		s = s->s;
	}
	printf("\n");
	}
	
}


