#ifndef VIEW_H
#define VIEW_H

#include "SDL2/SDL.h"
#include <vector>

#include "events.h"
#include "graphics.h"
#include "layout.h"


class View : public Layout
{
public:
	View(Layout* _parent);
	~View();

	void update();
	void redraw();

private:
	int posx, posy;
	Graphics* canvas;
	Events* events;
};

#endif