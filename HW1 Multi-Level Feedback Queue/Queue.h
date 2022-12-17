//This class has a queue of intagers with non-changeable size determined at constraction
//Written by: Deniz Can Gezgin 
#ifndef _QUEUE_H
#define _QUEUE_H

class Queue
{
public:
	Queue(int size);  //constructor
	~Queue(); //destructor


	bool isEmpty() const; //check if queue is logicaly empty
	bool isFull() const; //check if queue is logicaly full

	int dequeue(); //dequeue to frontmost item and return it
	void enqueue(const int &newItem); //enqueue the new item taken as parameter
	void clear(); //clear to queue logicaly

private:
	int currSize;
	int maxSize;
	int front;
	int back;
	int* arrayHead;
};

#endif