#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	int key;
	char name[100];
	int height;
	struct Node* right;
	struct Node* left;
};

struct Node* createNode(int key, char name[]){
	struct Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->key = key;
	newNode->height = 1;
	newNode->right = newNode->left = NULL;

	return newNode;
}

int getHeight(struct Node* curr){
	if(!curr){
		return 0;
	}

	return curr->height;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}

int getBalF(struct Node* curr){
	return getHeight(curr->left) - getHeight(curr->right);
}

struct Node* leftRotate(struct Node* curr){
	struct Node* child = curr->right;
	struct Node* subChild = child->left;
	
	child->left = curr;
	curr->right = subChild;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right))+1;
					
	child->height = max(getHeight(child->left), getHeight(child->right))+1;
	
	return child;
}

struct Node* rightRotate(struct Node* curr){
	struct Node* child = curr->left;
	struct Node* subChild = child->right;
	
	child->right = curr;
	curr->left = subChild;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
					
	child->height = max(getHeight(child->left), getHeight(child->right)) + 1;
					
	return child;
}

struct Node* balance(struct Node* curr){
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	int balF = getBalF(curr);
	
	// Left-Left
	if(balF > 1 && getBalF(curr->left) >= 0){
		return rightRotate(curr);
	}
	// Left-Right
	else if(balF > 1 && getBalF(curr->left) < 0){
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	// Right-Right
	else if(balF < -1 && getBalF(curr->right) <= 0){
		return leftRotate(curr);
	}
	// Right-Left
	else if(balF < -1 && getBalF(curr->right) > 0){
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}

	return curr;
}

struct Node* insertion(struct Node* curr, struct Node* newNode){
	if(!curr){
		return newNode; 
	}
	else if(newNode->key > curr->key){
		curr->right = insertion(curr->right, newNode);
	}
	else if(newNode->key < curr->key){
		curr->left = insertion(curr->left, newNode);
	}
	else{
		return curr;
	}
	
	return balance(curr);
}

struct Node* searchNode(int target, struct Node* curr){
	if(curr == NULL){
		return NULL;
	}
	else if(target > curr->key){
		return searchNode(target, curr->right);
	}
	else if(target < curr->key){
		return searchNode(target, curr->left);
	}
	else{
		// Return founded node address
		return curr;
	}
}

struct Node* getPredecessor(struct Node* curr){
	struct Node* predecessor = curr->left;

	while(predecessor->right != NULL){
		predecessor = predecessor->right;
	}

	return predecessor;
}

struct Node* deleteNode(int target, struct Node* curr){
	if(curr == NULL){
		return NULL;
	}
	else if(target < curr->key){
		curr->left = deleteNode(target, curr->left);
	}
	else if(target > curr->key){
		curr->right = deleteNode(target, curr->right);
	}
	else{
		// Have no child
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			curr == NULL;
		} 
		// Have 1 child
		else if(curr->left == NULL || curr->right == NULL){
			struct Node* child = (curr->left != NULL) ? curr->left : curr->right;
			free(curr);
			curr = child;
		}
		// Have 2 child
		else{
			struct Node* predecessor = getPredecessor(curr);
			curr->key = predecessor->key;
			strcpy(curr->name, predecessor->name);
			curr->left = deleteNode(predecessor->key, curr->left);
		}
	}

	/* Condition when leaf is deleted
	   doesn't need to rebalance the tree because
	   the curr node is already set to NULL */
	
	if(curr == NULL){
		return curr;
	}
	
	return balance(curr);
}

struct Node* popAll(struct Node* curr){
	if(curr){
		curr->left = popAll(curr->left);
		curr->right = popAll(curr->right);
		
		free(curr);
		curr = NULL;
		return curr;
	}

	return NULL;
}

struct Node* inOrder(struct Node* curr){
	if(curr){
		inOrder(curr->left);
		printf("[%s - %d - %d] -> ", curr->name, curr->key, curr->height);
		inOrder(curr->right);
	}
}

int main(){
	struct Node* root = NULL;

	root = insertion(root, createNode(50, "Budi"));
	root = insertion(root, createNode(40, "Jason"));
	root = insertion(root, createNode(30, "Vito"));
	root = insertion(root, createNode(60, "Jesi"));
	root = insertion(root, createNode(70, "Hans"));
	root = insertion(root, createNode(80, "Mbe"));
	
	inOrder(root);
	
	printf("\nSEARCHING NODE 80\n");
	struct Node* search = searchNode(100, root);
	if(search != NULL){
		printf("%s - %d\n", search->name, search->key);
	}
	else{
		printf("NOT FOUND\n");
	}
	
	printf("\nDELETING NODE\n");
	root = deleteNode(70, root);
	inOrder(root);

	printf("\nDELETING ALL\n");
	popAll(root);
	inOrder(root);
	
	return 0;
}
