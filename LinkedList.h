#pragma once

#include "Node.h"
#include "Util.h"

class LinkedList
{
	Node *head;
	uint size;
	Node* getLastNode(void);
public:
	LinkedList(void);
	LinkedList(const LinkedList &o);
	~LinkedList(void);
	uint getSize(void);
	void addBack(Vehicul* data);
	void addFront(Vehicul* data);
	bool remove(char *numar);
	Node* contains(char *numar);
	void showContent(void);
	LinkedList& operator = (const LinkedList &o);

	class myIterator
	{
		Node *node;
	public:
		myIterator(void)
		{
			this->node = nullptr;
		}
		myIterator(Node *node)
		{
			this->node = node;
		}
		myIterator(const myIterator &o)
		{
			this->node = o.node;
		}
		Vehicul* operator *(void)
		{
			return node->data;
		}
		myIterator operator ++(void)
		{
			node = node->next;
			return *this;
		}
		myIterator operator ++(int unit)
		{
			myIterator temp(node);
			this->operator++();
			return temp;
		}
		bool operator != (const myIterator &o)
		{
			return !(node == o.node);
		}
		bool operator == (const myIterator &o)
		{
			return (node == o.node);
		}
		myIterator& operator = (const myIterator &o)
		{
			node = o.node;
			return *this;
		}
	};

	myIterator begin(void)
	{
		return head;
	}

	myIterator end(void)
	{
		return nullptr;
	}
};