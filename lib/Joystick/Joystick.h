#ifndef _JOYSTICK_H
#define _JOYSTICK_H



class Joystick {
private:
    int UP;
    int DOWN;
    int LEFT;
    int RIGHT;
    bool inputs[4];
    float direction[2];
public:
    void update_inputs();
    bool* wait_inputs(); 
    bool* get_inputs();
    bool wait_for_input( int in );
    float* get_direction( bool* in );
    Joystick( int U, int D, int L, int R );


};

#endif 