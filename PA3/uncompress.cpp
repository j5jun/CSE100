#include <iostream>
#include <fstream>
#include <string>
#include "HCTree.h"
#include "HCNode.h"

using namespace std;

int main(int argc, char* argv[]){

	if(argc != 3){
    	cerr << "Input and output file names are required" << endl;
    	return 1;
    }

	ifstream inputFile;
	ofstream outputFile;
	vector<int> freqs(256); 

	int totalnum = 0;
	int uniquenum = 0;
	unsigned char nextCharInt;
	string str;

	if(argv[1] == argv[2]){
		return -1;
	}

	inputFile.open(argv[1]);
	if(!inputFile.is_open() || !inputFile.good()){
		return -1;
	}

	if( inputFile.peek() == EOF ) { // empty file
        inputFile.close();
        return -1;
    }

	//declare BitIntputStream to perform Bit I/O
	BitInputStream bin = BitInputStream(inputFile);

	getline(inputFile, str);
	totalnum = stoi(str, nullptr, 0);
	cout << totalnum << endl;
	getline(inputFile, str);
	uniquenum = stoi(str, nullptr, 0);
	cout << uniquenum << endl;

	// single unique character, print the character totalnum of times
	if(uniquenum == 1){
		outputFile.open(argv[2]);
		char oneChar= inputFile.get();
		for(int i = 0; i < totalnum; i++){
			outputFile << oneChar;
		}
	}

	/*
	int numchar = 0;
	for(int i = 0; i < 256; i++) {
		getline(inputFile, str);
		nextInt = stoi(str, nullptr, 0);
		//Update the frequency and the number of unique characters
		if(nextInt != 0){
			freqs[i] = (char)nextInt;
			numchar = numchar+nextInt;
		}
	}
	*/
	
	cout << "Building the tree" << endl;
	//construct a Huffman tree
	HCTree tree;
	tree.build(bin, inputFile);

	//create the encoded output file 
	outputFile.open(argv[2]);
	if(!outputFile.is_open() || !outputFile.good()){
		return -1;
	}

	//add condition to stop reading when the last character was read
	for(int j = 0; j < totalnum; j++){
		byte i = tree.decode(bin);
		outputFile.put(i);
	}

	inputFile.close();
	outputFile.close();

	return 0;
}