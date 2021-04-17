/*
ESCALONA, HACINAS, TURK
CSADPRG S12
*/

#include <stdio.h>
#include <stdlib.h>
//use as pointer
typedef struct Set{
	int val;
	struct Set *s;
}Set;


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
	Set * temp = b;
	
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

int main(){
	Set *s1, *s2, *s3;

	s1 = create();
	s2 = create();
	s3 = create();
	
	s1 = add (s1, 4);
	s1 = add (s1, 2);
	s1 = add (s1, 8);
	s1 = add (s1, 6);
	printf("S1\n");
	print (s1); // this statement will display (2, 4, 6, 8)
	s2 = add (s2, 2);
	s2 = add (s2, 5);
	printf("S2\n");
	print (s2); // this statement will display (2, 5)
	s3 = add (s3, 7);
	s3 = add (s3, 6);
	printf("S3\n");
	print (s3); // this statement will display (6, 7)
	
	printf("Operations Testing\n");
	//s2 = add(s2,4);
	print (unionSet(s1, s2)); // this statement will return (2, 4, 5, 6, 8)
	print (intersect(s1, s2)); // this statement will return (2)
	print (difference(s1, s3)); // this statement will return (2, 4, 8)
	print (intersect(s2, s3)); // this statement will return (2, 5)
	print (unionSet(s2, s3)); // this statement will return (2, 5, 6, 7)
	print(difference(s1,s3));
	//
	printf("S4\n");
	Set *s4 = create();
	s4 = add(s4, 3);
	s4 = add(s4, 3);
	s4 = add(s4, 3);
	s4 = add(s4, 2);
	s4 = add(s4, 2);
	s4 = add(s4, 1);
	print (s4); // this statement will display (1, 2, 3)
	
	print (unionSet(s4, s2)); // this statement will return (), missing 1
	print (intersect(s4, s2)); // this statement will return ()
	print (difference(s4, s3)); // this statement will return ()
	print (intersect(s4, s3)); // this statement will return ()
	print (unionSet(s4, s3)); // this statement will return ()
	print(difference(s4,s3));
	
	return 0;
}
