#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Graph implemented as adjacency matrix, with values representing the edge values.
class Graph {
private:
	//vector<vector<int>> * graph;
	int ** graph;
	int edgeCount;
	int size;

public:
	Graph();
	Graph(int s);
	Graph(ifstream *f);
	~Graph();
	int MSTCost;
	int numVertices();
	int numEdges();
	bool adjacent(int i, int j);
	vector<int> neighbors(int i);
	int getEdgeValue(int x, int y);
	void setEdgeValue(int x, int y, int value);
	void add(int x, int y);
	void generateRandom(int density, int distance);
	void toString();
	Graph* MST();
};