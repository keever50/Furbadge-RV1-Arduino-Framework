#ifndef _JOYSTICK_H
#define _JOYSTICK_H



class Joystick {
private:
    int UP;
    int DOWN;
    int LEFT;
    int RIGHT;
    bool inputs[4];
public:
    void update_inputs();
    void wait_input(); 
    bool* get_inputs();
    Joystick( int U, int D, int L, int R );

};

#endif 