#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick( int U, int D, int L, int R ){
    UP = U;
    DOWN = D;
    LEFT = L;
    RIGHT = R;

    pinMode(U, INPUT_PULLUP);
    pinMode(D, INPUT_PULLUP);
    pinMode(L, INPUT_PULLUP);
    pinMode(R, INPUT_PULLUP);
}


bool* Joystick::get_inputs()
{
    inputs[0]=!digitalRead(UP);
    inputs[1]=!digitalRead(DOWN);
    inputs[2]=!digitalRead(LEFT);
    inputs[3]=!digitalRead(RIGHT);

    return inputs;
}