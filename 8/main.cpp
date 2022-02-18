#include <iostream>

#define SIZE 5

struct Node
{
	char data;
	Node* next;
};

struct List
{
	Node* head;
	int size;
};

void init(List* lst)
{
	lst->head = NULL;
	lst->size = 0;
}

void pushNode(List* lst, char data)
{
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = NULL;

	Node* tmp = new Node;
	tmp = lst->head;
	if (tmp == NULL)
	{
		lst->head = newNode;
		lst->size++;
	}
	else
	{
		newNode->next = tmp;
		lst->head = newNode;
		lst->size++;
	}
}

void popNode(List* lst)
{
	Node* tmp = new Node;
	tmp = lst->head;
	if (tmp == NULL)
	{
		std::cout << "List is empty!";
	}
	else
	{
		lst->head = tmp->next;
		delete tmp;
		lst->size--;
	}
}

void printList(List* lst)
{
	Node* current = new Node;
	current = lst->head;
	if (current == NULL)
	{
		std::cout << "List is empty" << std::endl;
	}
	else
	{
		do
		{
			std::cout << int(current->data) << " ";
			current = current->next;
		} while (current != NULL);

		std::cout << std::endl;
	}
}

void deleteList(List* lst)
{
	for (size_t i = 0; i < lst->size; i++)
	{
		popNode(lst);
	}

	delete lst;
}

void initMatrix(int** matrix)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		matrix[i] = new int[SIZE];
		for (size_t j = 0; j < SIZE; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

void ins(int** m, int i, int j)
{
	m[i][j] = 1;
}

void printMatrix(int** matrix)
{
	std::cout << std::endl;
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void deleteMatrix(int** matrix)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void initArr(int* arr)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		arr[i] = 0;
	}
}

void initArrNeg(int* arr)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		arr[i] = -1;
	}
}

void depthTravers(int** matrix, int st)
{
	if (st > SIZE - 1) {
		std::cout << "No such vertex number exists" << std::endl;
	}
	else
	{
		List* lst = new List;
		init(lst);
		int* visited = new int[SIZE];
		initArr(visited);

		std::cout << st << " ";
		pushNode(lst, st);
		visited[st] = 1;

		while (lst->size > 0)
		{
			for (size_t r = 0; r < SIZE; r++)
			{
				if (matrix[lst->head->data][r] == 1 && visited[r] == 0)
				{
					pushNode(lst, r);
					visited[r] = 1;
					std::cout << r << " ";
				}
			}
			if (visited[lst->head->data] == 1)
				popNode(lst);
		}
		deleteList(lst);
		delete[] visited;
	}
	std::cout << std::endl;
}

void printLinks(int* arr)
{
	int* links = new int[SIZE];
	for (size_t i = 0; i < SIZE; i++)
	{
		int max = 0;
		int idx = 0;
		for (size_t j = 0; j < SIZE; j++)
		{
			if (max <= arr[j])
			{
				max = arr[j];
				idx = j;
			}
		}

		if (arr[idx] >= 0)
		{
			std::cout << idx << " (links = " << arr[idx] << ") ";
			arr[idx] = -1;
		}

	}
	std::cout << std::endl;
}

void countLinksAdjacent(int** matrix, int* visited, int* links, int st)
{
	visited[st] = 1;
	if (links[st] == -1) links[st] = 0;
	int next = -1;
	for (size_t r = 0; r < SIZE; r++)
	{
		if (matrix[st][r] == 1 && !visited[r])
			next = r;

		if (matrix[st][r] == 1 && st != r)
		{
			if (links[r] == -1) links[r] = 0;
			links[r]++;
		}

	}
	if (next != -1)	countLinksAdjacent(matrix, visited, links, next);
}

void countLinksAll(int** matrix)
{
	int* links = new int[SIZE];
	for (size_t j = 0; j < SIZE; j++)
	{
		int count = 0;
		for (size_t i = 0; i < SIZE; i++)
		{
			if (matrix[i][j] == 1 && i != j) count++;
		}
		links[j] = count;
	}
	printLinks(links);
	delete[] links;
}

int main()
{
	int** matrix = new int* [SIZE];
	initMatrix(matrix);
	ins(matrix, 0, 1);
	ins(matrix, 0, 2);
	ins(matrix, 1, 3);
	ins(matrix, 3, 4);

	printMatrix(matrix);
	depthTravers(matrix, 0);
	deleteMatrix(matrix);


	int** matrix2 = new int* [SIZE];
	initMatrix(matrix2);
	ins(matrix2, 0, 1);
	ins(matrix2, 0, 3);
	ins(matrix2, 1, 2);
	ins(matrix2, 1, 3);
	ins(matrix2, 2, 1);
	ins(matrix2, 3, 0);
	ins(matrix2, 3, 2);
	ins(matrix2, 0, 0);

	printMatrix(matrix2);

	countLinksAll(matrix2);

	int* visited = new int[SIZE];
	initArr(visited);
	int* links = new int[SIZE];
	initArrNeg(links);

	countLinksAdjacent(matrix2, visited, links, 0);
	printLinks(links);

	delete[] visited;
	delete[] links;
	deleteMatrix(matrix2);
}
