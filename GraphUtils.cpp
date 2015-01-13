#include "GraphUtils.h"
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;

string GraphUtils::toString(const Graph &g) {
	stringstream ss;
	ss << "Vertices: " << g.V() << endl
			<< "Edges: " << g.E() << endl;

	for(int i=0;i<g.V();++i) {
		vector<int> v = g.adj(i);
		ss << i << " : ";
		for(size_t j=0;j<v.size();++j) {
			ss << v[j] << " ";
		}
		ss << endl;
	}
	return ss.str();
}
int GraphUtils::degree(const Graph &g, int v) {
	return g.adj(v).size();
}

int GraphUtils::maxDegree(const Graph &g) {
	int maxVal = 0,deg;
	for(int i=0;i<g.V();++i) {
		deg = degree(g,i);
		if(deg > maxVal)
			maxVal = deg;
	}
	return maxVal;
}

int GraphUtils::avgDegree(const Graph &g) {
	return 2*g.E()/g.V();
}

//===============================================================================

DepthFirstSearch::DepthFirstSearch(const Graph &g, int s): fVisited(g.V(),false), fCount(0) {
	dfs(g,s);
}

void DepthFirstSearch::dfs(const Graph &g, int s) {
	vector<int> edges = g.adj(s);
	fVisited[s] = true;
	++fCount;
	for(size_t i=0;i<edges.size();++i) {
		if(!fVisited[edges[i]])
			dfs(g, edges[i]);
	}
}

bool DepthFirstSearch::marked(int v) {
	return fVisited[v];
}

int DepthFirstSearch::count() {
	return fCount;
}

//================================================================================

DepthFirstPaths::DepthFirstPaths(const Graph &g, int src): fParents(g.V()), fVisited(g.V(),false) {
	for(int i=0;i<g.V();++i) {
		fParents[i] = i;
	}
	dfs(g,src);
}

void DepthFirstPaths::dfs(const Graph &g, int src) {
	fVisited[src] = true;
	for(int x: g.adj(src)) {
		if(fVisited[x] == false) {
			fParents[x] = src;
			dfs(g,x);
		}
	}
}

bool DepthFirstPaths::hasPathTo(int v) {
	if(v >= 0 && v < (int)fVisited.size())
		return fVisited[v];
	return false;
}

vector<int> DepthFirstPaths::pathTo(int v) {
	vector<int> path = {v};
	while(fParents[v] != v) {
		path.push_back(fParents[v]);
		v = fParents[v];
	}
	reverse(path.begin(),path.end());
	return path;
}

//================================================================================

BreadthFirstPaths::BreadthFirstPaths(const Graph &g, int src): fParents(g.V()), fVisited(g.V(), false){
	for(int i=0;i<g.V();++i)
		fParents[i] = i;

	queue<int> q;
	q.push(src);
	fVisited[src] = true;

	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int v: g.adj(x)) {
			if(!fVisited[v]) {
				q.push(v);
				fVisited[v] = true;
				fParents[v] = x;
			}
		}
	}
}

bool BreadthFirstPaths::hasPathTo(int v) {
	if(v >= 0 && v < (int)fVisited.size())
		return fVisited[v];
	return false;
}

vector<int> BreadthFirstPaths::pathTo(int v) {
	vector<int> path = {v};
	while(fParents[v] != v) {
		path.push_back(fParents[v]);
		v = fParents[v];
	}
	reverse(path.begin(),path.end());
	return path;
}

//================================================================================

CC::CC(const Graph &g): fCount(0), fVisited(g.V(), false), fIds(g.V()) {
	for(int i=0;i<g.V();++i) {
		if(fVisited[i] == false) {
			dfs(g, i);
			++fCount;
		}
	}
}

void CC::dfs(const Graph &g, int src) {
	fVisited[src] = true;
	fIds[src] = fCount;
	for(int i: g.adj(src)) {
		if(!fVisited[i]) {
			dfs(g, i);
		}
	}
}

int CC::count() {
	return fCount;
}

bool CC::connected(int v, int w) {
	return id(v) == id(w);
}

int CC::id(int v) {
	return fIds[v];
}

//================================================================================

Cycle::Cycle(const Graph &g): fCycle(false), fVisited(g.V(), false) {
	for(int i=0;i<g.V();++i) {
		if(!fVisited[i])
			dfs(g, i, i);
	}
}

void Cycle::dfs(const Graph &g, int v, int u) {
	fVisited[v] = true;
	for(int w: g.adj(v)) {
		if(!fVisited[w])
			dfs(g, w, v);
		else {
			if(w != u)
				fCycle = true;
		}
	}
}

bool Cycle::hasCycle() {
	return fCycle;
}

//================================================================================

TwoColor::TwoColor(const Graph &g): fIsTwoColorable(true), fVisited(g.V(), false), fColor(g.V(), false) {
	for(int i=0;i<g.V();++i) {
		if(!fVisited[i]) {
			fColor[i] = false;
			dfs(g, i);
		}
	}
}

void TwoColor::dfs(const Graph & g, int v) {
	fVisited[v] = true;
	for(int w: g.adj(v)) {
		if(!fVisited[w]) {
			fColor[w] = !fColor[v];
			dfs(g,w);
		}
		else {
			if(fColor[w] == fColor[v])
				fIsTwoColorable = false;
		}
	}
}

bool TwoColor::isBipartite() {
	return fIsTwoColorable;
}

//================================================================================

DegreesOfSeparation::DegreesOfSeparation(const string &filename, const string &delim, const string &src) {
	fSG = new SymbolGraph(filename,delim);
	const Graph g = fSG->G();
	fPaths = new BreadthFirstPaths(g,fSG->index(src));
}

DegreesOfSeparation::~DegreesOfSeparation() {
	delete fPaths;
	delete fSG;
}

vector<string> DegreesOfSeparation::getPathFrom(const string &to) {
	vector<string> path;
	int idTo = fSG->index(to);
	if(fPaths->hasPathTo(idTo)) {
		for(int x: fPaths->pathTo(idTo)) {
			path.push_back(fSG->name(x));
		}
	}
	return path;
}

//================================================================================

DirectedDFS::DirectedDFS(const Digraph &dg, int src): fVisited(dg.V(), false) {
	dfs(dg, src);
}

DirectedDFS::DirectedDFS(const Digraph &dg, vector<int> sources):fVisited(dg.V(), false) {
	for(int i: sources) {
		if(!marked(i))
			dfs(dg, i);
	}
}

bool DirectedDFS::marked(int v) {
	if(v >= 0 && v < (int)fVisited.size())
		return fVisited[v];
	return false;
}

void DirectedDFS::dfs(const Digraph &dg, int u) {
	fVisited[u] = true;
	for(int v: dg.adj(u)) {
		if(!marked(v))
			dfs(dg, v);
	}
}















