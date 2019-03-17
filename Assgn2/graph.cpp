#include "stdafx.h"
#include "graph.h"
#include "PriorityQueue.h"
#include <iostream>
#include <iomanip> 

//Constructor initializes graph indicies to 0
	Graph::Graph() {
		  size = 50; //default size to 50
		  MSTCost = 0;
		  graph = new int*[size];
		  for (int i = 0; i < size; ++i) {
			  graph[i] = new int[size];
			  for (int j = 0; j < size; j++) {
				  graph[i][j] = 0;
			  }
		  }
	  }

	  //constructor with specified number of vertices
	Graph::Graph(int s) {
		  size = s;
		  MSTCost = 0;
		  graph = new int*[size];
		  for (int i = 0; i < size; ++i) {
			  graph[i] = new int[size];
			  for (int j = 0; j < size; j++) {
				  graph[i][j] = 0;
			  }
		  }
	  }

	  //Constructor reading a file to construct a graph
	Graph::Graph(ifstream *f) {
		  istream_iterator<int> start(*f), end;
		  vector<int> nums(start, end);

		  size = nums[0];
		  MSTCost = 0;
		  graph = new int*[size];
		  for (int i = 0; i < size; ++i) {
			  graph[i] = new int[size];
			  for (int j = 0; j < size; j++) {
				  graph[i][j] = 0;
			  }
		  }

		  for (int i = 1; i < nums.size(); i += 3) {
			  setEdgeValue(nums[i], nums[i + 1], nums[i + 2]);
		  }
	  }

	Graph::~Graph() {
		delete [] graph;
		delete &edgeCount;
		delete &size;
	}

	  //returns the numver of vertices
	int Graph::numVertices() {
		  return size;
	  }

	  //returns the number of edges
	int Graph::numEdges() {
		  return edgeCount;
	  }

	  //tests whether there is an edge from node x to node y.
	bool Graph::adjacent(int i, int j) {
		  return (graph[i][j] > 0) ? true : false;
	  }

	  //returns a list of vertices that are adjacent to vertex i
	vector<int> Graph::neighbors(int i) {
		  vector <int> adjList;
		  for (int j = 0; j < size; j++) {
			  if (adjacent(i, j)) {
				  adjList.push_back(j);
			  }
		  }
		  return adjList;
	  }

	  //returns the value of an edge
	int Graph::getEdgeValue(int x, int y) {
		  return graph[x][y];
	  }

	  //change/set the value of an edge
	void Graph::setEdgeValue(int x, int y, int value) {
		  graph[x][y] = value;
		  graph[y][x] = value;
	  }

	  //adds an edge to graph
	void Graph::add(int x, int y) {
		  if (getEdgeValue(x, y) == 0) {
			  setEdgeValue(x, y, 1);
			  edgeCount++;
		  }
		  else {
			  cout << "Edge already exists" << endl;
		  }
	  }

	  //randomly generates a graph with specified density
	void Graph::generateRandom(int density, int distance) {
		  for (int i = 0; i < size; i++) {
			  for (int j = i; j < size; j++) {
				  if (i != j) {
					  if ((rand() % 100) < density) {
						  setEdgeValue(i, j, rand() % distance + 1);
					  }
				  }
			  }
		  }
	  }

	 //converts the graph to a string.
	void Graph::toString() {
		  cout << "\tG:  ";
		  for (int i = 0; i < size; i++) {
			  cout << setw(2) << i << "  ";
		  }
		  cout << endl;
		  for (int i = 0; i < size; i++) {
			  cout << "\t" << setw(2) << i << "  ";
			  for (int j = 0; j < size; j++) {
				  //if (j >= size - 1) {
				cout << setw(2) << graph[i][j] << "  ";
				 /* }
				  else {
					  out += to_string(graph[i][j]) + ", ";
				  }*/
			  }
			  cout << endl;
		  }
	  }

	  //Prim minimum spanning tree algorithm
	Graph* Graph::MST() {
		  //initialize algorithm
		  PriorityQueue *minQ = new PriorityQueue();
		  vector<int> cost(numVertices(), INT_MAX);
		  vector<int> endEdge(numVertices(), -1);
		  int s = (rand() % numVertices());
		  cost[s] = 0;
		  for (int i = 0; i < numVertices(); i++) {
			  minQ->insert(i, cost[i]);
		  }

		  //find minimum edges for MST
		  while (minQ->size() > 0) {
			  node u = minQ->removeMin();
			  cout << u.item << ", ";

			  vector<int> adjU = neighbors(u.item);
			  for (int i = 0; i < adjU.size(); i++) {
				  if (cost[adjU[i]] > getEdgeValue(u.item, adjU[i])) {
					  cost[adjU[i]] = getEdgeValue(u.item, adjU[i]);
					  endEdge[adjU[i]] = u.item;
					  minQ->chgPriority(adjU[i], cost[i]);
				  }
			  }
		  }
		  
		  //construct MST graph
		  Graph *f = new Graph(numVertices());
		  for (int i = 0; i < numVertices(); i++) {
			  if (endEdge[i] != -1) {
				  MSTCost += cost[i];
				  f->setEdgeValue(i, endEdge[i], cost[i]);
			  }
			  
		  }
		  return f;
	  }