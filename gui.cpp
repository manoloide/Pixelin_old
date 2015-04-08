#include "gui.h"

GuiElement::GuiElement()
{
	events = Events::Instance();
	on = press = moved = false;
}

void GuiElement::update(int mx, int my)
{

}
void GuiElement::draw(int mx, int my)
{

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

void Slide::setVal(int v)
{
	val = constrain(v, min, max);
	pos = map(val, min, max, 0, w-h);
}

Button::Button(Layout* _layout, int _x, int _y, int _w, int _h, bool _val)
{
	layout = _layout;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	val = _val;

	click = press = false;
}

void Button::update(int mx, int my)
{
	click = false;
	press = false;
	val = false;
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
		click = true;
		press = true;
		val = !val;
	}
}

void Button::draw(int mx, int my)
{
	int cc = 100;
	if(val)
	{
		cc = 140;
	}
	if(on) cc += 10;
	Uint32 col = color(cc);
	SDL_Rect background = {x, y, w, h};
	SDL_FillRect(layout->getSurface(), &background, col);
}

void Button::setVal(bool v)
{
	val = v;
}

Selector::Selector(Layout* _layout, int _x, int _y, int _w, int _h, int _count, int _val)
{
	layout = _layout;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	count = _count;
	val = _val;

	click = press = false;
}

void Selector::update(int mx, int my)
{
	click = false;
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
		click = true;
		press = true;
		int ww = w/count;
		val = (mx-x)/ww;
	}
	if(events->mouseReleased)
	{
		press = false;
	}
}

void Selector::draw(int mx, int my)
{
	int ww = w/count;
	for(int i = 0; i < count; i++)
	{
		int cc = 100;
		if(i == val)
		{
			cc = 140;
		}
		if(on) cc += 10;
		Uint32 col = color(cc);
		SDL_Rect background = {x+ww*i, y, ww, h};
		SDL_FillRect(layout->getSurface(), &background, col);

	}
}

void Selector::setVal(int v)
{
	val = v;
}

Toggle::Toggle(Layout* _layout, int _x, int _y, int _w, int _h, bool _val)
{
	layout = _layout;
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	val = _val;

	click = press = false;
}

void Toggle::update(int mx, int my)
{
	click = false;
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
		click = true;
		press = true;
		val = !val;
	}
	if(events->mouseReleased)
	{
		press = false;
	}
}

void Toggle::draw(int mx, int my)
{
	int cc = 100;
	if(val)
	{
		cc = 140;
	}
	if(on) cc += 10;
	Uint32 col = color(cc);
	SDL_Rect background = {x, y, w, h};
	SDL_FillRect(layout->getSurface(), &background, col);
}

void Toggle::setVal(bool v)
{
	val = v;
}