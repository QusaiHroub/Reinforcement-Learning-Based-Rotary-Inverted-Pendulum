/* util/pins.hh
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

#ifndef PINS_HH
#define PINS_HH

#include "type.hh"

const uint_8b MOTOR_PIN_1 = 10;
const uint_8b MOTOR_PIN_2 = 14;
const uint_8b MOTOR_ENABLE_DC_1 = 1;

const uint_8b MOTOR_ENCODER_WIRE_A = 0;
const uint_8b MOTOR_ENCODER_WIRE_B = 2;

const uint_8b PENDULUM_ENCODER_WIRE_A = 0;
const uint_8b PENDULUM_ENCODER_WIRE_B = 2;

#endif