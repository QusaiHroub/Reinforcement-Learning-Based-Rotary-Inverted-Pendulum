/* util/state_tree.hh
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

#ifndef STATE_TREE
#define STATE_TREE

template<typename SNType, typename TType, typename SType> class StateTree {
  SNType *mRoot = nullptr;
  SNType *returnNode = nullptr;

  SNType* getNode(SNType *root, SType state);
  SNType* insert(SNType *root, SType state);
  SNType* newNode(SType state);
  void clear(SNType *root);

  public:
  ~StateTree();

  SNType* insert(SType state);
  SNType* getNode(SType state);
  void clear();
};

#include "type.hh"
#include "math.hh"
#include "utils.hh"

template<typename SNType, typename TType, typename SType>
SNType* StateTree<SNType, TType, SType>::getNode(SNType *root, SType state) {
  if (!root) {
    return nullptr;
  }

  if (state == root->getState()) {
    return root;
  }

  if (state < root->getState()) {
    return getNode(root->getLeft(), state);
  }
  
  return getNode(root->getRight(), state);
}

template<typename SNType, typename TType, typename SType>
SNType* StateTree<SNType, TType, SType>::newNode(SType state) {
  SNType *node = new SNType();
  node->setState(state);
  node->setChaildTree(new TType());
  node->setLeft(nullptr);
  node->setRight(nullptr);
  node->setHeight(1);

  return node;
}

template<typename SNType, typename TType, typename SType>
SNType* StateTree<SNType, TType, SType>::insert(SNType *root, SType state) {
  if (root == nullptr) {
    root = newNode(state);
    returnNode = root;

    return root;
  }

  if (state < root->getState()) {
    root->setLeft(insert(root->getLeft(), state));
  } else if (state > root->getState()) {
    root->setRight(insert(root->getRight(), state));
  } else {
    returnNode = root;
    return root;
  }

  root->setHeight(1 + max(height(root->getLeft()),
                      height(root->getRight())));
  int_16b balance = getBalance(root);

  if (balance > 1 && state < root->getLeft()->getState()) {
    return rightRotate(root);
  }

  if (balance < -1 && state > root->getRight()->getState()) {
    return leftRotate(root);
  }

  if (balance > 1 && state > root->getLeft()->getState()) {
      root->setLeft(leftRotate(root->getLeft()));
      return rightRotate(root);
  }

  if (balance < -1 && state < root->getRight()->getState()) {
      root->setRight(rightRotate(root->getRight()));
      return leftRotate(root);
  }

  return root;
}

template<typename SNType, typename TType, typename SType>
void StateTree<SNType, TType, SType>::clear(SNType *root) {
  if (root != nullptr) {
    delete root;
  }
}

template<typename SNType, typename TType, typename SType>
StateTree<SNType, TType, SType>::~StateTree() {
  clear(mRoot);
}

template<typename SNType, typename TType, typename SType>
SNType* StateTree<SNType, TType, SType>::insert(SType state) {
  mRoot = insert(mRoot, state);
  return returnNode;
}

template<typename SNType, typename TType, typename SType>
SNType* StateTree<SNType, TType, SType>::getNode(SType state) {
  return getNode(mRoot, state);
}

template<typename SNType, typename TType, typename SType>
void StateTree<SNType, TType, SType>::clear() {
  clear(mRoot);
}

#endif
