#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int key;
	int height;
	char data[50];
	Node *left;
	Node *right;
};

Node* createNode(int key, char *data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->height = 1;
	strcpy(newNode->data, data);
	newNode->left = newNode->right = NULL;
	
	return newNode;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int getHeight(Node* curr){
	if(curr == NULL){
		return 0;
	}
	
	return curr->height;
}

int calcHeight(Node* curr){
	if(curr == NULL){
		return 0;
	}
	
	return 1+max(getHeight(curr->left), getHeight(curr->right));
}

int calcBalFact(Node* curr){
	if(curr == NULL){
		return 0;
	}
	
	return calcHeight(curr->left) - calcHeight(curr->right);
}

Node* rotateRight(Node* curr){
	Node *pivot = curr->left;
	Node *pivotRightChild = pivot->right;
	
	curr->left = pivotRightChild;
	pivot->right = curr;
	
	// Update height anak (curr) terlebih dahulu
	curr->height = calcHeight(curr);
	pivot->height = calcHeight(pivot);
	
	return pivot;
}

Node* rotateLeft(Node* curr){
	Node *pivot = curr->right;
	Node *pivotLeftChild = pivot->left;
	
	curr->right = pivotLeftChild;
	pivot->left = curr;
	
	// Update height anak (curr) terlebih dahulu
	curr->height = calcHeight(curr);
	pivot->height = calcHeight(pivot);
	
	return pivot;
}

Node* balance(Node* curr){
	curr->height = calcHeight(curr);
	int balFact = calcBalFact(curr);
	
	// Left-Left Case
	if(balFact > 1 && calcBalFact(curr->left) > 0){
		return rotateRight(curr);
	}
	// Left-Right Case
	else if(balFact > 1 && calcBalFact(curr->left) < 0){
		curr->left = rotateLeft(curr->left);
		// Left-Left Case
		return rotateRight(curr);
	}
	// Right-Right Case
	else if(balFact < -1 && calcBalFact(curr->right) < 0){
		return rotateLeft(curr);
	}
	// Right-Left Case
	else if(balFact < -1 && calcBalFact(curr->right) > 0){
		curr->right = rotateRight(curr->right);
		// Right-Right Case
		return rotateLeft(curr);
	}
	
	return curr;
}

Node* insertNode(Node* root, Node *newNode){
	if(root == NULL){
		return newNode;
	}
	else if(newNode->key < root->key){
		root->left = insertNode(root->left, newNode);
	}
	else if(newNode->key > root->key){
		root->right = insertNode(root->right, newNode);
	}
	
	return balance(root);
}

void preOrder(Node* root){
	if(root == NULL){
		return;
	}
	
	printf("%d, %s\n", root->key, root->data);
	preOrder(root->left);
	preOrder(root->right);
}

int main(){
	Node* root = NULL;
	
	root = insertNode(root, createNode(1, "Data 1"));
	root = insertNode(root, createNode(2, "Data 2"));
	root = insertNode(root, createNode(3, "Data 3"));
	
	preOrder(root);
	
	return 0;
}
