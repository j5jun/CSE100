#include <iostream>
#include

class BST{
  public:
    BSTNodeInt root;
    int getMin();
    int getMax();
    int height();
    void insert(BSTNodeInt newNode);
    int find(int value);
    int size();
    void clear();
    bool empty();
    BSTNodeInt successor();
    
  private:  

};

BST::BST(BSTNodeInt rootNode){
  root = rootNode;
  min = rootNode->data;
  max = rootNode->data;
}

int getMin(){
  BSTNodeInt* compNode = this.root;
  while(compNode->leftChild != null){
    compNode = compNode->left;
  }
  return compNode->data;
}

int getMax(){
  BSTNodeInt* compNode = this.root;
  while(compNode->rightChild != null){
    compNode = compNode->right;
  }
  return compNode->data;
}

int height(){
  
}

void insert(BSTNodeInt newNode){
  BSTNodeInt* compNode = this.root;
  
  //CONDITION: if there is a corresponding child node to be compared to
  while(compNode != null)
  //if the value of the node to be inserted exists, cancel insertion.
  if(compNode->data == value)
    return;
   
  //if the value is greater than the data in the current node, check against the right child node
  else if (compNode->data < value){
    if(compNode->rightChild == null)
      compNode->rightChild = newNode;
    else
      compNode = compNode->rightChild;
  }
   
  //if the value is less than the data in the current node, check against the left child node
  else{
     if(compNode->leftChild == null)
      compNode->leftChild = newNode;
     else
      compNode = compNode->leftChild;  
}

int find(int value){
  BSTNodeInt* compNode = this.root;
  if(value < this.getMin() && value > this.getMin())
    return -1;
  
  //CONDITION: if there is a corresponding child node to be compared to
  while(compNode != null)
  //if the value is found, return the location of the node
  if(compNode->data == value)
    return
   
  //if the value is greater than the data in the current node, check against the right child node
  else if (compNode->data < value){
      compNode = compNode->rightChild;
  }
   
  //if the value is less than the data in the current node, check against the left child node
  else{
      compNode = compNode->leftChild;
  }
  
}

BSTNodeInt successor(BSTNodeInt* currNode){
  return currNode->parent;
}

void clear(){
 //traverse the BTS and erase each node except the root node
}

bool empty(){
  
}

