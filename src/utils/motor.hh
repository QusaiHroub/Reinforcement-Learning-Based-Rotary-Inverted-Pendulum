/* util/motor.hh
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

#ifndef MOTOR_HH
#define MOTOR_HH

class Motor {
	const char mMotorPin1;
	const char mMotorPin2;
	const char mMotorPWM;

	void turnCCT();
	void turnCT();
	void stop();

public:
	Motor(char, char, char);
	~Motor();

	void act(short);
};

#endif