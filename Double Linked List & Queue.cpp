#include <stdio.h>
#include <stdlib.h>

struct Node{
	int value;
	Node* next;
	Node* prev;
} *head = NULL, *tail = NULL;

Node* createNode(int value){
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	return newNode;
}

void pushHead(Node* newNode){
	if(head == NULL){
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail(Node* newNode){
	if(head == NULL){
		head = tail = newNode;
	}
	else{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

void pushMid(Node* newNode){
	// Tidak ada data sama sekali
	if(head == NULL){
		head = tail = newNode;
	}
	// Kalau newNode valuenya paling kecil
	else if(newNode->value < head->value){
		pushHead(newNode);
	}
	// Kalau newNode valuenya paling kecil
	else if(newNode->value > tail->value){
		pushTail(newNode);
	}
	// Kalau newNode valuenya bukan paling kecil ataupun paling besar
	else{
		Node* curr = head;
		while(curr){
			if(curr->value > newNode->value){
				newNode->next = curr;
				newNode->prev = curr->prev;
				
				curr->prev = newNode;
				newNode->prev->next = newNode;
				
				break;
			}
			curr = curr->next;
		}
	}
}

void popHead(){
	// Tidak ada data sama sekali
	if(head == NULL){
		return;
	}
	// Kalau hanya ada 1 data
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	// Kalau data lebih dari 1
	else{
		Node* del = head;
		
		head = head->next;
		head->prev = NULL;
		free(del);
		del = NULL;
	}
}

void popTail(){
	// Tidak ada data sama sekali
	if(head == NULL){
		return;
	}
	// Kalau hanya ada 1 data
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	// Kalau data lebih dari 1
	else{
		Node* del = tail;
		
		tail = tail->prev;
		tail->next = NULL;
		free(del);
		del = NULL;
	}
}

void popMid(int value){
	// Tidak ada data sama sekali
	if(head == NULL){
		return;
	}
	// Kalau yang mau dihapus adalah head
	else if(head->value == value){
		popHead();
	}
	// Kalau yang mau dihapus adalah tail
	else if(tail->value == value){
		popTail();
	}
	// Kalau data di tengah-tengah
	else{
		Node* curr = head;
		Node* prevCurr = head;
		while(curr){
			if(curr->value == value){
				prevCurr->next = curr->next;
				curr->next->prev = prevCurr;
				curr->next = NULL;
				free(curr);
				curr = NULL;
				break;
			}
			prevCurr = curr;
			curr = curr->next;
		}
	}
}

void search(int value){
	if(head == NULL){
		printf("No data!\n");
		return;
	}
	else if(head->value == value){
		printf("%d found in head.\n", value);
		return;
	}
	else if(tail->value == value){
		printf("%d found in tail.\n", value);
		return;
	}
	else{
		Node* curr = head;
		while(curr){
			if(curr->value == value){
				printf("%d found in mid.\n", value);
				break;
			}
			curr = curr->next;
		}
	}
}

void printAll(){
	Node* curr = head;
	while(curr){
		printf("%d -> ", curr->value);
		curr = curr->next;
	}
	printf("NULL");
}

int main(){
//	pushHead(createNode(15));
//	printAll();
//	
//	puts("");
//	
//	pushHead(createNode(20));
//	printAll();
//	
//	puts("");
//	
//	pushTail(createNode(50));
//	printAll();
//	
//	puts("");
//	
//	pushTail(createNode(42));
//	printAll();

//	pushMid(createNode(5));
//	printAll();
//	
//	puts("");
//	
//	pushMid(createNode(1));
//	printAll();
//	
//	puts("");
//	
//	pushMid(createNode(10));
//	printAll();
//	
//	puts("");
//
//	pushMid(createNode(100));
//	printAll();
//	
//	puts("");
//	
//	pushMid(createNode(57));
//	printAll();
//	
//	puts("");
	
//	popHead();
//	printAll();
//	
//	puts("");
//	
//	popTail();
//	printAll();
	
//	popMid(1);
//	printAll();
//	
//	puts("");
//	
//	popMid(100);
//	printAll();
//	
//	puts("");
	
//	popMid(10);
//	printAll();
//	
//	puts("");
	
//	search(5);
//	search(10);
//	search(57);

	printf("Queue\n");
	int menu = -1;
	
	while(menu != 3){
		printf("1. Queue\n");
		printf("2. Dequeue\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &menu);
		getchar();
		
		int value;
		switch(menu){
			case 1:
				scanf("%d", &value); getchar();
				pushTail(createNode(value));
				printAll();
				puts("");
				break;
			case 2:
				popHead();
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
