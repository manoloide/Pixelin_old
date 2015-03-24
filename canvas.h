#ifndef CANVAS_H
#define CANVAS_H

#include "SDL2/SDL.h"
#include "layout.h"
#include <vector>

class Canvas : public Layout
{
public:
	Canvas();
	Canvas(Layout* _parent);
	~Canvas();

	void redraw();

};

#endif