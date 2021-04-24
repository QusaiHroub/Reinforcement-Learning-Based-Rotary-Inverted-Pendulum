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

#include <cmath>

#include "type.hh"

const float_4b PI = 3.1415929;

float_4b angleNormalize(const float_4b angle) {
	float_4b result = fmod((angle + PI), (2 * PI));
	if (result < 0.0) {
		result += 2.0 * PI;
	}
	return result - PI;
}

#endif