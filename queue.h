#pragma once

struct node
{
	double val;
	node* next;
};

struct queue
{
	node* head;
	node* tail;
	int size;
};

queue createQueue();

node* createNode(double val);

void pushElement(queue & q, double val);

double popElement(queue& q);

bool isEmpty(queue& q);