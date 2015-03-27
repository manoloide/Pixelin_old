#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include "SDL2/SDL.h"

#include "events.h"
#include "layout.h"
#include "gui.h"
#include "graphics.h"

class ColorEditor : public Layout
{
public:
	ColorEditor(Layout* _parent);
	~ColorEditor();

	void update();
	void redraw();

private:
	Events* events;
	Uint32 colorSelect;
	Slide *red, *green, *blue;
};

#endif