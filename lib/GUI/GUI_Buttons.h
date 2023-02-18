#ifndef _GUI_BUTTONS_H
#define _GUI_BUTTONS_H

class GUI_Button : public GUI_Object{
public:
    GUI_Button(int ID, int x, int y, int w, int h, const unsigned char* icon, String text );
    
    unsigned char* icon;
    String text;
};

#endif 