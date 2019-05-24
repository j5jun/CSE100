#include "HCNode.h"

typedef unsigned char byte;

using namespace std;

bool HCNode::operator<(const HCNode& other){
	if(count != other.count){
		return count > other.count;
	}
	else{
		return symbol > other.symbol;
	}
}