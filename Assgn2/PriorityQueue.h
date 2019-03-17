#include "stdafx.h"
#include <vector>

using namespace std;

//node data structure to be stored in the Priority queue.
struct node {
	int priority;
	int item;
	void copy(node c) {
		priority = c.priority;
		item = c.item;
	};
};

//Priority queue class used to help find the shortest path in a graph. It is implemented as an array based min heap.
class PriorityQueue
{
private:
	vector<node> *queue;
	void upheap(int pos);
	void downheap(int pos);
	int findItem(int x);
public:
	PriorityQueue();
	~PriorityQueue();
	node removeMin();
	void chgPriority(int item, int priority);
	void insert(int item, int priority);
	node top();
	int size();
	int getPriority(int item);
};