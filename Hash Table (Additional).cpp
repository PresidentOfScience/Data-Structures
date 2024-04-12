#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

struct Node{
	char cardID[10];
	char registeredEmail[255];
	char card[255];
	int rarity;
	Node* next;
	Node* prev;
} *head[SIZE], *tail[SIZE];

Node* createNode(char card[], char email[], int rarity){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->rarity = rarity;
	strcpy(newNode->card, card);
	strcpy(newNode->registeredEmail, email);
	// Fungsi sprintf
	sprintf(newNode->cardID, "CRD%d%d%d", rand()%10, rand()%10, rand()%10);
//	printf("%s", newNode->cardID);
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

void mainMenu();

int hash(char cardID[]){
	int idx = 0;
	for(int i=0; i<strlen(cardID); i++){
		idx += cardID[i];
	}
	return idx % SIZE;
}

void insertCard(Node* newCard){
	int idx = hash(newCard->cardID);
	
	if(head[idx] == NULL){
		head[idx] = tail[idx] = newCard;
	}
	else if(head[idx]->rarity > newCard->rarity){
		newCard->next = head[idx];
		head[idx]->prev = newCard;
		head[idx] = newCard;
	}
	else if(tail[idx]->rarity < newCard->rarity){
		tail[idx]->next = newCard;
		newCard->prev = tail[idx];
		tail[idx] = newCard;
	}
	else{
		Node* curr = head[idx];
		while(curr){
			if(curr->rarity >= newCard->rarity){
				newCard->next = curr;
				newCard->prev = curr->prev;
				curr->prev->next = newCard;
				curr->prev = newCard;
				break;
			}
			curr = curr->next;
		}
		
	}
}

void pop(char target[]){
	int idx = hash(target);
	if(head[idx] == NULL){
		printf("No data to be popped\n");
	}
	else if(head[idx] == tail[idx] && strcmp(head[idx]->cardID, target) == 0){
		head[idx] = tail[idx] = NULL;
		free(head[idx]);
	}
	else if(strcmp(head[idx]->cardID, target) == 0){
		Node* toDel = head[idx];
		head[idx] = head[idx]->next;
		toDel->next = head[idx]->prev = NULL;
		toDel = NULL;
		free(toDel);
	}
	else if(strcmp(tail[idx]->cardID, target) == 0){
		Node* toDel = tail[idx];
		tail[idx] = tail[idx]->prev;
		tail[idx]->next = toDel->prev = NULL;
		toDel = NULL;
		free(toDel);
	}
	else{
		Node* toDel = head[idx];
		while(toDel){
			if(strcmp(toDel->cardID, target) == 0){
				toDel->prev->next = toDel->next;
				toDel->next->prev = toDel->prev;
				toDel = NULL;
				free(toDel);
				break;
			}
			toDel = toDel->next;
		}
	}
	printf("Item successfully deleted!\n");
	printf("\nPress enter to continue..."); getchar();
	mainMenu();
}

void createCard(){
	system("cls");
	char name[255];
	do{
		printf("Enter your Pokemon name : ");
		scanf("%[^\n]", name); getchar();
	}while(strlen(name) < 8 || strlen(name) > 20);
	
	char email[255];
	int ctr = 0;
	bool flag;
	do{
		flag = true;
		ctr = 0;
		// jaysie@binus.com
		printf("Enter your email : ");
		scanf("%s", email); getchar();
		for(int i=0; i<strlen(email); i++){
			if(email[i] == '@'){
				ctr++;
			}
		}
		if(ctr == 1 && strstr(email, "@")+4 < strstr(email, ".edu")){
			flag = false;
		}
	}while(flag);
//	printf("%s %s", name, email);
	
	int rarity;
	do{
		printf("Insert rarity : ");
		scanf("%d", &rarity); getchar();
	}while(rarity < 1 || rarity > 3);
	
	insertCard(createNode(name, email, rarity));
	printf("\nPress enter to continue..."); getchar();
	mainMenu();
}

void viewData(){
	system("cls");
	for(int i=0; i<SIZE; i++){
		Node* curr = head[i];
		while(curr){
			printf("%s - %s - %s - %d\n", curr->cardID, curr->card, curr->registeredEmail, curr->rarity);
			curr = curr->next;
		}
	}
	printf("\nPress enter to continue..."); getchar();
	mainMenu();
}

void mainMenu(){
	int input;
	do{
		system("cls");
		printf("Pokemonnnnnn\n");
		printf("1. Insert Card\n");
		printf("2. Delete Card\n");
		printf("3. View Card\n");
		printf("4. Exit\n");
		printf(">> ");
		scanf("%d", &input); getchar();
	
		if(input == 1){
			// Create card
			createCard();
		}
		else if(input == 2){
			// Delete card
			system("cls");
			char deletedID[255];
			printf("Enter ID to be deleted : ");
			scanf("%s", deletedID); getchar();
			pop(deletedID);
		}
		else if(input == 3){
			// View card
			viewData();
		}
	}while(input < 1 || input > 4);
}

int main(){
	srand(time(NULL));
	mainMenu();
	
	return 0;
}
