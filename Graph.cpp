#include "Graph.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

Graph::Graph(int v) {
	fV = v;
	fE = 0;
	for(int i=0;i<v;++i) {
		fAdjLst.push_back(vector<int>{});
	}
}

Graph::Graph(ifstream &fin) {
	int ed;
	fin >> fV >> ed;
	for(int i=0;i<fV;++i) {
		fAdjLst.push_back(vector<int>{});
	}
	for(int i=0;i<ed;++i) {
		int u,v;
		fin >> u >> v;
		addEdge(u,v);
	}
}

void Graph::addEdge(int u, int v) {
	fAdjLst[u].push_back(v);
	fAdjLst[v].push_back(u);
	++fE;
}

vector<int> Graph::adj(int v) const {
	return fAdjLst[v];
}

//===============================================================================

SymbolGraph::SymbolGraph(const string &filename, const string &delim): fkeytoid{}, fidtokey{} {
	ifstream fin(filename);
	int idx = 0;

	string str;
	while(getline(fin, str)) {
		vector<string> line = split(str, delim);
		for(string s: line) {
			if(fkeytoid.find(s) == fkeytoid.end()) { // not found
				fkeytoid.insert(make_pair(s,idx++));
			}
		}
	}

	for(int i=0;i<idx;++i)
		fidtokey.push_back("");

	for(auto p: fkeytoid) {
		fidtokey[p.second] = p.first;
	}
	// Now build the graph
	fin.close();
	fin.clear();
	fin.open(filename.c_str());
	gp = new Graph(idx);

	while(getline(fin, str)) {
		vector<string> line = split(str, delim);
		int v = index(line[0]);
		for(size_t i=1;i<line.size();++i) {
			gp->addEdge(v, index(line[i]));
		}
	}
}

SymbolGraph::~SymbolGraph() {
	delete gp;
}

vector<string> SymbolGraph::split(const string &str, const string &delim) {
	vector<string> result;
	size_t start=0,cur=0;

	while(cur < str.size()) {
		if( delim.find(str[cur]) != string::npos) { // current position is delimiter
			result.push_back(str.substr(start,cur-start));
			while(cur < str.size() && delim.find(str[cur]) != string::npos)
				++cur;
			start = cur;
		}
		else {
			++cur;
		}
	}
	if(start != cur)
		result.push_back(str.substr(start, cur-start));
	return result;
}

bool SymbolGraph::contains(const string &key) const{
	return fkeytoid.find(key) != fkeytoid.end();
}

string SymbolGraph::name(int v) const {
	if(static_cast<size_t>(v) < fidtokey.size())
		return fidtokey[v];
	return "";
}

int SymbolGraph::index(const string &key) const {
	if(contains(key)) {
		return fkeytoid.find(key)->second;
	}
	return -1;
}

const Graph& SymbolGraph::G() const{
	return *gp;
}

//===============================================================================

Digraph::Digraph(ifstream &fin): fEdges(0) {
	int ne;
	fin >> fVertices >> ne;

	for(int i=0;i<fVertices;++i)
		fAdj.push_back(vector<int>());

	while(ne--) {
		int u,v;
		fin >> u >> v;
		addEdge(u,v);
	}
}

Digraph::Digraph(int v): fVertices(v), fEdges(0), fAdj(v) {
}

void Digraph::addEdge(int u, int v) {
	fAdj[u].push_back(v);
	++fEdges;
}

int Digraph::V() const{
	return fVertices;
}

int Digraph::E() const {
	return fEdges;
}

vector<int> Digraph::adj(int v) const {
	return fAdj[v];
}

Digraph Digraph::reverse() const {
	Digraph rev(V());
	for(int i=0;i<V(); ++i) {
		for(int u: fAdj[i]) {
			rev.addEdge(u,i);
		}
	}
	return rev;
}




















