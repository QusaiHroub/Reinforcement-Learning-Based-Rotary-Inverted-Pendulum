/* pendulum.cc
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

 #include "pendulum.hh"

 Pendulum::Pendulum () {
 	mPendulumVelocityTimer.start([&]() {
        M_PENDULUM_ENCODER->ISR();
    });
 }

 Pendulum::~Pendulum () {
 	delete M_MOTOR;
 	delete M_PENDULUM_ENCODER;
 }

 void Pendulum::updateMotorPWM (const int_16b newValue) {
 	M_MOTOR->act (newValue);
 }

 void Pendulum::stopMotor () {
 	M_MOTOR->act (0);
 }

 PState Pendulum::getState () {
 	return PState(mState);
 }
