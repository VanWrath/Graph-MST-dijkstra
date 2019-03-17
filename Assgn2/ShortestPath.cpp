#include "stdafx.h"
#include "ShortestPath.h"

using namespace std;

ShortestPath::ShortestPath() {
	g = new Graph();
	distance = new int[g->numVertices()];
	path = new node[g->numVertices()];
	node empty = { 0,-1 }; //dummy node to represent null.
	q = new PriorityQueue();
	for (int i = 0; i < g->numVertices(); i++) {
		path[i] = empty;
	}
}

//constructor takes in a density and distance to generate a random graph
ShortestPath::ShortestPath(int density, int dist) {
	g = new Graph();
	g->generateRandom(density, dist);
	q = new PriorityQueue();
	path = new node[g->numVertices()];
	distance = new int[g->numVertices()];
	node empty = { 0,-1 };
	for (int i = 0; i < g->numVertices(); i++) {
		path[i] = empty;
	}
}

ShortestPath::~ShortestPath(){
	q->~PriorityQueue();
	g->~Graph();
	delete [] distance;
	delete []  path;
}

//find shortest path between s and d using Dijkstra's algorithm and saves the path in the path array
void ShortestPath::findPath(int s, int d) {
	node u;
	distance[s] = 0;
	q->insert(s, distance[s]);

	//populate priority queue
	for (int i = 0; i < g->numVertices(); i++) {
		if (i != s) {
			distance[i] = INT_MAX;
			q->insert(i, distance[i]);
		}
	}

	while (q->size() != 0) {
		//look at the first item in the priority queue
		u = q->removeMin();
		//for each vertex adjacent to u, calculate the distance from u and change priority
		vector<int> adjU = g->neighbors(u.item);
		for (int v = 0; v < adjU.size(); v++) {
			if (distance[adjU[v]] >(u.priority + g->getEdgeValue(adjU[v], u.item))) {
				distance[adjU[v]] = u.priority + g->getEdgeValue(adjU[v], u.item);
				q->chgPriority(adjU[v], u.priority + g->getEdgeValue(adjU[v], u.item));
				path[adjU[v]].copy(u);
			}
		}
	}
}

//return the path cost associated with the shortest path.
int ShortestPath::pathSize(int s, int d) {
	findPath(s, d);
	return distance[d];
}

//prints out the shortest path
void ShortestPath::printSP(int d) {
	if (path[d].item < 0) {
		return;
	}
	printSP(path[d].item);
	cout << to_string(path[d].item) << ", ";
}