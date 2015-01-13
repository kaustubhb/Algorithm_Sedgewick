/*
 * Graph.h
 *
 *  Created on: 10-Jan-2015
 *      Author: kaustubh
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <vector>
#include <string>
#include <map>

class Graph {
public:
	Graph(int v);	// v vertex graph with no edges (yet)
	Graph(std::ifstream &fin);	// read a graph from stream

	int V() const { return fV;};	// no of vertices
	int E() const { return fE;};	// no of edges
	void addEdge(int u, int v);
	std::vector<int> adj(int v) const;		// all vertices adjacent to v

private:
	int fV;
	int fE;
	std::vector<std::vector<int> > fAdjLst;
};

class SymbolGraph {
public:
	SymbolGraph(const std::string &filename, const std::string &delim);
	~SymbolGraph();
	bool contains(const std::string &key) const;	// is this key a vertex?
	int index(const std::string &key) const;
	std::string name(int v) const;
	const Graph& G() const;

private:
	std::map<std::string, int> fkeytoid;
	std::vector<std::string> split(const std::string &str, const std::string &delim);
	std::vector<std::string> fidtokey;
	Graph *gp;	// corresponding graph
};

class Digraph {
public:
	Digraph(int nv);	// no of vertices
	Digraph(std::ifstream &fin);
	int V() const;
	int E() const;
	void addEdge(int u, int v);
	std::vector<int> adj(int v) const;
};

#endif /* GRAPH_H_ */
