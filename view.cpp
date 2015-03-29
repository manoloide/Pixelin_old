#include "view.h"

View::View(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	global = Global::Instance();

	setBackgroundColor(0x494E4A);
	canvas = new Graphics(40, 40);
	canvas->background(240);

	scale = 4; 
	posx = 10;//-canvas->w/2;
	posy = 10;//-canvas->h/2;
}

void View::update()
{
	if(events->mousePressed && events->mouseButton == SDL_BUTTON_MIDDLE)
	{
		posx += events->mouseX-events->amouseX;
		posy += events->mouseY-events->amouseY;
	}
	if(events->mousePressed)
	{
		int amx = events->amouseX-posx-realLeft;
		int amy = events->amouseY-posy-realTop;
		int mx = events->mouseX-posx-realLeft;
		int my = events->mouseY-posy-realTop;
		if(events->mouseButton == SDL_BUTTON_LEFT)
		{
			if(events->Ctrl && mx >= 0 && mx/scale < canvas->w && my >= 0 && my/scale < canvas->h)
			{
				global->colorSelect = canvas->getPixel(mx/scale, my/scale);
			}
			else
			{
				canvas->strokeColor = global->colorSelect;
				canvas->line(amx/scale, amy/scale, mx/scale, my/scale);
			}
		}
		/*
		if(events->mouseButton == SDL_BUTTON_RIGHT)
		{
			canvas->stroke(250);
			canvas->line(amx/scale, amy/scale, mx/scale, my/scale);
		}
		*/
	}

	if(events->mouseWheel != 0)
	{	
		int ascale = scale;
		scale += events->mouseWheel;
		if(scale < 1) scale = 1;
	}
}

void View::redraw()
{

	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Surface* aux = SDL_CreateRGBSurface(0, canvas->w*scale, canvas->h*scale, 32, 0, 0, 0, 0);

	SDL_Rect location = {0, 0, canvas->w*scale, canvas->h*scale}; 
	SDL_BlitScaled(canvas->get(), NULL, aux, &location); 
	location = {posx, posy, canvas->w*scale, canvas->h*scale}; 
	SDL_BlitSurface(aux, NULL, getSurface(), &location);

	SDL_FreeSurface(aux);
}