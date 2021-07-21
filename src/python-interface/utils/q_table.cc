/* python-interface/utils/q_table.cc
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

#include "../../utils/type.hh"
#include "../../utils/q_table.hh"
#include "../../utils/state.hh"

extern "C" {
  QTable* QTable_new() {
      return new QTable();
  }

  void QTable_del(State* self) {
      delete self;
  }

  float_32b get(QTable *self, State *state, int action) {
    return self->get(*state, action);
  }

  void set(QTable *self, State *state, int action, float_32b qValue) {
    self->set(*state, action, qValue);
  }
}
