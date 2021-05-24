/* util/q_table.cc
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

#include "q_table.hh"

QTable::QTable() {
  mQTable = new L3STType();
}

QTable::~QTable() {
  delete mQTable;
}

float_4b QTable::get(State &state, int_8b action) {
  L3SNType *l3SNode = mQTable->getNode(state[0]);
  if (!l3SNode) {
    return NULL_VALUE;
  }
  L2STType *l2STType = l3SNode->getChaildTree();

  L2SNType *l2SNType = l2STType->getNode(state[1]);
  if (!l2SNType) {
    return NULL_VALUE;
  }
  L1STType *l1STType = l2SNType->getChaildTree();

  L1SNType *l1SNType = l1STType->getNode(state[2]);
  if (!l1SNType) {
    return NULL_VALUE;
  }
  L0STType *l0STType = l1SNType->getChaildTree();

  L0SNType *l0SNType = l0STType->getNode(state[3]);
  if (!l0SNType) {
    return NULL_VALUE;
  }
  ATType *aTType = l0SNType->getChaildTree();

  ANType *aNType = aTType->getNodeByAction(action);
  if (!aNType) {
    return NULL_VALUE;
  }
  return aNType->getQValue();
}

void QTable::set(State &state, int_8b action, float_4b qValue) {
  L3SNType *l3SNode = mQTable->getNode(state[0]);
  if (!l3SNode) {
    l3SNode = mQTable->inseart(state[0]);
  }
  L2STType *l2STType = l3SNode->getChaildTree();

  L2SNType *l2SNType = l2STType->getNode(state[1]);
  if (!l2SNType) {
    l2SNType = l2STType->inseart(state[1]);
  }
  L1STType *l1STType = l2SNType->getChaildTree();

  L1SNType *l1SNType = l1STType->getNode(state[2]);
  if (!l1SNType) {
    l1SNType = l1STType->inseart(state[2]);
  }
  L0STType *l0STType = l1SNType->getChaildTree();

  L0SNType *l0SNType = l0STType->getNode(state[3]);
  if (!l0SNType) {
    l0SNType = l0STType->inseart(state[3]);
  }
  ATType *aTType = l0SNType->getChaildTree();

  ANType *aNType = aTType->getNodeByAction(action);
  if (!aNType) {
    aTType->inseart(qValue, action);
  } else {
    aTType->update(aNType, qValue);
  }
}
