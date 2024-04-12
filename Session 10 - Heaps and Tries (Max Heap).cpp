#include <stdio.h>
#include <limits.h>

// Max Heap
int size = 0;
int heap[100] = {INT_MAX};

void swap(int curr, int parent){
	int temp = heap[curr];
	heap[curr] = heap[parent];
	heap[parent] = temp;
}

void insert(int value){
	size++;
	heap[size] = value;
	
	// Upheapify
	int currIndex = size;
	while(heap[currIndex] > heap[currIndex/2]){
		// Swap
		swap(currIndex, currIndex/2);
		currIndex = currIndex/2;
	}
}

int getLeftChild(int curr){
	if(curr*2 > size){
		return INT_MIN;
	}
	
	return heap[curr*2];
}

int getRightChild(int curr){
	if(curr*2+1 > size){
		return INT_MIN;
	}
	
	return heap[curr*2+1];
}

void heapify(int curr){
	int parent = heap[curr];
	int left = getLeftChild(curr);
	int right = getRightChild(curr);
	
	if(left > parent || right > parent){
		if(left > right){
			swap(curr*2, curr);
			heapify(curr*2);
		}
		else{
			swap(curr*2+1, curr);
			heapify(curr*2+1);
		}
	}
}

int extract(){
	int temp = heap[1];
	heap[1] = heap[size];
	heap[size] = 0;
	size--;
	
	// Downheapify
	heapify(1);
	
	return temp;
}

void print(){
	for(int i=1; i<=size; i++){
		printf("Parent: %d, ", heap[i]);
		printf("Left: %d, ", heap[i*2]);
		printf("Right: %d\n", heap[i*2+1]);
	}
}

int main(){
	insert(10);
	insert(20);
	insert(30);
	insert(40);
	print();
	
	puts("");
	
	printf("Extract: %d\n", extract());
	print();
	
	return 0;
}
