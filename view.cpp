#include "view.h"

View::View(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	setBackgroundColor(0x494E4A);
	canvas = new Graphics(20, 20);
	canvas->background(240);

	scale = 10; 
	posx = 200;//-canvas->w/2;
	posy = 200;//-canvas->h/2;
}

void View::update()
{
	if(events->mousePressed && events->mouseButton == SDL_BUTTON_MIDDLE)
	{
		posx += events->mouseX-events->amouseX;
		posy += events->mouseY-events->amouseY;
	}
	if(events->mousePressed && events->mouseButton == SDL_BUTTON_LEFT)
	{
		int amx = events->amouseX-posx-realLeft;
		int amy = events->amouseY-posy-realTop;
		int mx = events->mouseX-posx-realLeft;
		int my = events->mouseY-posy-realTop;
		canvas->line(amx/scale, amy/scale, mx/scale, my/scale);
	}
		
	scale += events->mouseWheel;
	if(scale < 1) scale = 1;
}

void View::redraw()
{

	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Rect ori = {0,0,canvas->w,canvas->h}; 
	SDL_Rect location = {posx,posy,canvas->w*scale,canvas->h*scale}; 
	SDL_BlitScaled(canvas->get(), &ori, getSurface(), &location);
}