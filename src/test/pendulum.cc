#include <iostream>
#include "../pendulum.hh"
#include "../utils/pstate.hh"
#include <wiringPi.h>

using namespace std;

auto main () -> int {

    Pendulum pendulum;
    PState pState;

    while (true) {
        pendulum.getState();
        pState = pendulum.getState();

        cout << pState.getMotorAngle() << endl;
    }

    return 0;
}
