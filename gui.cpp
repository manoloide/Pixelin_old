#include "gui.h"

GuiElement::GuiElement()
{
	events = Events::Instance();
	on = press = moved = false;
}

Slide::Slide(Layout* _layout, int _x, int _y, int _w, int _h, int _min, int _max, int _val)
{
	
	layout = _layout;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	min = _min;
	max = _max;
	val = _val;

	pos = map(val, min, max, 0, w-h);
}


void Slide::update(int mx, int my)
{
	if(mx >= x && mx < x+w && my >= y && my < y+h)
	{
		on = true;
	}
	else
	{
		on = false;
	}

	if(on && events->mouseClicked)
	{
		moved = true;
	}

	if(!events->mousePressed)
	{
		moved = false;
	}

	if(moved)
	{
		pos = constrain(map(mx-h/2, x, x+w, 0, w), 0, w-h);
		val = constrain(map(mx, x, x+w, min, max), min, max);
		//printf("%i\n", val);
	}
}

void Slide::draw(int mx, int my)
{
	Uint32 col = color(100);
	SDL_Rect background = {x, y, w, h};
	SDL_FillRect(layout->getSurface(), &background, col);
	col = color(140);
	if(moved)
	{
		col = color(160);
	}
	background = {x+pos, y, h, h};
	SDL_FillRect(layout->getSurface(), &background, col);
}