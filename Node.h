#pragma once

#include "Vehicul.h"

struct Node
{
	Vehicul* data;
	Node *next;

	Node(void)
	{
		// empty body
	}
	
	Node(Vehicul *data, Node *next)
	{
		this->data = data;
		this->next = next;
	}
};
