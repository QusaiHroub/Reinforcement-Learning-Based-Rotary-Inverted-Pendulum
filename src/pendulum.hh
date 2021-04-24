/* pendulum.hh
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

#ifndef PENDULUM_HH
#define PENDULUM_HH

#include "utils/motor.hh"
#include "utils/pins.hh"
#include "utils/type.hh"
#include "utils/pstate.hh"
#include "utils/encoders.hh"
#include "utils/timer.hh"
#include "utils/qthread.hh"

class Pendulum {
	Motor *const M_MOTOR = new Motor(MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_ENABLE_DC_1);
	MotorEncoder *const M_MOTOR_ENCODER =
		new MotorEncoder(MOTOR_ENCODER_WIRE_A, MOTOR_ENCODER_WIRE_B);

	Timer mMotorVelocityTimer;
	QThread mUpdateStateThread;
	PState mState;

public:
	Pendulum();
	~Pendulum();

	void updateMotorPWM(const int_16b);
	void stopMotor();
	PState getState();
};

#endif