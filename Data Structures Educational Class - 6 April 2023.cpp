#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PRIORITY QUEUE (USING DOUBLE LINKED LIST)

// Kasus:
// Restoran mengaplikasikan Priority Queue, dengan 3 level, yaitu VVIP (3), VIP (2), dan Member (1).
// Aturan utamanya adalah barisan diurutkan berdasarkan nilai prioritas.

// Enqueue (memasukkan node ke queue) & Dequeue (keluarkan node dari head)

struct node{
	char name[100];
	int age;
	char role[100];
	int level;
	node* next;
	node* prev;
} *head = NULL, *tail = NULL;

struct node* createNode(char name[], int age, char role[]){
	node* newNode = (node*)malloc(sizeof(node));
	
	strcpy(newNode->name, name);
	newNode->age = age;
	strcpy(newNode->role, role);
	
	if(strcmp(newNode->role, "VVIP") == 0){
		newNode->level = 3;
	}
	else if(strcmp(newNode->role, "VIP") == 0){
		newNode->level = 2;
	}
	else{
		newNode->level = 1;
	}
	
	newNode->next = newNode->prev = NULL;
	
	return newNode;
}

void insertQueue(char name[], int age, char role[]){
	node* toPush = createNode(name, age, role);
	
	if(head == NULL){
		head = tail = toPush;
	}
	else{
		if(head->level < toPush->level){
			toPush->next = head;
			head->prev = toPush;
			head = toPush;
		}
		else if(tail->level >= toPush->level){
			tail->next = toPush;
			toPush->prev = tail;
			tail = toPush;
		}
		else{
			node* curr = head;
			while(curr && curr->level >= toPush->level){
				curr = curr->next;
			}
			toPush->next = curr;
			toPush->prev = curr->prev;
			curr->prev = toPush;
			toPush->prev->next = toPush;
		}
	}
}

void addQueue(){
	char name[100], role[100];
	int age;
	printf("Input name : ");
	scanf("%[^\n]", name); getchar();
	printf("Input age : ");
	scanf("%d", &age); getchar();
	printf("Input role : ");
	scanf("%[^\n]", role); getchar();
	
	insertQueue(name, age, role);
	printf("Attention!! New guess named %s with role %s coming to the queue!\n", name, role);
	printf("Press any key to continue...\n"); getchar();
}

void viewQueue(){
	if(head == NULL){
		printf("No queue yet.\n");
		printf("Press any key to continue...\n"); getchar();
	}
	else{
		node* curr = head;
		while(curr){
			printf("%s - %d - %s\n", curr->name, curr->age, curr->role);
			curr = curr->next;
		}
		printf("Press any key to continue...\n"); getchar();		
	}
}

void dequeue(){
	if(head == tail){
		free(head);
		head = NULL;
	}
	else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

void serveOne(){
	if(head == NULL){
		printf("No queue yet.\n");
		printf("Press any key to continue...\n"); getchar();
	}
	else{
		printf("Attention!! Guess named %s with role %s is served right now!\n", head->name, head->role);
		dequeue();
		printf("Press any key to continue...\n"); getchar();
	}
}

void serveAll(){
	if(head == NULL){
		printf("No queue yet.\n");
		printf("Press any key to continue...\n"); getchar();
	}
	else{
		while(head != NULL){
			printf("Attention!! Guess named %s with role %s is served right now!\n", head->name, head->role);
			dequeue();
		}
		printf("Press any key to continue...\n"); getchar();
	}
}

void dismissAll(){
	if(head == NULL){
		printf("No queue yet.\n");
		printf("Press any key to continue...\n"); getchar();
	}
	else{
		while(head != NULL){
			dequeue();
		}
		printf("Queue dismissed.\n");
		printf("Press any key to continue...\n"); getchar();
	}
}

void menu(){
	int opt;
	do{
		system("cls");
		printf("Welcome to The Binus Restaurant!\n");
		printf("1. Add Queue\n");
		printf("2. Serve One\n");
		printf("3. Serve All\n");
		printf("4. View Queue\n");
		printf("5. Dismiss All\n");
		printf("6. Exit\n");
		printf(">> ");
		scanf("%d", &opt); getchar();
	
		switch(opt){
			case 1:
				puts("");
				addQueue();
				break;
			case 2:
				puts("");
				serveOne();
				break;
			case 3:
				puts("");
				serveAll();
				break;
			case 4:
				puts("");
				viewQueue();
				break;
			case 5:
				puts("");
				dismissAll();
				break;
			case 6:
				printf("\nThank You!\n");
				break;
			default:
				break;
		}
	}while(opt != 6);
}

int main(){
	menu();
	
	return 0;
}
