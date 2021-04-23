/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
/* TO CHECK
	1. DOUBLE CHECK SUCCESSOR
	2. DOUBLE CHECK PREDECESSOR
	3. DOUBLE CHECK PARENT IT SEEMS TO OVERWRITE THE WHOLE TREE
*/



struct Node{
    int data;
    struct Node *pLeft;
    struct Node *pRight;
};

typedef struct Node sNode;

typedef struct {
	sNode *pRoot;
} bst;


sNode* search(bst *t, int x) { //Search the nodes for the passed value. Returns null if value is not found.
	// Your code here
  if(t->pRoot == NULL)
		return NULL;
	
	else{
		sNode *curr = t->pRoot;
		sNode *temp;
		
		while(curr!= NULL){
			temp = curr;	
			if(x == temp->data)
				return temp;
			else if(x < temp->data)
				curr = curr->pLeft;
			else
				curr = curr->pRight;
		}
		return NULL;
	}
}

bst* create() {
	// Your code here

	bst* root = (bst*) malloc(sizeof(bst));
	if(root == NULL){
		printf("Memory allocation has failed.\n");
	}
	else{
		root->pRoot = NULL;
	}

	return root;
}

void insert(bst *t, int x) {
	// Your code here
  		sNode *newNode = (sNode*) malloc(sizeof(sNode));
  		
  		sNode* hold = search(t, x); //temporary variable
		if(hold != NULL) //Checks if value already exists in the set. If value exists, exit function, else continue.
			return;		
  		
	
	if(newNode == NULL){
		printf("Memory allocation has failed.\n");
	}
	else{
		newNode->data = x;
		newNode->pLeft = NULL;
		newNode->pRight = NULL;	
	}
	
	sNode *temp = t->pRoot;

	if(t->pRoot == NULL){
		t->pRoot = newNode;
	}
	else{
		sNode *curr = t->pRoot;
		while(curr!=NULL){
				
			temp= curr;
			
			if(newNode->data > curr->data){
				curr = curr->pRight;
			}
			else{
				curr= curr->pLeft;
			}
		}
		
		if(newNode->data <= temp->data){
			temp->pLeft = newNode;
		}
		else{
			temp->pRight = newNode;
		}
	}
}


void print(sNode *pPointer) { //Based on the "inorder" function that prints values in ascending order
	// Your code here
	if(pPointer == NULL){
		return;
	}
	print(pPointer->pLeft);
	printf("%d	",pPointer->data);
	print(pPointer->pRight);	
}


bst* addAll(sNode *pPointer, bst* set){ //recursive insertion of value to node; Also based on the Inorder function but inserts value instead of printing
	if(pPointer == NULL){//return the point to the set.
		return set;
	}
	
	addAll(pPointer->pLeft, set);
	insert(set, pPointer->data);
	addAll(pPointer->pRight, set);	
}

bst* unionSet(bst* set1, bst* set2){ //function that will combine all elements of two sets into one set
	bst* sumSet = create();
	sumSet = addAll(set1->pRoot, sumSet);
	sumSet = addAll(set2->pRoot, sumSet);
	return sumSet;
}

bst* intersect(sNode *pPointer1, bst* set2, bst* finalSet){ //Snode of set1, sNode of set2
	if(pPointer1 != NULL){//return the point to the set.
		return finalSet;
	}
	
	intersect(pPointer1->pLeft, set2, finalSet); 
	
	sNode* nodeHold = search(set2, pPointer1->data);
	if ( nodeHold != NULL){
		insert(finalSet, nodeHold->data);
	}
	
	intersect(pPointer1->pRight, set2, finalSet);
}



