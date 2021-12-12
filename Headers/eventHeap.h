#ifndef _EVENT_HEAP_
#define _EVENT_HEAP_

#include "event.h"

class EventHeap
{
public:
	int length;
	int size;
	Event** eventHeap;

	EventHeap();
	~EventHeap();

	void insert(Event* newEvent);
	Event* pop();

	void print();
};



#endif