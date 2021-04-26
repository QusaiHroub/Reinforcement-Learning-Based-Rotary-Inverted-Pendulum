#ifndef UTILS
#define UTILS

#include "type.hh"
#include "math.hh"

template<typename T> uint_16b height(T *node) { 
    if (node == nullptr) {
      return 0;
    }
    return node->getHeight(); 
} 

template<typename T> T* rightRotate(T *y) { 
    T *x = y->getLeft(); 
    T *T2 = x->getRight(); 
 
    x->setRight(y); 
    y->setLeft(T2); 
 
    y->setHeight(max(height(y->getLeft()),
                    height(y->getRight())) + 1); 
    x->setHeight(max(height(x->getLeft()),
                    height(x->getRight())) + 1); 
 
    return x; 
} 
 
template<typename T> T *leftRotate(T *x) { 
    T *y = x->getRight(); 
    T *T2 = y->getLeft(); 
 
    y->setLeft(x); 
    x->setRight(T2); 
 
    y->setHeight(max(height(y->getLeft()),
                    height(y->getRight())) + 1); 
    x->setHeight(max(height(x->getLeft()),
                    height(x->getRight())) + 1);  
 
    return y; 
} 

template<typename T> int_16b getBalance(T *node) { 
    if (node == nullptr) {
      return 0;
    }
    return height(node->getLeft()) - height(node->getRight()); 
}

template<typename AType, typename QType> ActionNode<AType, QType>* 
minValueNode(ActionNode<AType, QType> *node) {  
  ActionNode<AType, QType> *current = node;  
  
  while (current->getLeft()) {
    current = current->getLeft();
  }

  return current;  
}

#endif