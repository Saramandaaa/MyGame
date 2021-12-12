#include "eventHeap.h"

#include<iostream>
using namespace std;

EventHeap::EventHeap() {
	length = 0;
	size = 10;
	eventHeap = new Event * [size];
	for (int i = 0; i < size; i++) {
		eventHeap[i] = nullptr;
	}
}

EventHeap::~EventHeap() {
	if (eventHeap) {
		delete[] eventHeap;
		eventHeap = nullptr;
	}
}

void EventHeap::insert(Event* newEvent) {
	if (length == 0) {
		eventHeap[0] = newEvent;
		length++;
		return;
	}

	if (length == size) {
		Event** temp = new Event * [size * 2];
		for (int i = 0; i < length; i++) {
			temp[i] = eventHeap[i];
		}
		delete[] eventHeap;
		eventHeap = temp;
		size *= 2;
		for (int i = length; i < size; i++) {
			eventHeap[i] = nullptr;
		}
	}

	Event* value = newEvent;
	int pre = length;
	int cur = (length - 1) / 2;
	while (value->priority > eventHeap[cur]->priority && pre) {
		eventHeap[pre] = eventHeap[cur];
		pre = cur;
		cur = (cur - 1) / 2;
	}
	eventHeap[pre] = value;
	length++;
}

Event* EventHeap::pop() {
	if (length == 0) return nullptr;
	Event* result = eventHeap[0];
	Event* value = eventHeap[length - 1];
	int pre = 0;
	int left = 1;
	int right = 2;
	int cur;
	while (true) {
		if (!eventHeap[left] && !eventHeap[right]) break;
		if (!eventHeap[left]) cur = right;
		else if (!eventHeap[right]) cur = left;
		else if (eventHeap[left]->priority >= eventHeap[right]->priority) cur = left;
		else cur = right;
		if (value->priority < eventHeap[cur]->priority) {
			eventHeap[pre] = eventHeap[cur];
			pre = cur;
			left = (pre + 1) * 2 - 1;
			right = (pre + 1) * 2;
		}
		else break;
	}
	eventHeap[pre] = value;
	length--;
	eventHeap[length] = nullptr;
	return result;
}

void EventHeap::print() {
	if (!eventHeap) cout << "completely null" << endl;
	for (int i = 0; i < length; i++) {
		if (!eventHeap[i]) cout << "null" << endl;
		cout << eventHeap[i]->priority << endl;
	}
	cout << endl;
}