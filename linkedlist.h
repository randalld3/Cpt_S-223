#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

template <typename DATA_TYPE>
class PlayerProfile
{
public:
	DATA_TYPE name;
	int score;
};

template <typename DATA_TYPE>
class CommandNode
{
public:
	CommandNode(DATA_TYPE data1, DATA_TYPE data2);
	DATA_TYPE data1;
	DATA_TYPE data2;
	CommandNode* next;
};

template <typename DATA_TYPE>
CommandNode<DATA_TYPE>::CommandNode(DATA_TYPE data1, DATA_TYPE data2)
{
	this->data1 = data1;
	this->data2 = data2;
	next = nullptr;
}

template <typename DATA_TYPE>
class CommandList
{
public:
	CommandList();
	~CommandList();
	void insertAtFront(DATA_TYPE item1, DATA_TYPE item2);
	void removeNode(DATA_TYPE item);
	int search(DATA_TYPE item);
	DATA_TYPE at(int index, bool command);
	int size();
private:
	CommandNode<DATA_TYPE>* nodeAt(int index);
	CommandNode<DATA_TYPE>* head;
	int commandCount;
};

template <typename DATA_TYPE>
CommandList<DATA_TYPE>::CommandList()
{
	commandCount = 0;
	head = nullptr;
}

template <typename DATA_TYPE>
CommandList<DATA_TYPE>::~CommandList()
{
	DATA_TYPE removeMe;
	while (head != nullptr)
	{
		removeMe = at(0, true);
		removeNode(removeMe);
	}
}

template <typename DATA_TYPE>
void CommandList<DATA_TYPE>::insertAtFront(DATA_TYPE item1, DATA_TYPE item2)
{
	CommandNode<DATA_TYPE>* newNode = new CommandNode<DATA_TYPE>(item1, item2);

	if (this->size() == 0)
	{
		head = newNode;
		++commandCount;
	}
	else
	{
		int index = this->search(item1);

		if (index == -1)
		{
			newNode->next = head;
			head = newNode;
			++commandCount;
		}
		else
		{
			cout << "Error: Command is already in list" << endl;
			cout << "Please enter a new command" << endl;
		}
	}
}

template <typename DATA_TYPE>
void CommandList<DATA_TYPE>::removeNode(DATA_TYPE item)
{
	int index = this->search(item);

	if (index == -1)
	    cout << "Error 404: Not Found" << endl << "Please enter a new command" << endl;
	else
	{
		if (index == 0) // we wish to delete the head of the list
			head = head->next;
		else
		{
			CommandNode<DATA_TYPE>* current = nodeAt(index - 1);
			current->next = current->next->next;
		}
		cout << "The command has been removed" << endl;
		--commandCount;
	}
}

template <typename DATA_TYPE>
int CommandList<DATA_TYPE>::search(DATA_TYPE item)
{
	CommandNode<DATA_TYPE>* current = head;
	bool found = false;
	int index = 0;

	while (current != nullptr)
	{
		if (current->data1 == item)
		{
			found = true;
			break;
		}
		current = current->next;
		++index;
	}
	if (!found)
		return -1;

	return index;

}

template <typename DATA_TYPE>
DATA_TYPE CommandList<DATA_TYPE>::at(int index, bool command)
{
	if (index < 0 || index > commandCount - 1)
		cout << "Index out of bounds" << endl;

	CommandNode<DATA_TYPE>* current = nodeAt(index);

	if (command)
	    return current->data1;

	return current->data2;

}

template <typename DATA_TYPE>
int CommandList<DATA_TYPE>::size()
{
	return commandCount;
}

template <typename DATA_TYPE>
CommandNode<DATA_TYPE>* CommandList<DATA_TYPE>::nodeAt(int index)
{
	if (index < 0 || index > this->size() - 1)
		cout << "Something has gone very wrong!" << endl;

	CommandNode<DATA_TYPE>* current = head;
	for (int i = 0; i < index; ++i)
		current = current->next;

	return current;
}

#endif