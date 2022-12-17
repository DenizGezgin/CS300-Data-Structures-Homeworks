#include "Queue.h"
#include <iostream>

//constractor
Queue::Queue(int size)
{
	maxSize = size;
	arrayHead = new int[size];
	clear();
}

//desctractor
Queue::~Queue()
{
	delete[] arrayHead;
}

bool Queue::isEmpty() const
{
	return currSize == 0;
}

bool Queue::isFull() const
{
	return currSize == maxSize;
}

void Queue::enqueue(const int &newItem)
{
	if (isFull())
	{
		std::cout << "Queue is full no changes were made!" << std::endl;
	}
	else
	{
		//increment back circulary
		if (++back == maxSize)
			back = 0;
		*(arrayHead + back) = newItem;  //append to location back
		currSize++;
	}
}

int Queue::dequeue()
{
	if (isEmpty())
	{
		std::cout << "Dequeued from empty queue program is shutting down!" << std::endl;
		exit(1);
	}
	else
	{
		//get front item
		int frontItem = *(arrayHead + front);

		//incremnt front circulary
		if (++front == maxSize)
			front = 0;

		currSize--;
		return frontItem;
		
	}
}

void Queue::clear()
{
	currSize = 0;
	front = 0;
	back = -1;
}