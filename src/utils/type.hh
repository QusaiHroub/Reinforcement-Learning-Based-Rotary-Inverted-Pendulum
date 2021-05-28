/* util/type.hh
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

#ifndef TYPE
#define TYPE

typedef char int_8b;
typedef unsigned char uint_8b;
typedef float float_4b;
typedef double float_8b;
typedef long double float_12_16b;
typedef short int_16b;
typedef unsigned short uint_16b;

template<typename AType, typename QType> class ActionNode {
  AType mAction;
  QType mQ_value;
  ActionNode *mLeft = nullptr;
  ActionNode *mRight = nullptr;

  uint_16b mHeight; 

  public: 
  ~ActionNode() {
  }

  void setAction(AType action) {
    mAction = action;
  }

  void setQValue(QType q_value) {
    mQ_value = q_value;
  }

  void setLeft(ActionNode *left) {
    mLeft = left;
  }

  void setRight(ActionNode *right) {
    mRight = right;
  }

  void setHeight(uint_16b height) {
    mHeight = height;
  }

  AType getAction() {
    return mAction;
  }

  QType getQValue() {
    return mQ_value;
  }

  ActionNode* getLeft() const {
    return mLeft;
  }

  ActionNode* getRight() const {
    return mRight;
  }

  uint_16b getHeight() const {
    return mHeight;
  } 
};

template<typename TreeType, typename StateType> class StateNode {
  StateType mState;
  TreeType *mTree = nullptr;
  StateNode *mLeft = nullptr;
  StateNode *mRight = nullptr;

  uint_16b mHeight;

  public: 
  ~StateNode() {
    delete mTree;
    delete mLeft;
    delete mRight;
    mTree = nullptr;
    mLeft = nullptr;
    mRight = nullptr;
  }

  void setState(StateType state) {
    mState = state;
  }

  void setChaildTree(TreeType *tree) {
    mTree = tree;
  }

  void setLeft(StateNode *left) {
    mLeft = left;
  }

  void setRight(StateNode *right) {
    mRight = right;
  }

  void setHeight(uint_16b height) {
    mHeight = height;
  }

  StateType getState() {
    return mState;
  }

  TreeType* getChaildTree() {
    return mTree;
  }

  StateNode* getLeft() const {
    return mLeft;
  }

  StateNode* getRight() const {
    return mRight;
  }

  uint_16b getHeight() const {
    return mHeight;
  } 
};

#endif
