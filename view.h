#ifndef VIEW_H
#define VIEW_H

#include "SDL2/SDL.h"
#include "layout.h"
#include <vector>

class View : public Layout
{
public:
	View();
	View(Layout* _parent);
	~View();

	void redraw();

};

#endif