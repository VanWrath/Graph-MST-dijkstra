#include "PriorityQueue.h"
#include "graph.h"

class ShortestPath
{
private:
	PriorityQueue * q;
	int *distance;
	node *path;
public:
	Graph * g;
	ShortestPath();
	ShortestPath(int density, int dist);
	~ShortestPath();
	void findPath(int s, int d);
	int pathSize(int s, int d);
	void printSP(int d);
};

