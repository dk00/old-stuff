// stack.h

#ifndef STACK_H
#define STACK_H

template <class T>
class Stack{
public:
	Stack(const int=10);
	void push(T a);
	T pop();
	bool isEmpty();
	bool isFull();
	int getTop();
	~Stack();
protected:
	T *element;
	int Top;
	const int size;
};
#endif

#include <iostream>
using namespace std;

#include "stack.h"


template <class T>
Stack<T>::Stack(const int s)
:size(s)
{
	element=new T[size];
	Top=-1;
}

template <class T>
void Stack<T>::push(T a)
{
	element[++Top]=a;
}

template <class T>
T Stack<T>::pop()
{
	return element[Top--];
}

template<class T>
bool Stack<T>::isEmpty()
{
	return (Top==-1);
}

template<class T>
bool Stack<T>::isFull()
{
	return (Top==size-1);
}


template<class T>
Stack<T>::~Stack()
{
	delete [] element;
}

template<class T>
int Stack<T>::getTop()
{
	return Top;
}
