#include "canvas.h"

Canvas::Canvas() : Layout()
{

}

Canvas::Canvas(Layout* _parent) : Layout(_parent)
{
	if(getParent() == NULL){
		printf("%s\n", "no parent");
	}
}

void Canvas::redraw()
{
	Uint32 col = getBackgroundColor();
	if(getFocus()){
		col = 0xFFFFFF00;
	}

	printf("%s\n", "ANDA");
	SDL_FillRect(getSurface(), NULL, col);
}