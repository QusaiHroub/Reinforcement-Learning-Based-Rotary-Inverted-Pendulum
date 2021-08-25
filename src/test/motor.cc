#include "../utils/motor.hh"
#include "../utils/pins.hh"

#include <iostream>
#include <wiringPi.h>

using namespace std;

auto main () -> int {
    wiringPiSetup();
    Motor *const M_MOTOR = new Motor(MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_ENABLE_DC_1);

    while (true) {
        M_MOTOR->act(60);
    }

    delete M_MOTOR;

    return 0;
}
