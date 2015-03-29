#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include "SDL2/SDL.h"

#include "events.h"
#include "layout.h"
#include "global.h"
#include "gui.h"
#include "graphics.h"
#include "utilities.h"

class ColorEditor : public Layout
{
public:
	ColorEditor(Layout* _parent);
	~ColorEditor();

	void update();
	void redraw();

private:
	Events* events;
	Global* global;

	Uint32 colorSelect;
	Slide *sred, *sgreen, *sblue;
};

#endif