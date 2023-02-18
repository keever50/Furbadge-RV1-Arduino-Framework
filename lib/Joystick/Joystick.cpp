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

bool* Joystick::wait_inputs()
{
    while(true){
        get_inputs();
        if(inputs[0] | inputs[1] | inputs[2] | inputs[3]){
            return inputs;
        }
        delay(50);
    }
    
    return inputs;
}

bool Joystick::wait_for_input( int in ){
    while(true){
        get_inputs();
        if(inputs[in]==true){
            return true;
        }
        delay(50);
    }
    return false;
}

float* Joystick::get_direction( bool* in ){
    
    //Convert input bool array to a byte. So we have an unique byte for each direction.
    char input_byte;
    for(int i=0;i<4;i++){
        input_byte |= in[i] << i; 
    }

    switch(input_byte){
        case 6:
            direction[0]=0;
            direction[1]=1;
            break;
        case 2:
            direction[0]=0.707;
            direction[1]=0.707;
            break;
        case 10:
            direction[0]=1;
            direction[1]=0;
            break;
        case 8:
            direction[0]=0.707;
            direction[1]=-0.707;
            break;
        case 9:
            direction[0]=0;
            direction[1]=-1;
            break;
        case 1:
            direction[0]=-0.707;
            direction[1]=-0.707;
            break;
        case 5:
            direction[0]=-1;
            direction[1]=0;
            break;
        case 4:
            direction[0]=-0.707;
            direction[1]=0.707;
            break;            

        default:
            direction[0]=0;
            direction[1]=0;
            break;
    }
    
    return direction;
}