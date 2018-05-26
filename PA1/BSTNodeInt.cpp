#include <iostream>

class BSTNodeInt {
public:
  int getValue();
  BSTNodeInt getLeftChild();
  BSTNodeInt getRightChild();
  BSTNodeInt getParent();
  
  void setLeftChild();
  void setRIghtChild();
  
private:
  int* value;
  BSTNodeInt leftchild;
  BSTNodeInt rightchild;
  BSTNodeInt parent;
};

BSTNodeInt::BSTNodeInt(const int & data){
  *value = data;
  leftchild = null;
  rightchild = null;
  parent = null;
}
