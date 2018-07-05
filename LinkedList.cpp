#include "LinkedList.h"
#include "HierarchyHeaders.h"
#include <iomanip>

Node* LinkedList::getLastNode(void)
{
	Node *p;
	for (p = head; p->next != nullptr; p = p->next);
	return p;
}

LinkedList::LinkedList(void)
{
	this->head = nullptr;
	size = 0;
}

LinkedList::LinkedList(const LinkedList &o)
{
	for (Node *p = o.head; p != nullptr; p = p->next)
		addBack(p->data);
}

LinkedList::~LinkedList(void)
{
	size = 0;
	while (head != nullptr)
	{
		Node *p = head;
		head = head->next;
		delete p;
	}
}

uint LinkedList::getSize(void)
{
	return size;
}

void LinkedList::addBack(Vehicul* data)
{
	if (++size == 1)
		head = new Node(data, nullptr);
	else
	{
		Node *p = getLastNode();
		Node *q = new Node(data, nullptr);
		p->next = q;
	}
}


void LinkedList::addFront(Vehicul* data)
{
	if(++size == 1)
		head = new Node(data, nullptr);
	else
	{
		Node *p = new Node;
		p->data = data;
		p->next = head;
		head = p;
	}
}

bool LinkedList::remove(char *numar)
{
	Node *p = contains(numar);
	if (p != nullptr)
	{
		--size;
		Node *q = p->next;
		p->next = q->next;
		delete q;
		return true;
	}
	return false;
}

Node* LinkedList::contains(char *numar)
{
	Node *p, *q = head;
	for (p = head; p != nullptr; p = p->next)
	{
		AutoVehicul *av = dynamic_cast<AutoVehicul*>(p->data);
		if (Util::stringsEqual(av->getNumar(), numar))
			return q;
		q = p;
	}
	return nullptr;
}

void LinkedList::showContent(void)
{
	int W = 20;
	cout << std::setw(W) << "MARCA";
	cout << std::setw(W) << "MODEL";
	cout << std::setw(W) << "NUMAR" << enter;
	AutoVehicul *av = nullptr;
	myIterator it;
	for (it = begin(); it != end(); ++it)
	{
		av = dynamic_cast<AutoVehicul*>(*it);
		cout << std::setw(W) << av->getMarca();
		cout << std::setw(W) << av->getModel();
		cout << std::setw(W) << av->getNumar() << enter;
	}
	cout << enter;
}

LinkedList& LinkedList::operator = (const LinkedList &o)
{
	if (this != &o)
	{
		for (Node *p = o.head; p != nullptr; p = p->next)
			addBack(p->data);
	}
	return *this;
}
