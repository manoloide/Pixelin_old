#ifndef GUI_H
#define GUI_H

#include "SDL2/SDL.h"
#include "events.h"
#include "layout.h"
#include "utilities.h"

class GuiElement{
public:
	GuiElement();

	bool on, press, moved;
	Events* events;
	int x, y, w, h;	
	Layout* layout;
};

class Slide : public GuiElement{
public:
	Slide(Layout* _layout, int _x, int _y, int _w, int _h, int _min, int _max, int _val);
	void update(int mx, int my);
	void draw(int mx, int my);

	//int getValue() const {return val;};

	int min, max, val, pos;
};

#endif