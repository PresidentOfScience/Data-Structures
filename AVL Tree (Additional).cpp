#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Game{
//	char id[30];
	char title[30];
	char genre[30];
	char email[30];
	int stock;
	
	Game* left;
	Game* right;
	int height;
} *root = NULL;

Game* createGame(char title[], char genre[], char email[], int stock){
	Game* newGame = (Game*)malloc(sizeof(Game));
	strcpy(newGame->title, title);
	strcpy(newGame->genre, genre);
	strcpy(newGame->email, email);
	newGame->stock = stock;
	
//	sprintf(newGame->id, "GA%03d", rand()%1000);
//	while(search(root, newGame->id) != NULL){
//		sprintf(newGame->id, "GA%03d", rand()%1000);
//	}
	
	newGame->left = newGame->right = NULL;
	newGame->height = 1;
	
	return newGame;
}

int height(Game* game){
	// Jika node game tidak ada
	if(game == NULL){
		return 0;
	}
	
	return game->height;
}

int max(int a, int b){
	if(a > b){
		return a;
	}
	
	return b;
}

Game* leftRotate(Game* root){
	// Tampung node
	Game* x = root->right;
	Game* y = x->left;
	
	// Rotate
	x->left = root;
	root->right = y;
	
	// Hitung ulang height
	root->height = 1 + max(height(root->left), height(root->right));
	x->height = 1 + max(height(x->left), height(x->right));
	
	return x;
}

Game* rightRotate(Game* root){
	// Tampung node
	Game* x = root->left;
	Game* y = x->right;
	
	// Rotate
	x->right = root;
	root->left = y;
	
	// Hitung ulang height
	root->height = 1 + max(height(root->left), height(root->right));
	x->height = 1 + max(height(x->left), height(x->right));
	
	return x;
}

int getBalanceFactor(Game* root){
	if(root == NULL){
		return 0;
	}
	
	return height(root->left) - height(root->right);
}

Game* rebalance(Game* root){
	// 2. Hitung height node
	root->height = 1 + max(height(root->left), height(root->right));
	
	// 3. Hitung balance factor
	int balance = height(root->left) - height(root->right);
	
	// 4. Lakukan balancing (4 jenis)
	// a. Left Rotate
	if(balance < -1 && getBalanceFactor(root->right) <= 0){
		return leftRotate(root);
	}
	// b. Left-Right Rotate
	if(balance > 1 && getBalanceFactor(root->left) >= 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	// c. Right Rotate // LEFT LEFT
	if(balance > 1 && getBalanceFactor(root->left) > 0){
		return rightRotate(root);
	}
	// d. Right-Left Rotate
	if(balance < -1 && getBalanceFactor(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Game* search(Game* root, char target[]){
	if(!root) return NULL;
	else if(strcmp(target, root->title) < 0){
		return search(root->left, target);
	}
	else if(strcmp(target, root->title) > 0){
		return search(root->right, target);
	}
	else{
		return root;
	}
}

Game* insertion(Game* root, char title[], char genre[], char email[], int stock){
	// 1. Cek sudah ada data atau belum:
	// a. Belum ada data (rootnya kosong, langsung return game)
	if(root == NULL){
		return createGame(title, genre, email, stock);
	}
	// b. Sudah ada data (rootnya tidak kosong)
	if(strcmp(title, root->title) < 0){
		root->left = insertion(root->left, title, genre, email, stock);
	}
	else{
		root->right = insertion(root->right, title, genre, email, stock);
	}
	
	return rebalance(root);
}

Game* pop(Game* root, char title[]){
	if(root == NULL){
		return NULL;
	}
	else if(strcmp(title, root->title) < 0){
		root->left = pop(root->left, title);
	}
	else if(strcmp(title, root->title) > 0){
		root->right = pop(root->right, title);
	}
	else if(strcmp(title, root->title) == 0){
		// Kondisi ketika game ditemukan
		// a. Tidak punya anak
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
			return NULL;
		}
		// b. Punya 1 anak
		else if(root->left == NULL || root->right == NULL){
			Game* child;
			if(root->left != NULL){
				child = root->left;
			}
			else{
				child = root->right;
			}
			free(root);
			root = child;
		}
		// c. Punya 2 anak
		else{
			Game* predecessor = root->left;
			while(predecessor->right != NULL){
				predecessor = predecessor->right;
			}
			strcpy(root->title, predecessor->title);
			strcpy(root->genre, predecessor->genre);
			strcpy(root->email, predecessor->email);
			root->stock = predecessor->stock;
			root->left = pop(root->left, predecessor->title);
		}
	}
	
	return rebalance(root);
}

void preOrder(Game* root){
	if(root != NULL){
		printf("Game name: %s\n", root->title);
		printf("Game genre: %s\n", root->genre);
		printf("Game name: %d\n\n", root->stock);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(Game* root){
	if(root != NULL){
		inOrder(root->left);
		printf("Game name: %s\n", root->title);
		printf("Game genre: %s\n", root->genre);
		printf("Game name: %d\n\n", root->stock);
		inOrder(root->right);
	}
}

void postOrder(Game* root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("Game name: %s\n", root->title);
		printf("Game genre: %s\n", root->genre);
		printf("Game name: %d\n\n", root->stock);
	}
}

int main(){
//	root = insertion(root, "game1", "genre1", "email1", 1);
	root = insertion(root, "game2", "genre2", "email2", 2);
	root = insertion(root, "game3", "genre3", "email3", 3);
	root = insertion(root, "game4", "genre4", "email4", 4);
	
	root = pop(root, "game3");
	
	puts("Preorder:");
	preOrder(root);

	puts("Inorder:");
	inOrder(root);
		
	puts("Postorder:");
	postOrder(root);
	
	return 0;
}
