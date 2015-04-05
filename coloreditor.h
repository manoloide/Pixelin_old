#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include "SDL2/SDL.h"

#include "gui.h"
#include "layout.h"
#include "utilities.h"
#include "widget.h"


class ColorEditor : public Widget
{
public:
	ColorEditor(Layout* _parent);
	~ColorEditor();

	void update();
	void redraw();

private:

	Uint32 colorSelect;

	Button *black;
	Selector *selector;
	Slide *sred, *sgreen, *sblue;
};

#endif