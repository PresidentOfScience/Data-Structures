#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient{
	char name[255];
	int prior;
	Patient *next;
} *head, *tail;

Patient *createPatient(char name[], int prior){
	Patient *newPatient = (Patient*)malloc(sizeof(Patient));
	newPatient->prior = prior;
	strcpy(newPatient->name, name);
	newPatient->next = NULL;
	
	return newPatient;
}

void pushHead(Patient *newPatient){
	if(head == NULL){
		head = tail = newPatient;
	}
	else{
		newPatient->next = head;
		head = newPatient;
	}
}

void pushTail(Patient *newPatient){
	if(head == NULL){
		head = tail = newPatient;
	}
	else{
		tail->next = newPatient;
		tail = newPatient;
	}
}

void pushMid(Patient *newPatient){
	if(head == NULL){
		head = tail = newPatient;
	}
	else if(head->prior > newPatient->prior){
		pushHead(newPatient);
	}
	else if(tail->prior < newPatient->prior){
		pushTail(newPatient);
	}
	else{
		Patient *curr = head;
		while(curr != NULL){
			if(curr->next->prior > newPatient->prior){
				break;
			}
			curr = curr->next;
		}
		newPatient->next = curr->next;
		curr->next = newPatient;
	}
}

void popHead(){
	if(head == NULL){
		return;
	}
	else if(head == tail){
		head = tail = NULL;
		free(head);
	}
	else{
		Patient *toDel = head;
		head = head->next;
		toDel = NULL;
		free(toDel);
	}
}

void popTail(){
	if(head == NULL){
		return;
	}
	else if(head == tail){
		head = tail = NULL;
		free(head);
	}
	else{
		Patient *curr = head;
		while(curr->next != tail){
			curr = curr->next;
		}
		Patient *toDel = tail;
		tail = curr;
		curr->next = NULL;
		toDel = NULL;
		free(toDel);
	}
}

void popMid(char name[]){
	if(head == NULL){
		return;
	}
	else if(head == tail && strcmp(head->name, name) == 0){
		head = tail = NULL;
		free(head);
	}
	else if(strcmp(head->name, name) == 0){
		popHead();
	}
	else if(strcmp(tail->name, name) == 0){
		popTail();
	}
	else{
		Patient *curr = head;
		while(curr){
			if(strcmp(curr->next->name, name) == 0){
				break;
			}
			curr = curr->next;
		}
		if(curr != NULL){
			Patient *toDel = curr->next;
			curr->next = toDel->next;
			toDel = NULL;
			free(toDel);
		}
	}
}

Patient *search(char name[]){
	if(head == NULL){
		return NULL;
	}
	else{
		Patient *curr = head;
		while(curr){
			if(strcmp(curr->name, name) == 0){
				break;
			}
			curr = curr->next;
		}
		return curr;
		// 1 -> 2 -> 3 -> NULL
		// Bisa isinya NULL jika data tidak ditemukan
		// Bisa isinya address dari node yang ditemukan
	}
}

void printAll(){
	if(head == NULL){
		return;
	}
	else{
		Patient *curr = head;
		while(curr != NULL){
			printf("%s (%d) -> ", curr->name, curr->prior);
			curr = curr->next;
		}
		printf("NULL\n");
	}
}

int main(){
//	pushHead(createPatient("Dodo", 2));
//	pushHead(createPatient("Dodi", 10));
//	pushHead(createPatient("Dadi", 8));
//	pushTail(createPatient("Jaysie", 20));
	
//	pushMid(createPatient("Muzak", 30));
//	pushMid(createPatient("Jaysie", 10));
//	pushMid(createPatient("Wirgun", 20));
//	pushMid(createPatient("Ciu", 25));
//	popHead();
//	popTail();
//	popMid("Ciu");	
//	
//	Patient *result = search("Jaysie");
//	if(result != NULL){
//		printf("Data ditemukan : %s (%d)\n", result->name, result->prior);
//	}
//	else{
//		printf("Data tidak ditemukan.\n");
//	}
//	
//	printAll();

	printf("Stack\n");
	int menu = -1;
	
	while(menu != 3){
		printf("1. Insert Stack\n");
		printf("2. Remove Stack\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &menu);
		getchar();
		
		int value;
		char name[100];
		switch(menu){
			case 1:
				scanf("%s", name); getchar();
				scanf("%d", &value); getchar();
				pushTail(createPatient(name, value));
				printAll();
				puts("");
				break;
			case 2:
				popTail();
				printAll();
				puts("");
				break;
			case 3:
				printf("Exit\n");
				break;
			default:
				printf("Invalid input!\n");
				break;
		}
	}
	
	return 0;
}
