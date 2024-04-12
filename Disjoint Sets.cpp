#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num[5] = {2, 0, 2, 3, 4};

void initializeDisjoint(){
	int len = sizeof(num)/sizeof(num[0]);
	
	for(int i=0; i<len; i++){
		num[i] = i;
	}
}

void printDisjoint(){
	int len = sizeof(num)/sizeof(num[0]);
	
	for(int i=0; i<len; i++){
		printf("{%d : %d} - ", i, num[i]);
	}
}

int findAncestor(int i){
	while(i != num[i]){
		i = num[i];
	}
	
	return i;
}

void Union(int i, int j){
	int parent_i = findAncestor(i);
	int parent_j = findAncestor(j);
	
	if(parent_i != parent_j){
		num[parent_j] = num[parent_i];
		return;
	}
	
	printf("Is already in the same set.\n");
	return;
}

int main(){
	initializeDisjoint();
	Union(0, 1);
	Union(2, 0);
	Union(3, 1);
	Union(0, 3);
	
//	printf("Ancestor of index 1 : %d", findAncestor(1));
	
	printDisjoint();

	return 0;
}
