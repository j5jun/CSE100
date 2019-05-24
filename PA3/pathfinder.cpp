#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "HCTree.h"
#include "HCNode.h"

using namespace std;

int main(int argc, char* argv[]){

	if(argc != 5){
		cerr << "Invalid number of arguments" << endl;
    	return -1;
	}

	if(argv[1] == argv[4]){
		cerr << "Input and output files cannot be the same" << endl;
		return -1;
	}

	string inputFileName = argv[1];
	string weight = argv[2];
	string imdb = argv[3];
	string outputFileName = argv[4];

	if (weight == "u"){
		weight = false;
	}
	else if (weighted == "w"){
		weight = true;
	}
	else{
		cout << "invalid input for weighted or unweighted" << endl;
		return -1;
	}

	map<pair<string, int> set<string>>* movieactormap;

	ActorGraph graph;
	graph.loadFromFile(inputFileName, weight, movieactormap);

	ifstream inputFile(imdb);
	ofstream outputFile(outputFileName);




















	inputFile.open(argv[1]);
	if(!inputFile.is_open()){
		return -1;
	}

	if(inputFile.peek() == EOF){
		inputFile.close();
		return -1;
	}

	map<pair<string, int>, set<string>> movie_actor;

	cout << "CREATING THE GRAPH" << endl;
	ActorGraph();