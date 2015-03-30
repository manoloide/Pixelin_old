#ifndef SWATCHES_H
#define SWATCHES_H

#include "SDL2/SDL.h"

#include "gui.h"
#include "layout.h"
#include "utilities.h"
#include "widget.h"


class Swatches : public Widget
{
public:
	Swatches(Layout* _parent);
	~Swatches();

	void update();
	void redraw();

private:
	int sizeBox, borderBox, limitBorder;
	Uint32 colors[40];
};

#endif