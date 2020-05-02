#include "queue.h"

queue createQueue()
{
	queue q;
	q.head = nullptr;
	q.tail = nullptr;
	q.size = 0;
	return q;
}

node* createNode(double val)
{
	node* n = new node;
	n->val = val;
	n->next = nullptr;
	return n;
}

void pushElement(queue& q, double val)
{
	if (isEmpty(q))
	{
		q.head = q.tail = createNode(val);
	}
	else
	{
		q.tail->next = createNode(val);
		q.tail = q.tail->next;
	}
	q.size++;
}

double popElement(queue& q)
{
	if (isEmpty(q))
	{
		throw "Error";
	}
	else
	{
		q.size--;
		node* n = q.head;
		q.head = q.head->next;
		double val = n->val;
		delete n;
		if (q.size==0)
		{
			q.head = q.tail = 0;
		}
		return val;
	}
}

bool isEmpty(queue& q)
{
	if (q.head==nullptr && q.tail==nullptr)
	{
		return true;
	}
	return false;
}
