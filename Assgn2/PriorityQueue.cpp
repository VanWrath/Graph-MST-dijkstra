#include "stdafx.h"
#include "PriorityQueue.h"

void PriorityQueue::upheap(int pos) {
	while (pos > 1) {
		int p = pos / 2;
		if (queue->at(pos).priority >= queue->at(p).priority) {
			break;
		}
		iter_swap(queue->begin() + pos, queue->begin() + p);
		pos = p;
	}
}

void PriorityQueue::downheap(int pos) {
	while ((2 * pos) < queue->size()) {
		int leftIndex = 2 * pos;
		int smallChildIndex = leftIndex;
		if ((leftIndex + 1) < queue->size()) {
			int rightIndex = leftIndex + 1;
			if (queue->at(leftIndex).priority > queue->at(rightIndex).priority) {
				smallChildIndex = rightIndex;
			}
		}
		if (queue->at(smallChildIndex).priority >= queue->at(pos).priority) {
			break;
		}
		iter_swap(queue->begin() + pos, queue->begin() + smallChildIndex);
		pos = smallChildIndex;
	}
}

//finds item x in the priority queue and returns its index
int PriorityQueue::findItem(int x) {
	int ret = 0;
	for (int i = 0; i < queue->size(); i++) {
		if (queue->at(i).item == x) {
			ret = i;
		}
	}
	return ret;
}

PriorityQueue::PriorityQueue() {
	queue = new vector<node>();
	node empty = { 0,0 };
	queue->push_back(empty);
}

PriorityQueue::~PriorityQueue() {
	queue->~vector();
}

//removes and returns the top element of the queue
node PriorityQueue::removeMin() {
	//swap top element with last eleement.
	node min = queue->at(1);
	iter_swap(queue->begin() + 1, queue->begin() + size());
	//remove the last element
	queue->pop_back();
	downheap(1);
	return min;
}

//changes the priority of an item in the queue
void PriorityQueue::chgPriority(int item, int priority) {
	//find the item in the priority queue
	int p = findItem(item);
	queue->at(p).priority = priority;
	//check to upheap or downheap after change
	if (p > 0 && queue->at(p).priority < queue->at(p / 2).priority) {
		upheap(p);
	}
	else {
		downheap(p);
	}
}

//inserts item into queue
void PriorityQueue::insert(int item, int priority) {
	node tmp;
	tmp.item = item;
	tmp.priority = priority;
	queue->push_back(tmp);
	upheap(size());
}

//returns the top element of the queue
node PriorityQueue::top() {
	return queue->at(1);
}

//returns the size of the queue
int PriorityQueue::size() {
	return queue->size() - 1;
}

//get the priority of an item in the priority queue.
int PriorityQueue::getPriority(int item) {
	int p = INT_MAX;
	for (int i = 0; i < queue->size(); i++) {
		if (queue->at(i).item == item) {
			p = queue->at(i).priority;
		}
	}
	return p;
}