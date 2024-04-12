#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char name[50];
	int age;
	Node* left;
	Node* right;
} *root = NULL;

Node* createNode(char name[], int age){
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->age = age;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

Node* insert(Node* root, Node* newNode){
	// Kalau root-nya kosong
	if(root == NULL){
		return newNode;
	}
	// Kalau root sudah terisi
	// Age newNode < root's age
	if(newNode->age < root->age){
		root->left = insert(root->left, newNode);
	}
	// Age newNode > root's age
	else if(newNode->age > root->age){
		root->right = insert(root->right, newNode);
	}
	
	return root;
}

void update(Node* root, char name[], int age){
	// Tidak ditemukan age yang tepat
	if(root == NULL){
		printf("Not found!\n");
		return;
	}
	
	// Age yang dicari < age root
	if(age < root->age){
		update(root->left, name, age);
	}
	// Age yang dicari > age root
	else if(age > root->age){
		update(root->right, name, age);	
	}
	// Age yang dicari ketemu
	else{
		strcpy(root->name, name);
		return;
	}
}

void search(Node* root, int age){
	// Tidak ditemukan age yang tepat
	if(root == NULL){
		printf("Not found!\n");
		return;
	}
	
	// Age yang dicari < age root
	if(age < root->age){
		search(root->left, age);
	}
	// Age yang dicari > age root
	else if(age > root->age){
		search(root->right, age);	
	}
	// Age yang dicari ketemu
	else{
		printf("%s found!\n", root->name);
		return;
	}
}

void printInorder(Node* root){
	if(root){
		printInorder(root->left);
		printf("Name: %s\n", root->name);
		printf("Age: %d\n\n", root->age);
		printInorder(root->right);
	}
}

void printPreorder(Node* root){
	if(root){
		printf("Name: %s\n", root->name);
		printf("Age: %d\n\n", root->age);
		printPreorder(root->left);
		printPreorder(root->right);
	}
}

void printPostorder(Node* root){
	if(root){
		printPostorder(root->left);
		printPostorder(root->right);
		printf("Name: %s\n", root->name);
		printf("Age: %d\n\n", root->age);
	}
}

int main(){
	root = insert(root, createNode("Jaysie", 20));
	insert(root, createNode("Michael", 30));
	insert(root, createNode("Budi", 15));
	insert(root, createNode("Hans", 35));
	insert(root, createNode("Rico", 10));
	insert(root, createNode("Glori", 25));
	
	printf("Before Update:\n");
	printf("Inorder :\n\n");
	printInorder(root);
	printf("--------------------------------------\n");
	printf("Preorder :\n\n");
	printPreorder(root);
	printf("--------------------------------------\n");
	printf("Postorder :\n\n");
	printPostorder(root);
	printf("--------------------------------------\n");
	printf("After Update:\n");
	update(root, "Kevin", 10);
	printInorder(root);
	
	search(root, 15);
	search(root, 70);
	
	return 0;
}
