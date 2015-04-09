#ifndef TOOLMENU_H
#define TOOLMENU_H

#include "SDL2/SDL.h"

#include "gui.h"
#include "layout.h"
#include "utilities.h"
#include "widget.h"

class ToolMenu : public Widget
{
public:
	ToolMenu(Layout* _parent);
	~ToolMenu();

	void update();
	void redraw();

protected:
	Toggle* bucketContinguous;
	Slide* bucketTolerance;

	Selector* gradientType;
	Slide* gradientAlpha;
};

#endif