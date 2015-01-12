#ifndef GRAPHUTILS_H_
#define GRAPHUTILS_H_
#include "Graph.h"
#include <string>
#include <vector>

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


#endif /* GRAPHUTILS_H_ */



















