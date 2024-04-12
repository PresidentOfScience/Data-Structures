#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

struct Data{
	char name[255];
	int number;
	Data* next;
	Data* prev;
}*head[SIZE], *tail[SIZE];

int COUNTER = 0;

int hash(char name[]){
	return name[0]%SIZE;
}

Data* createData(char name[], int number){
	Data* newData = (Data*)malloc(sizeof(Data));
	newData->number = number;
	strcpy(newData->name, name);
	newData->next = newData->prev = NULL;
	
	return newData;
}

void insertData(Data* newData){
	int idx = hash(newData->name);
	
	if(head[idx] == NULL){
		head[idx] = tail[idx] = newData;
	}
	else{
		tail[idx]->next = newData;
		newData->prev = tail[idx];
		tail[idx] = newData;
	}
}

Data* searchData(char name[]){
	int idx = hash(name);
	Data* curr = head[idx];
	while(curr){
		if(strcmp(curr->name, name) == 0){
			break;
		}
		curr = curr->next;
	}
	return curr;
}

void deleteData(char name[]){
	int idx = hash(name);
	
	if(head[idx] == NULL){
		return;
	}
	else if(head[idx] == tail[idx] && strcmp(head[idx]->name, name) == 0){
		head[idx] = tail[idx] = NULL;
		free(head[idx]);
	}
	else if(strcmp(head[idx]->name, name) == 0){
		Data* toDel = head[idx];
		head[idx] = head[idx]->next;
		head[idx]->prev = NULL;
		toDel = NULL;
		free(toDel);
	}
	else if(strcmp(tail[idx]->name, name) == 0){
		Data* toDel = tail[idx];
		tail[idx] = tail[idx]->prev;
		tail[idx]->next = NULL;
		toDel = NULL;
		free(toDel);
	}
	else{
		Data* curr = searchData(name);
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		curr = NULL;
		free(curr);
//		Data* curr = head[idx];
//		while(curr){
//			if(strcmp(curr->name, name) == 0){
//				curr->next->prev = curr->prev;
//				curr->prev->next = curr->next;
//				curr = NULL;
//				free(curr);
//				break;
//			}
//			curr = curr->next;
//		}
	}
}

void printAll(){
	for(int i=0; i<SIZE; i++){
		printf("[%d] ", i);
		Data* curr = head[i];
		while(curr){
			printf("%s {%d} -> ", curr->name, curr->number);
			curr = curr->next;
		}
		printf("NULL\n");
	}
}

int main(){
	insertData(createData("Jason", 40));
	insertData(createData("Jaysie", 30));
	insertData(createData("Jaszie", 20));
	printAll();
	puts("");
	deleteData("Jaysie");
	printAll();
	puts("");

	Data* myData = searchData("Jaszie");
	if(myData){
		printf("Data found:\n");
		printf("%s {%d} at address : %d\n", myData->name, myData->number, myData);
	}
	else{
		printf("Not found.\n");
	}
	
	puts("");
	printAll();
	
	return 0;
}
