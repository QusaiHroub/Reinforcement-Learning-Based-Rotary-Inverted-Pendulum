/* util/qthread.hh
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

#ifndef QTHREAD_HH
#define QTHREAD_HH

#include <thread>
#include <atomic>

using namespace std;

class QThread {
	atomic<bool> active{true};

    public:
    	template<typename T>
        void start(T);
        void stop();
};

template<typename T>
void QThread::start(T function) {
	active = true;
	thread t([=]() {
		while(active.load()) {
			if(!active.load()) {
				return;
			}
			function();
		}
    });
    t.detach();
}

void QThread::stop() {
    active = false;
}

#endif