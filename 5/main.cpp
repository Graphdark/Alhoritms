#include <stdio.h>
#include <stdlib.h>

#define T char
#define true 1 == 1
#define false 1 != 1

#define SIZE 10

typedef int boolean;

int cursor = -1;
T stack[SIZE];

typedef struct {
	int ptr;
	int data;
} Node;

Node* array[SIZE];
int head;
int tail;
int item;

void initQu() {
	for (int i = 0; i < SIZE; i++) {
		array[i] = NULL;
	}
	head = 0;
	tail = 0;
	item = 0;
}

void insertQu(int ptr, int data) {
	Node* element = (Node*)malloc(sizeof(Node));
	element->ptr = ptr;
	element->data = data;

	if (item == 0) {
		array[tail++] = element;
		item++;
	}
	else if (item == SIZE) {
		printf("Очередь переполнена! Не попал в очередь: [ %d, %d]\n", element->ptr, element->data);
		return;
	}
	else {
		int idxIns = tail % SIZE;
		array[idxIns] = element;
		item++;
		tail++;
		printf("INS: ptr = %d, data = %d\n", element->ptr, element->data);
	}
}

Node* clearQu() {
	if (item == 0) {
		printf("Очерель пуста!");
		return NULL;
	}
	else {

		int idx = 0;
		int maxPriority = array[head]->ptr;
		for (int i = head; i < tail; i++) {
			int iX = i % SIZE;
			if (maxPriority > array[iX]->ptr) {
				maxPriority = array[iX]->ptr;
				idx = i;
			}
		}

		Node* tmp;

		if (maxPriority == array[head]->ptr) {
			idx = head;
			tmp = array[idx];
			array[idx] = NULL;
			head++;
			item--;
			return tmp;
		}

		int idxX = idx % SIZE;

		tmp = array[idxX];
		array[idxX] = NULL;
		Node* tmp2;
		for (int i = idx; i > head; i--) {
			int iY = i % SIZE;
			int iYM = (i - 1) % SIZE;
			tmp2 = array[iY];
			array[iY] = array[iYM];
			array[iYM] = tmp2;
		}

		head++;
		item--;
		return tmp;
	}
}

void printQu() {
	printf("[> ");
	for (int i = 0; i < SIZE; i++) {
		if (array[i] == NULL) {
			printf("[*, *] ");
		}
		else {
			printf("[%d, %d] ", array[i]->ptr, array[i]->data);
		}
	}
	printf("<]\n");
}

boolean push(T data) {
	if (cursor < SIZE) {
		stack[++cursor] = data;
		return true;
	}
	else {
		printf("Стэк переполнен!");
		return false;
	}
}

T pop() {
	if (cursor != -1) {
		return stack[cursor--];
	}
	else {
		printf("Стэк пуст!");
		return -1;
	}
}

void DecToBin(int num) {
	while (num != 0) {
		push(num % 2);
		num /= 2;
	}
}

void funcSteckDecToBin(int num) {
	DecToBin(num);
	while (cursor != -1) {
		printf("%d", pop());
	}
}

int main()
{
	printf("1. Задание\n");
	initQu();
	insertQu(7, 70);
	insertQu(3, 30);
	insertQu(9, 90);
	insertQu(6, 60);
	insertQu(5, 50);
	insertQu(1, 10);
	insertQu(4, 40);
	insertQu(8, 80);
	insertQu(2, 20);
	insertQu(9, 80);
	printQu();

	for (int i = 0; i < 7; i++) {
		Node* value = clearQu();
		printf("DEL: ptr = %d, data = %d \n", value->ptr, value->data);
	}
	printQu();

	insertQu(1, 10);
	insertQu(3, 30);
	insertQu(2, 20);
	printQu();

	for (int i = 0; i < 1; i++) {
		Node* value = clearQu();
		printf("DEL: ptr = %d, data = %d \n", value->ptr, value->data);
	}
	printQu();

	printf("\n2. Задание\n");
	int numValue = 100;
	printf("Число %d в двоичной системе = ", numValue);
	funcSteckDecToBin(numValue);
	printf("\n");

	return 0;
}
