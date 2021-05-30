/* util/timer.hh
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

#ifndef TIMER_HH
#define TIMER_HH

#include <thread>
#include <atomic>

class Timer {
	std::atomic<bool> active{true};
	int mInterval = 1;

    public:
        void setInterval(int);
        void start(auto);
        void stop();
};

void Timer::setInterval(int interval) {
    if (interval > 0) {
        mInterval = interval;
    }
}

void Timer::start(auto function) {
    active = true;
    std::thread t([=]() {
        while(active.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(mInterval));
            if(!active.load()) {
            	return;
			}
            function();
        }
    });
    t.detach();
}

void Timer::stop() {
    active = false;
}

#endif