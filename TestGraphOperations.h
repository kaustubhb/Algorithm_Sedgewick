#ifndef TESTSEARCH_H_
#define TESTSEARCH_H_

#include "Graph.h"
#include "GraphUtils.h"
#include <fstream>
#include <iostream>
using namespace std;

int testGraphInput() {
	std::ifstream fin("tinyG.txt");
	if(!fin) {
		std::cerr << "File read error" << std::endl;
		return 0;
	}
	Graph g(fin);
	std::cout << GraphUtils::toString(g);
	return 0;
}

void testDepthFirstSearch(string filename, int source) {
	ifstream fin(filename);
	Graph g(fin);

	DepthFirstSearch search(g, source);
	// find all the reachable vertices
	for(int i=0;i<g.V();++i) {
		if(search.marked(i))
			cout << i << " ";
	}
	cout << endl;
	// check if it's connected;
	if(search.count() != g.V())
		cout << "NOT ";
	cout << "Connected" << endl;
}

void testDepthFirstPaths(string filename, int src) {
	ifstream fin(filename);
	Graph g(fin);
	DepthFirstPaths paths(g,src);
	// print paths to all vertices from source
	for(int i=0;i<g.V();++i) {
		if(paths.hasPathTo(i)) {
			cout << i << " : ";
			vector<int> path = paths.pathTo(i);
			for(int x: path) {
				cout << x << " ";
			}
			cout << endl;
		}
	}
}

void testBreadthFirstPaths(string filename, int src) {
	ifstream fin(filename);
	Graph g(fin);
	BreadthFirstPaths paths(g,src);
	// print paths to all vertices from source
	for(int i=0;i<g.V();++i) {
		if(paths.hasPathTo(i)) {
			cout << i << " : ";
			vector<int> path = paths.pathTo(i);
			for(int x: path) {
				cout << x << " ";
			}
			cout << endl;
		}
	}
}

void testConnectedComponents(string filename) {
	ifstream fin(filename);
	Graph g(fin);

	CC cc(g);
	cout << cc.count() << " components" <<endl;
	vector<vector<int> > components(cc.count());
	for(int i=0;i<g.V();++i) {
		components[cc.id(i)].push_back(i);
	}
	for(size_t i=0;i<components.size();++i) {
		cout << "Component " << i << " : ";
		for(int c: components[i]) {
			cout << c << " ";
		}
		cout << endl;
	}
}

void testCycle(string filename) {
	ifstream fin(filename);
	Graph g(fin);

	Cycle cycle(g);
	cout << "hasCycle: " << cycle.hasCycle() << endl;
}

void testSymbolGraph(string filename, string delim) {
	SymbolGraph sg(filename, delim);
	const Graph g = sg.G();

	cout << "Number of vertices: " << g.V() << endl;
	for(int i=0;i<g.V();++i) {
		cout << sg.name(i) << endl;
		for(int j: g.adj(i)) {
			cout << "\t" << sg.name(j) << endl;
		}
	}
}

#endif /* TESTSEARCH_H_ */










