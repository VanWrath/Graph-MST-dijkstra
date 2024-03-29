#include "stdafx.h"
#include "ShortestPath.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	cout << "Running Dijkstra's shortest path Algorithm..." << endl;
	ShortestPath *sp1 = new ShortestPath(20, 10);
	//calculating average for path length for 20% density;
	int sum = 0;
	int numPaths = sp1->g->numVertices();
	for (int i = 0; i < sp1->g->numVertices(); i++) {
		int p = sp1->pathSize(0, i);
		if (p == INT_MAX) {
			numPaths--;
		}
		else {
			sum += p;
		}
	}
	cout << "The average path length for a random graph with density of 20% is: " << to_string(sum / numPaths) << endl;

	//calculating average for path length for 40% density;
	ShortestPath *sp2 = new ShortestPath(40, 10);
	sum = 0;
	numPaths =  sp2->g->numVertices();
	for (int i = 0; i < sp2->g->numVertices(); i++) {
		int p = sp2->pathSize(0, i);
		if (p == INT_MAX) {	//checks if there is a path and if not, disregard path.
			numPaths--;
		}
		else {
			sum += p;
		}
	}
	cout << "The average path length for a random graph with density of 40% is: " << to_string(sum / numPaths) << endl << endl;
	
	cout << "Running Minimum spanning tree Algorithm..." << endl;
	ifstream reader("graph_data.txt");
	if (!reader) {
		cout << "Error opening file." << endl;
	}
	else {
		Graph *g1 = new Graph(&reader);
		cout << "Graph read from file:" << endl;
		g1->toString();
		cout << "Tree edges of Minimum spanning tree: " << endl;
		Graph *MSTGraph = g1->MST();
		cout << "\nMST Cost: " << g1->MSTCost << endl;
		cout << "MST Graph: " << endl;
		MSTGraph->toString();
	}
	reader.close();

	getchar();
	return 0;
}
