#include <stdio.h>
#include <stdlib.h>


#define SIZE 15

void exercise_1();
void exercise_2_3();


typedef enum {
	BRACE_OPENLEFT,
	BRACE_MISSINGLEFT,
	BRACE_NONCONFORMITY,
	BRACE_CONFORMITY
} bMessage;

bool checkLeftBrace(char);
bool checkRightBrace(char);
char getBraceLeftPair(char);
bool checkBraces(char* string, int size);
void printBraceMessage();


typedef enum {
	L_SORTASC,
	L_SORTDESC,
	L_NOTSORT,
} lMessage;

typedef struct Node
{
	int dat;
	struct Node* next;
} Node;

typedef struct
{
	Node* head;
	int size;
} List;

List* init();
void freeList(List*);
void freeNode(Node*);

void ins(List*, int);
Node* rm(List*, int);

List* copy(List*);
void copy2(List*, List*);

void printNode(Node*);
void printList(List*);

bool checkSort(List*);
void printListMessage();



int main(const int arc, const char** argv)
{
	exercise_1();
	exercise_2_3();

	return 0;
}

void exercise_1()
{
	printf("Задание 1\n");
	char str1[SIZE] = "(2+(2*2))";
	printf("%s - ", checkBraces(str1, SIZE) ? "true" : "false");
	printBraceMessage();
	char str2[SIZE] = "{2/{5*(4+7)]";
	printf("%s - ", checkBraces(str2, SIZE) ? "true" : "false");
	printBraceMessage();
}

void exercise_2_3()
{
	printf("\nЗадание 2 и 3\n");
	List* lst1 = init();
	ins(lst1, 123);
	ins(lst1, 653);
	ins(lst1, 947);
	printf("Печать первого списка после добваления в него элементов:\n");
	printList(lst1);

	List* lst2 = copy(lst1);
	printf("Печать второго списка после копирования:\n");
	printList(lst2);
	printf("%s - ", checkSort(lst2) ? "true" : "false");
	printListMessage();
	ins(lst2, 453);
	printf("Печать второго списка после добваления в него элементов:\n");
	printList(lst2);
	printf("%s - ", checkSort(lst2) ? "true" : "false");
	printListMessage();

	free(rm(lst1, 123));
	printf("Печать первого списка после удаления из него элементов:\n");
	printList(lst1);
	printf("Печать второго списка:\n");
	printList(lst2);

	free(rm(lst2, 947));
	printf("Печать первого списка:\n");
	printList(lst1);
	printf("Печать второго списка после удаления из него элементов:\n");
	printList(lst2);

	free(rm(lst2, 123));
	free(rm(lst2, 653));
	ins(lst2, 452);
	ins(lst2, 321);
	printf("Печать второго списка после удаления/добавления в него элементов:\n");
	printList(lst2);
	printf("%s - ", checkSort(lst2) ? "true" : "false");
	printListMessage();

	copy2(lst1, lst2);
	printf("Печать второго списка после копирования в него элементов из первого списка:\n");
	printList(lst2);

	freeList(lst1);
	freeList(lst2);
}
