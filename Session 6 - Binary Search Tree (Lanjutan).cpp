#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char name[100];
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

Node* insertNode(Node* curr, Node* newNode){
	// Kosong, belum ada data
	if(curr == NULL){
		return newNode;
	}
	
	// Tidak kosong, sudah ada root
	// Age newNode > Age curr
	if(newNode->age > curr->age){
		curr->right = insertNode(curr->right, newNode);
	}
	// Age newNode < Age curr
	else if(newNode->age < curr->age){
		curr->left = insertNode(curr->left, newNode);
	}
	
	return curr;
}

void updateNode(Node* root, char newName[], int searchAge){
	// Tidak ketemu di root
	if(root == NULL){
		printf("Not found\n");
		return;
	}
	
	// Umur yg dicari < Umur node sekarang
	if(searchAge < root->age){
		updateNode(root->left, newName, searchAge);
	}
	// Umur yg dicari > Umur node sekarang
	else if(searchAge > root->age){
		updateNode(root->right, newName, searchAge);
	}
	// Ganti nama
	else{
		strcpy(root->name, newName);
		return;
	}
}

void searchNode(Node* root, int searchAge){
	// Tidak ditemukan
	if(root == NULL){
		printf("%d not found\n", searchAge);
		return;
	}
	
	// Umur yg dicari < Umur node sekarang
	if(searchAge < root->age){
		searchNode(root->left, searchAge);
	}
	// Umur yg dicari > Umur node sekarang
	else if(searchAge > root->age){
		searchNode(root->right, searchAge);
	}
	// Jika sudah ditemukan
	else{
		printf("%s with age %d is found", root->name, searchAge);
		return;
	}
}

Node* popNode(Node* root, int searchAge){
	// Sudah tidak ditemukan
	if(root == NULL){
		printf("Not found!\n");
		return NULL;
	}
	// Ketemu dan cek ada anak atau tidak
	else if(root->age == searchAge){
		// Gak punya anak sama sekali
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		// Punya anak kiri
		else if(root->left != NULL && root->right == NULL){
			Node* temp = root->left;
			root->left = NULL;
			free(root);
			root = temp;
		}
		// Punya anak kanan
		else if(root->left == NULL && root->right != NULL){
			Node* temp = root->right;
			root->right = NULL;
			free(root);
			root = temp;
		}
		// Punya anak kiri dan kanan
		else if(root->left != NULL && root->right != NULL){
			Node* temp = root->left;
			// Ambil predecessor (node paling kanan dari left child)
			while(temp->right != NULL){
				temp = temp->right;
			}
			strcpy(root->name, temp->name);
			root->age = temp->age;
			root->left = popNode(root->left, temp->age);
		}
		return root;
	}
	if(searchAge < root->age){
		root->left = popNode(root->left, searchAge);
	}
	else if(searchAge > root->age){
		root->right = popNode(root->right, searchAge);
	}
	
	return root;
}

Node* popAll(Node* root){
	if(root){
		popAll(root->left);
		popAll(root->right);
		
		root->left = root->right = NULL;
		free(root);
		root = NULL;
	}
	return root;
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
	root = insertNode(root, createNode("abc", 45));
	insertNode(root, createNode("bcd", 36));
	insertNode(root, createNode("cde", 55));
	insertNode(root, createNode("def", 40));
	insertNode(root, createNode("efg", 50));
	insertNode(root, createNode("fgh", 10));
	
	printInorder(root);
	getchar();
////	printPreorder(root);
////	printPostorder(root);
//	
//	printf("Update Node 1\n");
//	updateNode(root, "abcde", 100);
//	puts("");
//	
//	printf("Update Node 2\n");
//	updateNode(root, "xyz", 36);
//	printInorder(root);
//	
//	getchar();
//	
//	printf("Search Node\n");
//	searchNode(root, 100);
//	puts("");
//	searchNode(root, 45);
	
	root = popNode(root, 36);
	printInorder(root);
	getchar();
	
	root = popNode(root, 10);
	printInorder(root);
	getchar();
	
	puts("Delete All");
	root = popAll(root);
	printInorder(root); 
	
	return 0;
}
