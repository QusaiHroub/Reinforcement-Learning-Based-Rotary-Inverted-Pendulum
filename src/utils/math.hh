/* util/math.hh
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

#ifndef MATH_HH
#define MATH_HH

#pragma once

#include <cmath>

#include "type.hh"

const float_32b PI = 3.1415929;
const float_32b RAD = 57.2957795;

float_32b angleNormalize(const float_32b angle) {
	float_32b result = fmod((angle + PI), (2 * PI));
	if (result < 0.0) {
		result += 2.0 * PI;
	}
	return result - PI;
}

float_32b convertDegToRad(const float_32b angle) {
	return angle * (PI * RAD / 180);
}

template<typename T> T max(T a, T b) { 
  return (a > b) ? a : b;
}

#endif
