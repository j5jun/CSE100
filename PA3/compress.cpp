#include <iostream>
#include <fstream>
#include <string>
#include "HCTree.h"
#include "HCNode.h"
#include "BitOutputStream.h"

using namespace std;

int main(int argc, char* argv[]){

    if(argc != 3){
    	cerr << "Input and output file names are required" << endl;
    	return 1;
    }

	ifstream inputFile;
	ofstream outputFile;

	//if the output file names are the same
	if(argv[1] == argv[2]){
		cerr << "Input and output file names cannot be the same" << endl;
		return -1;
	}

	inputFile.open(argv[1]);

	//if the file cannot be opened, exit.
	if(!inputFile.good() || !inputFile.is_open()){
		return -1;
	}

	//if the file is empty exit.
	if( inputFile.peek() == EOF){
		cout << "The input file is empty" << endl;
		outputFile.close();
		return -1;
	}

	//initializing a vector to print frequency of each character
	vector<int> freqs(256);

	//initializing unsigned char to store each character in the original.txt file
	int nextInt = 0;
	int totalnum = 0;
	int uniquenum = 0;

	while ( inputFile.peek() != EOF ) {
		nextInt = (int)inputFile.get();
		if(inputFile.eof()){
			break;
		}
		for(int i = 0; i < freqs.size(); i++){
			if(nextInt == i){
				if(freqs[i] == 0){
					uniquenum++;
				}
				freqs[i]++;
				totalnum++;
			}
		}
	}

	cout << "Frequency list updated" << endl;

	inputFile.close();

	//construct a Huffman tree
	HCTree tree;
	tree.build(freqs);

	cout << "Tree built" << endl;
	//create the encoded output file 
	outputFile.open(argv[2]);

	if(!outputFile.is_open() || !outputFile.good()){
		return -1;
	}

	//create the BitOutputStream using the "outputFile" ofstream
	BitOutputStream bout = BitOutputStream(outputFile);

	cout << "Writing header" << endl;
	tree.encode_header(totalnum, uniquenum, bout, outputFile);

	inputFile.open(argv[1]);


	cout << "Compressing File" << endl;

	int currnum = 0;
	unsigned char nextChar;
	outputFile << endl;
	while( inputFile.peek() != EOF && currnum < totalnum){
		nextChar = (unsigned char)inputFile.get();
		if(inputFile.eof()){
			break;
		}
		cout<< nextChar << endl;
		tree.encode(nextChar, bout);
		currnum++;
	}

	/* After the encoding is finished, if there are un-filled bits in the
	 * last byte, fill the rest of the bit places with 0 to ensure that the 
	 * byte is flushed to the buffer
	 */

	bout.flush();
	outputFile.flush();

	outputFile.close();

	return 0;
}