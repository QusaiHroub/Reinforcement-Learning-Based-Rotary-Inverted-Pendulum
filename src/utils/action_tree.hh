/* util/action_tree.hh
 *
 * This file is part of Reinforcement Learning-based Rotary Inverted Pendulum
 * Graduation Project.
 *
 * Authors:
 * Qusai Hroub <qusaihroub.r@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef ACTION_TREE
#define ACTION_TREE

template<typename ANType, typename AType, typename QType> class ActionTree {
  ANType *mRoot = nullptr;

  ANType* getNodeByAction(ANType *root, QType action);
  ANType* deleteNode(ANType* root, ANType* targetNode);
  ANType* inseart(ANType *root, QType qValue, AType action);
  ANType* update(ANType *root, ANType *targetNode, QType qValue);
  ANType* getMaxQvalue(ANType *root);
  void clear(ANType *root);

  public:
  ~ActionTree();

  void inseart(QType qValue, AType action);
  void update(ANType *targetNode, QType qValue);
  ANType* getNodeByAction(AType action);
  void clear();
};

#include "type.hh"
#include "utils.hh"

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::getNodeByAction(ANType *root, QType action) {
  if (!root) {
    return nullptr;
  }

  if (action == root->getAction()) {
    return root;
  }

  ANType *node = getNodeByAction(root->getRight(), action);
  if (node) {
    return node;
  }

  return getNodeByAction(root->getLeft(), action);
}

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::deleteNode(ANType* root, ANType* targetNode) {  
  if (root == nullptr) {
    return root;
  } 

  if (targetNode == root) {
    root->setLeft(deleteNode(root->getLeft(), targetNode));
  } else if (targetNode->getQValue() > root->getQValue()) { 
    root->setRight(deleteNode(root->getRight(), targetNode));
  } else {  
      if (!root->getLeft()) {  
          ANType *temp = root->getRight();  
          delete root;  
          return temp;  
      } else if (!root->getRight()) {  
          ANType *temp = root->getLeft();  
          delete root;  
          return temp;  
      }  

      ANType* temp = minValueNode(root->getRight());

      root->setQValue(temp->getQValue());  

      root->setRight(deleteNode(root->getRight(), temp));  
  }  
  return root;  
}  

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::inseart(ANType *root, QType qValue, AType action) {
  if (root == nullptr) {
    root = new ANType();
    root->setQValue(qValue);
    root->setAction(action);
    root->setLeft(nullptr);
    root->setRight(nullptr);
    
    return root;
  }

  if (qValue < root->getQValue()) {
    root->setLeft(inseart(root->getLeft(), qValue, action));
  } else {
    root->setRight(inseart(root->getRight(), qValue, action));
  }

  return root;    
}

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::update(ANType *root, ANType *targetNode, QType qValue) {
  AType action = targetNode->getAction();

  root = deleteNode(root, targetNode);  

  root = inseart(root, qValue, action);  

  return root;
}  

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::getMaxQvalue(ANType *root) {
  if (!root->getRight()) {
    return root;
  }

  return getMaxQvalue(root->getRight());
}

template<typename ANType, typename AType, typename QType>
void ActionTree<ANType, AType, QType>::clear(ANType *root) {
  delete root;
  root = nullptr;
}

template<typename ANType, typename AType, typename QType>
ActionTree<ANType, AType, QType>::~ActionTree() {
  clear(mRoot);
}

template<typename ANType, typename AType, typename QType>
void ActionTree<ANType, AType, QType>::inseart(QType qValue, AType action) {
  mRoot = inseart(mRoot, qValue, action);
}

template<typename ANType, typename AType, typename QType>
void ActionTree<ANType, AType, QType>::update(ANType *targetNode, QType qValue) {
  mRoot = update(mRoot, targetNode, qValue);
}

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::getNodeByAction(AType action) {
  return getNodeByAction(mRoot, action);
}

template<typename ANType, typename AType, typename QType>
void ActionTree<ANType, AType, QType>::clear() {
  clear(mRoot);
}

#endif
