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
  ANType* insert(ANType *root, QType qValue, AType action);
  ANType* update(ANType *root, ANType *targetNode, QType qValue);
  ANType* getMaxQvalue(ANType *root);
  void clear(ANType *root);

  public:
  ~ActionTree();

  void insert(QType qValue, AType action);
  void update(ANType *targetNode, QType qValue);
  ANType* getNodeByAction(AType action);
  ANType* newNode(QType qValue, AType action);
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

  if (action < root->getAction()) {
    return getNodeByAction(root->getLeft(), action);
  }

  return getNodeByAction(root->getRight(), action);
}

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::deleteNode(ANType* root, ANType* targetNode) {  
  if (root == nullptr) {
    return root;
  } 

  if (targetNode == root) {
    root->setLeft(deleteNode(root->getLeft(), targetNode));
  } else if (targetNode->getAction() > root->getAction()) {
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
      root->setAction(temp->getAction());

      root->setRight(deleteNode(root->getRight(), temp));  
  }  
  return root;  
}  

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::newNode(QType qValue, AType action) {
  ANType *node = new ANType();
  node->setQValue(qValue);
  node->setAction(action);
  node->setLeft(nullptr);
  node->setRight(nullptr);

  return node;
}

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::insert(ANType *root, QType qValue, AType action) {
  if (root == nullptr) {
    return newNode(qValue, action);
  }

  if (action < root->getAction()) {
    root->setLeft(insert(root->getLeft(), qValue, action));
  } else if (action > root->getAction()) {
    root->setRight(insert(root->getRight(), qValue, action));
  }

  return root;    
}

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::update(ANType *root, ANType *targetNode, QType qValue) {
  AType action = targetNode->getAction();

  root = deleteNode(root, targetNode);  

  root = insert(root, qValue, action);

  return root;
}  

template<typename ANType, typename AType, typename QType>
ANType* ActionTree<ANType, AType, QType>::getMaxQvalue(ANType *root) {
  if (root == nullptr) {
    return nullptr;
  }

  ANType *left = getMaxQvalue(root->getRight());

  ANType *right = getMaxQvalue(root->getRight());

  if (left == nullptr) {
    return right;
  }

  if (right == nullptr) {
    return left;
  }

  return left->getQValue() > right->getQValue() ? left : right;
}

template<typename ANType, typename AType, typename QType>
void ActionTree<ANType, AType, QType>::clear(ANType *root) {
  if (root == nullptr) {
    return;
  }
  clear(root->getLeft());
  clear(root->getRight());

  delete root;
  root = nullptr;
}

template<typename ANType, typename AType, typename QType>
ActionTree<ANType, AType, QType>::~ActionTree() {
  clear(mRoot);
}

template<typename ANType, typename AType, typename QType>
void ActionTree<ANType, AType, QType>::insert(QType qValue, AType action) {
  mRoot = insert(mRoot, qValue, action);
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
