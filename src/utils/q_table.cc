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

float_32b QTable::get(PState &state, int_8b action) {
  int_16b target;

  target = state.getPendulumAngle() * PRECISION;
  L3SNType *l3SNode = mQTable->getNode(target);
  if (!l3SNode) {
    return NULL_VALUE;
  }
  L2STType *l2STType = l3SNode->getChaildTree();

  target = state.getPendulumAngularVelocity() * PRECISION;
  L2SNType *l2SNType = l2STType->getNode(target);
  if (!l2SNType) {
    return NULL_VALUE;
  }
  L1STType *l1STType = l2SNType->getChaildTree();

  target = state.getMotorAngle() * PRECISION;
  L1SNType *l1SNType = l1STType->getNode(target);
  if (!l1SNType) {
    return NULL_VALUE;
  }
  L0STType *l0STType = l1SNType->getChaildTree();

  target = state.getMotorAngularVelocity() * PRECISION;
  L0SNType *l0SNType = l0STType->getNode(target);
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

void QTable::set(PState &state, int_8b action, float_32b qValue) {
  int_16b target;

  target = state.getPendulumAngle() * PRECISION;
  L3SNType *l3SNode = mQTable->getNode(target);
  if (!l3SNode) {
    l3SNode = mQTable->insert(target);
  }
  L2STType *l2STType = l3SNode->getChaildTree();

  target = state.getPendulumAngularVelocity() * PRECISION;
  L2SNType *l2SNType = l2STType->getNode(target);
  if (!l2SNType) {
    l2SNType = l2STType->insert(target);
  }
  L1STType *l1STType = l2SNType->getChaildTree();

  target = state.getMotorAngle() * PRECISION;
  L1SNType *l1SNType = l1STType->getNode(target);
  if (!l1SNType) {
    l1SNType = l1STType->insert(target);
  }
  L0STType *l0STType = l1SNType->getChaildTree();

  target = state.getMotorAngularVelocity() * PRECISION;
  L0SNType *l0SNType = l0STType->getNode(target);
  if (!l0SNType) {
    l0SNType = l0STType->insert(target);
  }
  ATType *aTType = l0SNType->getChaildTree();

  ANType *aNType = aTType->getNodeByAction(action);
  if (!aNType) {
    aTType->insert(qValue, action);
  } else {
    aTType->update(aNType, qValue);
  }
}
