#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

struct Data{
	char name[255];
	int number;
}*TABLE[SIZE];

int COUNTER = 0;

int hash(char name[]){
	return name[0]%SIZE;
}

Data* createData(char name[], int number){
	Data* newData = (Data*)malloc(sizeof(Data));
	newData->number = number;
	strcpy(newData->name, name);
	
	return newData;
}

void insertData(Data* newData){
	int idx = hash(newData->name);
	
	if(COUNTER == SIZE){
		printf("TABLE IS FULL!\n");
		return;
	}
	
	while(TABLE[idx] != NULL){
		idx = (idx+1)%SIZE;
	}
	
	TABLE[idx] = newData;
	COUNTER++;
}

int searchData(char name[]){
	int idx = hash(name);
	
	if(TABLE[idx] != NULL && strcmp(TABLE[idx]->name, name) == 0){
		return idx;
	}
	
	int pos = idx;
	while(TABLE[pos] == NULL || strcmp(TABLE[pos]->name, name) != 0){
		pos = (pos+1)%SIZE;
		if(pos == idx){
			return -1;
		}
	}
	
	return pos;
}

void deleteData(char name[]){
	int idx = searchData(name);
	if(idx != -1){
		TABLE[idx] = NULL;
		free(TABLE[idx]);
	}
	else{
		printf("No data to be deleted.\n");
	}
	return;
}

void printAll(){
	for(int i=0; i<SIZE; i++){
		printf("[%d] ", i);
		if(TABLE[i] != NULL){
			printf("%s {%d}\n", TABLE[i]->name, TABLE[i]->number);
		}
		else{
			printf("NULL\n");
		}
	}
}

int main(){
	insertData(createData("Jason", 40));
	insertData(createData("Jaysie", 30));
	printAll();
	
//	printf("%d", searchData("Jaysieasd"));
	deleteData("Jaysie");
	printAll();
	
	return 0;
}
