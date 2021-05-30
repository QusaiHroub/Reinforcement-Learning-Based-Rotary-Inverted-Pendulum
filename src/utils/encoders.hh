/* util/encoders.hh
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

#ifndef ENCODERS_HH
#define ENCODERS_HH

#include "type.hh"

class MotorEncoder {
	const float_32b NUMBER_OF_FULL_ROTATE_PULSES = 540.0;

	const int_8b mWireA;
	const int_8b mWireB;

	struct Internal {
		static int_64b encoder;
		static int_32b stateA, stateB;

		static const int_8b *mWireA;
		static const int_8b *mWireB;

		static void A();
		static void B();
	} internal;

	int_8b t = 0;
	float_32b angle_post, angle_previous, velocity;

public:
	MotorEncoder(int_8b, int_8b);
	float_32b getAngle();
	float_32b getVelocity();
	void ISR();
};

#endif