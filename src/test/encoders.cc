#include "../utils/encoders.hh"
#include "../utils/pins.hh"

#include <iostream>
#include <wiringPi.h>

using namespace std;

auto main () -> int {
    wiringPiSetup();
    Encoder *const M_MOTOR_ENCODER =
		new Encoder(MOTOR_ENCODER_WIRE_A, MOTOR_ENCODER_WIRE_B);

    while (true) {
        cout << M_MOTOR_ENCODER->getAngle() << endl;
    }

    delete M_MOTOR_ENCODER;

    return 0;
}
