// ConsoleApplication11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

class Node {
public:
	int key;
	Node* left;
	Node* right;
};

Node* treeInsert(Node*, int);
void printTree(Node*);
bool deleteNode(Node*, int);
Node* getSuccessor(Node*);
void deleteTree(Node*);
int countNode(Node*);
bool isBalance(Node*);
bool itFound(Node*, int);

int main()
{
	srand(time(NULL));

	Node* tree = nullptr;

	const int numberOfTree = 500;
	const int numberOfElements = 10000;
	int numberBalance = 0;

	for (int i = 0; i < numberOfTree; ++i)
	{
		for (int j = 0; j < numberOfElements; ++j)
		{
			if (tree == nullptr)
			{
				tree = treeInsert(tree, rand() % (numberOfElements * 10));
			}
			else
			{
				treeInsert(tree, rand() % (numberOfElements * 10));
			}
		}

		if (isBalance(tree))
			numberBalance++;
		deleteTree(tree);
		tree = nullptr;
	}
	cout << "Percentage of balanced trees is " << 100 * numberBalance / numberOfTree << endl;

	for (int i = 0; i < numberOfElements; ++i)
	{
		if (tree == nullptr)
		{
			tree = treeInsert(tree, rand() % (numberOfElements * 10));
		}
		else
		{
			treeInsert(tree, rand() % (numberOfElements * 10));
		}
	}

	cout << "What are we looking for?\nval = ";
	int val;
	cin >> val;
	if (itFound(tree, val))
		cout << val << " in the tree." << endl;
	else
		cout << val << " not in the tree." << endl;

	return 0;
}

Node* treeInsert(Node* t, int d)
{
	Node* newNode = new Node;
	newNode->key = d;
	newNode->left = nullptr;
	newNode->right = nullptr;

	Node* current = t;
	Node* parent = t;
	if (t == nullptr)
	{
		t = newNode;
		return t;
	}
	else
	{
		while (true) 
		{
			parent = current;
			if (current->key > d)
			{
				current = current->left;
				if (current == nullptr)
				{
					parent->left = newNode;
					return newNode;
				}
			}
			else if (current->key <= d)
			{
				current = current->right;
				if (current == nullptr)
				{
					parent->right = newNode;
					return newNode;
				}
			}
		}
	}
}

void printTree(Node* t)
{
	if (t)
	{
		cout << t->key;
		if (t->left || t->right)
		{
			cout << "(";
			if (t->left)
				printTree(t->left);
			else
				cout << "NULL";
			cout << ",";
			if (t->right)
				printTree(t->right);
			else
				cout << "NULL";
			cout << ")";
		}
	}
}

void deleteTree(Node* t)
{
	if (t == nullptr)
		return;
	deleteTree(t->left);
	deleteTree(t->right);
	delete t;
}

int countNode(Node* t)
{
	if (t == nullptr)
		return 0;
	return countNode(t->left) + countNode(t->right) + 1;
}

bool isBalance(Node* t)
{
	if (abs(countNode(t->left) - countNode(t->right)) <= 1)
		return true;
	else
		return false;
}

bool itFound(Node* t, int v)
{
	if (t == nullptr)
		return false;
	if (t->key == v)
		return true;
	else
		return (itFound(t->left, v) || itFound(t->right, v));
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
