#ifndef GRAPHUTILS_H_
#define GRAPHUTILS_H_
#include "Graph.h"
#include <string>
#include <vector>
#include <stack>

class GraphUtils {
public:
	static std::string toString(const Graph &g);
	static int degree(const Graph &g, int v);	// self loop is counted twice
	static int maxDegree(const Graph &g);
	static int avgDegree(const Graph &g);
};

class DepthFirstSearch {
public:
	DepthFirstSearch(const Graph &g, int s);
	bool marked(int v);
	int count();

private:
	std::vector<bool> fVisited;
	int fCount;
	void dfs(const Graph &g, int s);
};

class DepthFirstPaths {
public:
	DepthFirstPaths(const Graph &g, int src);
	bool hasPathTo(int v);
	std::vector<int> pathTo(int v);

private:
	std::vector<int> fParents;
	std::vector<bool> fVisited;
	void dfs(const Graph &g, int src);
};

class BreadthFirstPaths {
public:
	BreadthFirstPaths(const Graph &g, int src);
	bool hasPathTo(int v);
	std::vector<int> pathTo(int v);

private:
	std::vector<int> fParents;
	std::vector<bool> fVisited;
};

// Connected Components
class CC {
public:
	CC(const Graph &c);
	bool connected(int v, int w);
	int count();
	int id(int v);	// component identifier

private:
	int fCount;		// no of connected components
	std::vector<bool> fVisited;
	std::vector<int> fIds;
	void dfs(const Graph &g, int src);
};

// Cycle detection
class Cycle {
public:
	Cycle(const Graph &g);
	bool hasCycle();

private:
	bool fCycle;
	std::vector<bool> fVisited;
	void dfs(const Graph &g, int v, int u);		// edge from u to v in dfs
};

class TwoColor {
public:
	TwoColor(const Graph &g);
	bool isBipartite();

private:
	bool fIsTwoColorable;
	std::vector<bool> fVisited;
	std::vector<bool> fColor;
	void dfs(const Graph &g, int v);
};

class DegreesOfSeparation {
public:
	DegreesOfSeparation(const std::string &filename, const std::string &delim, const std::string &src);
	~DegreesOfSeparation();
	std::vector<std::string> getPathFrom(const std::string &to);

private:
	BreadthFirstPaths *fPaths;
	SymbolGraph *fSG;
};

class DirectedDFS {
public:
	DirectedDFS(const Digraph &dg, int src);
	DirectedDFS(const Digraph &dg, std::vector<int> sources);
	bool marked(int v);

private:
	void dfs(const Digraph &dg, int u);
	std::vector<bool> fVisited;
};

class DirectedCycle {
public:
	DirectedCycle(const Digraph &dg);
	bool hasCycle();
	std::stack<int> cycle();

private:
	std::vector<bool> fvisited;
	std::vector<bool> fonstack;
	std::vector<int> fparent;
	std::stack<int> fcycle;
	bool fHasCycle;
	void dfs(const Digraph &dg, int src);
};

#endif /* GRAPHUTILS_H_ */



















