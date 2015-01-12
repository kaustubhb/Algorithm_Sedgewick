#include "TestGraphOperations.h"

int main() {
//	testGraphInput();
//	testDepthFirstSearch("tinyG.txt", 0);
//	testDepthFirstSearch("tinyG.txt", 9);

//	testDepthFirstPaths("tinyCG.txt", 0);
//	testBreadthFirstPaths("tinyCG.txt", 0);

//	testConnectedComponents("tinyG.txt");

//	testCycle("noCycle.txt");
//	testCycle("tinyCG.txt");

	//testSymbolGraph("routes.txt", " ");
	//testSymbolGraph("movies.txt", "/");

	//testDegreesOfSeparation("movies.txt", "/", "Bacon, Kevin", "Kidman, Nicole");
	//testDegreesOfSeparation("movies.txt", "/", "Bacon, Kevin", "Grant, Cary");
	testDegreesOfSeparation("movies.txt", "/", "Pitt, Brad", "Jolie, Angelina");
}
