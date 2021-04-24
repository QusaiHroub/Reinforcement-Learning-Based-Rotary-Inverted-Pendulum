/* util/motor.cc
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

#include "motor.hh"
#include <wiringPi.h>
#include <softPwm.h>

Motor::Motor(char motorPin1, char motorPin2, char motorPWM) :
		mMotorPin1(motorPin1), mMotorPin2(motorPin2),
		mMotorPWM(motorPWM) {

		pinMode(mMotorPin1, OUTPUT);
        pinMode(mMotorPin2, OUTPUT);
		softPwmCreate(mMotorPWM, PWM_OUTPUT, 100);

		stop();
}

Motor::~Motor() {
    stop();
}

void Motor::turnCCT() {
    digitalWrite(mMotorPin1, LOW);
    digitalWrite(mMotorPin2, HIGH);
}

void Motor::turnCT() {
    digitalWrite(mMotorPin1, HIGH);
    digitalWrite(mMotorPin2, LOW);
}

void Motor::stop() {
    digitalWrite(mMotorPin1, LOW);
    digitalWrite(mMotorPin2, LOW);
}

void Motor::act(short value) {
    if (value > 0) {
        softPwmWrite(mMotorPWM, value);
        turnCT();
    } else if (value < 0) {
        softPwmWrite(mMotorPWM, -1 * value);
        turnCCT();
    } else {
        softPwmWrite(mMotorPWM, value);
        stop();
    }
}
