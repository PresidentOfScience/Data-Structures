#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	char name[50];
	char nim[10];
	float ipk;
};

int main(){
	// Array
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	arr[0] = 100;
	arr[1] = 110;
	
	int size = sizeof(arr)/sizeof(arr[0]);
	
	for(int i=0; i<size; i++){
		printf("Data ke-%d = %d\n", i, arr[i]);
	}
	puts("");

	char str[] = {"Data Structure"};
	printf("%s\n\n", str);
	
	
	// Struct
	Student student1 = {"Student 1", "S000001", 4.0};
	Student student2;
	strcpy(student2.name, "Student 2");
	strcpy(student2.nim, "S000002");
	student2.ipk = 4.0;
	
	Student students[5];
	strcpy(students[0].name, "Student A");
	strcpy(students[0].nim, "S00000A");
	students[0].ipk = 4.0;
	
	for(int i=0; i<1; i++){
		printf("%s - %s - %.1f\n", students[i].name, students[i].nim, students[i].ipk);
	}
	puts("");
	
	
	// Pointer
	int a = 10;
	int *ptr;
	ptr = &a;
	printf("Address a : %d\n", &a);
	printf("Value ptr : %d\n", ptr);
	printf("Value a : %d\n", a);
	printf("Value a : %d\n", *ptr);
	
	int *ptr2;
	ptr2 = (int*)malloc(sizeof(int));
	
	Student *ptr3;
	ptr3 = (Student*)malloc(sizeof(Student));
	strcpy(ptr3->name, "Student Pointer A");
	
	return 0;
}
