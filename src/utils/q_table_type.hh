/* util/q_table_type.hh
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

#ifndef Q_TABLE_TYPE
#define Q_TABLE_TYPE

#include "type.hh"
#include "action_tree.hh"
#include "state_tree.hh"

template class ActionNode<int_16b, float_32b>;
using ANType = ActionNode<int_16b, float_32b>;
template class ActionTree<ANType, int_16b, float_32b>;
using ATType = ActionTree<ANType, int_16b, float_32b>;

template class StateNode<ATType, int_16b>;
using L0SNType = StateNode<ATType, int_16b>;
template class StateTree<L0SNType, ATType, int_16b>;
using L0STType = StateTree<L0SNType, ATType, int_16b>;
template class StateNode<L0STType, int_16b>;
using L1SNType = StateNode<L0STType, int_16b>;
template class StateTree<L1SNType, L0STType, int_16b>;
using L1STType = StateTree<L1SNType, L0STType, int_16b>;
template class StateNode<L1STType, int_16b>;
using L2SNType = StateNode<L1STType, int_16b>;
template class StateTree<L2SNType, L1STType, int_16b>;
using L2STType = StateTree<L2SNType, L1STType, int_16b>;
template class StateNode<L2STType, int_16b>;
using L3SNType = StateNode<L2STType, int_16b>;
template class StateTree<L3SNType, L2STType, int_16b>;
using L3STType = StateTree<L3SNType, L2STType, int_16b>;

#endif
