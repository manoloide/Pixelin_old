#ifndef VIEW_H
#define VIEW_H

#include "SDL2/SDL.h"

#include "events.h"
#include "global.h"
#include "graphics.h"
#include "layout.h"
#include "utilities.h"
#include "widget.h"

#include <vector>


class View : public Widget
{
public:
	View(Layout* _parent);
	~View();

	void update();
	void redraw();

	Graphics* getCanvas() const { return canvas;};

private:
	int scale;
	int posx, posy;
	Graphics* canvas;
};

#endif