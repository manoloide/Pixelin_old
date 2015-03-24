#include "view.h"

View::View(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	setBackgroundColor(0x494E4A);
	canvas = new Graphics(200, 200);
	canvas->background(240);

	posx = 20;//-canvas->w/2;
	posy = 20;//-canvas->h/2;
}

void View::update()
{
	printf("%i %i\n", realLeft, realTop);
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
		canvas->line(amx, amy, mx, my);
	}
}

void View::redraw()
{

	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Rect location = {posx,posy,canvas->w,canvas->h}; 
	SDL_BlitSurface(canvas->get(), NULL, getSurface(), &location);

	/*
	if(mousePressed)
	{   
        //printf("%i %i %i %i\n", amouseX, amouseY, mouseX, mouseY);
		canvas->stroke(5);
		canvas->line(amouseX, amouseY, mouseX, mouseY);
	}*/
	}