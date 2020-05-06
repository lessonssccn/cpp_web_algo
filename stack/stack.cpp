#include "stack.h"

node::node(char val, node* next)
{
	this->val = val;
	this->next = next;
}

char node::getVal()
{
	return val;
}

node* node::getNext()
{
	return next;
}

stack::stack(): head(nullptr), size(0)
{
}

stack::~stack()
{
	node* cur = head;

	while (cur)
	{
		node* t = cur->getNext();
		delete cur;
		cur = t;
	}
}

void stack::push(char val)
{
	head = new node(val, head);
	size++;
}

char stack::getHead()
{
	return head->getVal();
}

void stack::pop()
{
	if (head)
	{
		node* next = head->getNext();
		delete head;
		head = next;
		size--;
	}
}

int stack::getSize()
{
	return size;
}
