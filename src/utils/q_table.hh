/* util/q_table.hh
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

#ifndef Q_TABLE
#define Q_TABLE

#include "q_table_type.hh"

#include "state.hh"

class QTable {

  L3STType *mQTable = nullptr;
  const uint_8b NUMBER_OF_LEVELS = 4;

  public:
  const float_32b NULL_VALUE = 1e9;

  QTable();
  ~QTable();

  float_32b get(State &state, int_8b action);
  void set(State &state, int_8b action, float_32b qValue);
};

#endif
