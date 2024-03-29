#ifndef GUI_H
#define GUI_H

#include "SDL2/SDL.h"
#include "events.h"
#include "layout.h"
#include "utilities.h"

#define PENCIL 0
#define BUCKET 1
#define GRADIENT 2
#define ERASER 3


class GuiElement{
public:
	GuiElement();

	virtual void update(int mx, int my);
	virtual void draw(int mx, int my);

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
	void setVal(int v);

	int min, max, val, pos;
};

class Button : public GuiElement{
public:
	Button(Layout* _layout, int _x, int _y, int _w, int _h, bool _val);
	void update(int mx, int my);
	void draw(int mx, int my);

	//int getValue() const {return val;};
	void setVal(bool v);

	bool val, click, press;
};

class Selector : public GuiElement{
public:
	Selector(Layout* _layout, int _x, int _y, int _w, int _h, int _count, int _val);
	void update(int mx, int my);
	void draw(int mx, int my);

	//int getValue() const {return val;};
	void setVal(int v);

	bool click, press;
	int count, val;
};

class Toggle : public GuiElement{
public:
	Toggle(Layout* _layout, int _x, int _y, int _w, int _h, bool _val);
	void update(int mx, int my);
	void draw(int mx, int my);

	//int getValue() const {return val;};
	void setVal(bool v);

	bool val, click, press;
};

#endif