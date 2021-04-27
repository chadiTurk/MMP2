/*
MMP2 - Dynamic Memory Management and Data Type
ESCALONA, HACINAS, TURK
CSADPRG S12
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//use as pointer
typedef struct Set{
	int val;
	struct Set *s;
	bool isEmpty;
}Set;


//create function; returns reference to a new set
Set *create(){
	Set *newSet = malloc(sizeof(Set)); //allocate memory for the 'newSet'
	newSet->s = NULL;
	newSet->isEmpty = true;
	return newSet;
}

Set *add(Set *s, int val){
	if(s ->isEmpty == true){//for head node
		s->val = val;
		s->isEmpty = false;
		return s;	
	}else{ //for child/subsequent nodes
		Set *traversal = s;
		
		do{
			//check if val < head
			if(val < traversal->val){
				Set *newHead = create();
				newHead->val = val;
				newHead->s = traversal;
				newHead->isEmpty = false;
				return newHead;
			}
			
			//check if curr->val < val && val < curr->s->val && curr->s != NULL
			if(traversal->s != NULL)
				if(traversal->val < val && val < traversal->s->val){
					Set *newSet = create();
					newSet->val = val;
					newSet->s = traversal->s;
					newSet->isEmpty = false;
					traversal->s = newSet;
					break;
				}
			
			//check if curr->val < val && curr->s == NULL
			if(traversal->val < val && traversal->s == NULL){
				Set *newLast = create();
				newLast->val = val;
				newLast->isEmpty = false;
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
	
	if(s->isEmpty == true){
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

//search for the given number in the set
int search(Set *s, int num){ 
	
	if(s->isEmpty == true){
		return 0; //number not found in set
	}
	else{
		while(s != NULL){
		if(s->val == num)
			return 1; //number is found
		
		s = s->s;
		}

	}
	
}

int main(){
	Set *s1, *s2, *s3;

	s1 = create();
	s2 = create();
	s3 = create();
	
	s1 = add (s1, 4);
	s1 = add (s1, 2);
	s1 = add (s1, 8);
	s1 = add (s1, 6);
	print (s1); // this statement will display (2, 4, 6, 8) OK
	s2 = add (s2, 2);
	s2 = add (s2, 5);
	print (s2); // this statement will display (2, 5) OK
	s3 = add (s3, 7);
	s3 = add (s3, 6);
	print (s3); // this statement will display (6, 7) OK

	print (unionSet(s1, s2)); // this statement will return (2, 4, 5, 6, 8) OK
	print (intersect(s1, s2)); // this statement will return (2) OK
	print (difference(s1, s3)); // this statement will return (2, 4, 8) OK
	print (intersect(s2, s3)); // this statement will return () OK
	print (unionSet(s2, s3)); // this statement will return (2, 5, 6, 7) OK
	
	Set *s4 = create();
	s4 = add(s4, 3);
	s4 = add(s4, 3);
	s4 = add(s4, 3);
	s4 = add(s4, 2);
	s4 = add(s4, 2);
	s4 = add(s4, 1);
	print (s4); // this statement will display (1, 2, 3) OK
	
	
	return 0;
}
