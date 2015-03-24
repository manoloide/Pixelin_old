#include "view.h"

View::View() : Layout()
{

}

View::View(Layout* _parent) : Layout(_parent)
{

}

void View::redraw()
{
	Uint32 col = getBackgroundColor();
	if(getFocus()){
		col = 0xFFFFFF00;
	}

	SDL_FillRect(getSurface(), NULL, col);
}