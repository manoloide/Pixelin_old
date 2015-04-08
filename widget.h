#ifndef WIDGET_H
#define WIDGET_H

#include "SDL2/SDL.h"

#include "layout.h"
#include "events.h"
#include "global.h"
#include "gui.h"

class Widget : public Layout
{
public:
	Widget(Layout* _parent);
	~Widget();

	virtual void update();
	virtual void redraw();

	void addElement(GuiElement* ng);

protected:
	Events* events;
	Global* global;

	std::vector<GuiElement*> elements;
};

#endif