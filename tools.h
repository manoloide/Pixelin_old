#ifndef TOOLS_H
#define TOOLS_H

#include "SDL2/SDL.h"

#include "gui.h"
#include "layout.h"
#include "utilities.h"
#include "widget.h"


class Tools : public Widget
{
public:
	Tools(Layout* _parent);
	~Tools();

	void update();
	void redraw();

private:
	int sizeBox, borderBox, limitBorder;
	int tool, toolsCount;
};

#endif