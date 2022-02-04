#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <tchar.h>
#pragma warning(suppress : 4996)

#define SIZE_X 3
#define SIZE_Y 3

void freeMem(int** array, const int row)
{
	for (int i = 0; i < row; i++)
	{
		free(array[i]);
	}
	free(array);
}

double f(double x)
{
	return (sqrt(fabs(x)) + 5.0 * pow(x, 3.0));
}

void algorithmTPK()
{
	double arr[11], rezult;
	int i = 0;
	printf("Введите 11 чисел: \n");
	for (i = 0; i < 11; i++)
		scanf_s("%lf", &arr[i]);
	int k = 1;
		for (i = 10; i >= 0; i--, k++)
		{
			printf("%d: ", k);
			rezult = f(arr[i]);
			if (rezult > 400)
				printf("Значение выражения sqrt(fabs(%.3f)) + 5 * pow(%.3f, 3) ПРЕВЫШАЕТ 400\n", arr[i], arr[i]);
			else
				printf("sqrt(fabs(%.3f)) + 5 * pow(%.3f, 3) = %f\n", arr[i], arr[i], rezult);
		}
}

int** initArray(int** array, const int row, const int col)
{
	array = (int**)calloc(sizeof(int*), row);
	for (int i = 0; i < row; ++i)
	{
		*(array + i) = (int*)calloc(sizeof(int), col);
	}
	return array;
}

void fillArr(int** arr) {
	for (int i = 0; i < SIZE_X; ++i) {
		for (int j = 0; j < SIZE_Y; ++j) {
			arr[i][j] = rand() % 100;
		}
	}
}

void printArr(int** arr) {
	for (int i = 0; i < SIZE_X; ++i) {
		for (int j = 0; j < SIZE_Y; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble(int** arr) {
	int tmp;
	for (int i = 0; i < SIZE_X; ++i) {
		for (int j = 0; j < SIZE_Y; ++j) {
			for (int k = 0; k < SIZE_X; ++k) {
				for (int m = 0; m < SIZE_Y; ++m) {
					if (arr[i][j] < arr[k][m]) {
						swap(&arr[i][j], &arr[k][m]);
					}
				}
			}
		}
	}
}

int main()
{
	const int row = 3;
	const int col = 3;
	int** arr = 0;
	arr = initArray(arr, row, col);
	fillArr(arr);
	printArr(arr);
	bubble(arr);
	printf("\n-------------------------\n\n");
	printArr(arr);
	freeMem(arr, row);
	printf("\n");
	algorithmTPK();
	return 0;
}
