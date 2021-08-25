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

#pragma once

#include "utils/motor.hh"
#include "utils/pins.hh"
#include "utils/type.hh"
#include "utils/pstate.hh"
#include "utils/encoders.hh"
#include "utils/timer.hh"
#include "utils/qthread.hh"
#include "utils/constants.hh"

#include <wiringPi.h>

class Pendulum {
	Motor *mMotor;
	Encoder *mMotorEncoder, *mPendulumEncoder;

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

Pendulum::Pendulum () {
	wiringPiSetup();
	mMotor = new Motor(MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_ENABLE_DC_1);
	mMotorEncoder = new Encoder(MOTOR_ENCODER_WIRE_A, MOTOR_ENCODER_WIRE_B, MOTOR_ENCODER_CPR);
	mPendulumEncoder = new Encoder(PENDULUM_ENCODER_WIRE_A, PENDULUM_ENCODER_WIRE_B, PENDULUM_ENCODER_CPR);

	mMotorVelocityTimer.start([&]() {
		mMotorEncoder->ISR();
		mPendulumEncoder->ISR();
	});

	mUpdateStateThread.start([&]() {
   		mState.setMotorAngle (convertDegToRad (mMotorEncoder->getAngle ()));
    		mState.setMotorAngularVelocity (convertDegToRad (
    			mMotorEncoder->getVelocity ()));
    		mState.setPendulumAngle (convertDegToRad (mPendulumEncoder->getAngle ()));
    		mState.setPendulumAngularVelocity (convertDegToRad (
    			mPendulumEncoder->getVelocity ()));
	});
}

Pendulum::~Pendulum () {
	delete mMotor;
 	delete mMotorEncoder;
}

void Pendulum::updateMotorPWM (const int_16b newValue) {
 	mMotor->act (newValue);
}

void Pendulum::stopMotor () {
 	mMotor->act (0);
}

PState Pendulum::getState () {
 	return PState(mState);
}

#endif