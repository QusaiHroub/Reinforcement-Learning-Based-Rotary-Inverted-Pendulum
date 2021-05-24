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

#ifndef MATH
#define MATH

#include <cmath>

const double PI = 3.141592865358979;

 /**
 * angle normalize
 *
 * @tparam angle is double
 * @param angle - angle to normalize
 *
 * @return double - normalized angle
 */
double angleNormalize(const double angle);

template<typename T> T max(T a, T b) { 
  return (a > b)? a : b;
}

#endif