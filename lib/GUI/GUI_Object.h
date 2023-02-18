#ifndef _GUI_OBJECT_H
#define _GUI_OBJECT_H

class GUI_Object
{
public:
    GUI_Object(int ID, int x, int y, int w, int h );
    void (*update_ptr)(void);
    int ID;
    int x; int y; int w; int h;

};

#endif 
