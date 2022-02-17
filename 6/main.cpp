#include <iostream>

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

void ins(List* lst, char data)
{
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = NULL;

	Node* current = new Node;
	current = lst->head;
	if (current == NULL)
	{
		lst->head = newNode;
		lst->size++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = newNode;
		lst->size++;
	}
}

void deleteList(List* lst)
{
	Node* current = new Node;
	Node* nextNode = new Node;
	current = lst->head;
	while (current->next != NULL)
	{
		nextNode = current->next;
		lst->head = nextNode;
		lst->size--;
		delete current;
		current = nextNode;
	}
	delete nextNode;
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

bool checkBracket(List* list)
{
	int flag1 = 0, flag2 = 0, flag3 = 0;
	Node* current = new Node;
	current = list->head;
	if (current == NULL)
	{
		std::cout << "List is empty" << std::endl;
		return false;
	}
	else
	{
		do
		{
			if (current->data == '(') flag1++;
			if (current->data == ')') flag1--;
			if (current->data == '{') flag2++;
			if (current->data == '}') flag2--;
			if (current->data == '[') flag3++;
			if (current->data == ']') flag3--;
			current = current->next;
		} while (current != NULL);

		if (flag1 == 0 && flag2 == 0 && flag3 == 0)
		{
			std::cout << "Bracket sequence is correct" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Bracket sequence is NOT correct" << std::endl;
			return false;
		}
	}
}

List* copyList(List* lst)
{
	//old
	Node* current = new Node;
	current = lst->head;

	if (current == NULL) {
		std::cout << "List is empty!" << std::endl;
		return NULL;
	}

	//new
	List* newLst = new List;
	init(newLst);

	for (size_t i = 0; i < lst->size; i++)
	{
		ins(newLst, current->data);
		current = current->next;
	}
	return newLst;
}

bool checkSort(List* lst)
{
	Node* current = new Node;
	current = lst->head;
	if (current == NULL)
	{
		std::cout << "List is empty" << std::endl;
		return false;
	}
	else
	{
		int max = 0;
		int min = 100;
		int sortMax = 0;
		int sortMin = 0;
		do
		{
			if (current->data > max && sortMax == 0)
				max = current->data;
			else
			{
				sortMax = 1;
				if (current->data < min && sortMin == 0)
					min = current->data;
				else
				{
					sortMin = 1;
					break;
				}
			}
			current = current->next;
		} while (current != NULL);
		if (sortMin == 0 || sortMax == 0)
		{
			std::cout << "List is sorted" << std::endl;
			return true;
		}
		else
		{
			std::cout << "List is NOT sorted" << std::endl;
			return false;
		}
	}
}

int main()
{
	List* list = new List;
	init(list);
	char bracket = ' ';
	std::cout << "Enter a bracket sequence. For exit enter 0" << std::endl;
	while (bracket != '0')
	{
		std::cin >> bracket;
		if (bracket != '0') ins(list, bracket);
	}
	checkBracket(list);
	deleteList(list);
	delete list;

	List* lst = new List;
	init(lst);
	for (size_t i = 0; i < 10; i++)
	{
		ins(lst, rand() % 100);
	}
	printList(lst);

	List* copyLst = new List;
	copyLst = copyList(lst);

	deleteList(lst);
	delete lst;

	std::cout << "Copy of list" << std::endl;
	printList(copyLst);

	deleteList(copyLst);
	delete copyLst;

	List* lstSort = new List;
	init(lstSort);
	int n;
	std::cout << "Enter 10 numbers" << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		std::cin >> n;
		ins(lstSort, n);
	}
	printList(lstSort);

	checkSort(lstSort);

	deleteList(lstSort);
	delete lstSort;
}
