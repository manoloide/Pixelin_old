#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include "SDL2/SDL.h"

#include "events.h"
#include "graphics.h"
#include "layout.h"


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
};

#endif