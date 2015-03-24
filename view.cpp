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
	if(events->mousePressed && events->mouseButton == SDL_BUTTON_MIDDLE)
	{
		posx += events->mouseX-events->amouseX;
		posy += events->mouseY-events->amouseY;
	}
	if(events->mousePressed && events->mouseButton == SDL_BUTTON_LEFT)
	{
		int amx = events->amouseX-posx;
		int amy = events->amouseY-posy;
		int mx = events->mouseX-posx;
		int my = events->mouseY-posy;
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