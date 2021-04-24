/* util/encoders.cc
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

#include <wiringPi.h>

#include "encoders.hh"

int_64b PendulumEncoder::Internal::encoder = 0;
int_32b PendulumEncoder::Internal::stateA = 0,
	PendulumEncoder::Internal::stateB = 0;
int_8b PendulumEncoder::*mWireA;
int_8b PendulumEncoder::*mWireB;

PendulumEncoder::PendulumEncoder(int_8b wireA, int_8b wireB) : mWireA (wireA), mWireB (wireB) {

	internal.mWireA = &mWireA;
	internal.mWireB = &mWireB;

	wiringPiISR(mWireA, INT_EDGE_BOTH, internal.A);
	wiringPiISR(mWireB, INT_EDGE_BOTH, internal.B);
}

void PendulumEncoder::Internal::A() {
    if (stateA == stateB) {
        encoder++;
    }
    stateA = digitalRead(*mWireA);
}


void PendulumEncoder::Internal::B() {
    if (stateA == stateB) {
        encoder--;
    }
    stateB = digitalRead(*mWireB);
}

void PendulumEncoder::ISR() {
  t++;
  if (t == 1) {
    angle_previous = getAngle ();
  }
  else if (t == 20) {
    angle_post = getAngle ();
  }
  else if (t == 21) {
    velocity = (angle_post - angle_previous) * 50;
    t = 0;
  }
}

float_4b PendulumEncoder::getAngle () {
	return internal.encoder * 360.0 / NUMBER_OF_FULL_ROTATE_PULSES;
}

float_4b PendulumEncoder::getVelocity () {
	return velocity;
}
