#ifndef WDIGET_H
#define WIDGET_H

#include "SDL2/SDL.h"

#include "layout.h"
#include "events.h"
#include "global.h"

class Widget : public Layout
{
public:
	Widget(Layout* _parent);
	~Widget();

	virtual void update();
	virtual void redraw();

protected:
	Events* events;
	Global* global;

};

#endif