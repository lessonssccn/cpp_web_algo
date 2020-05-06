#pragma once

class node
{
	char val;
	node* next;

public:
	node(char val, node* next);
	char getVal();
	node* getNext();
};

class stack
{
	node * head;
	int size;

public:
	stack();
	~stack();

	void push(char val);
	char getHead();
	void pop();
	int getSize();
};