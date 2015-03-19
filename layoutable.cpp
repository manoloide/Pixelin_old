#include "layoutable.h"

Layoutable::Layoutable()
{

}

Layoutable::~Layoutable()
{

}

void Layoutable::resize()
{

}
void Layoutable::show()
{

}
void Layoutable::redraw()
{

}

/*
SDL_Surface* Layoutable::getSurface()
{
	return surface;
}*/

void Layoutable::setMinWidth(int _minWidth)
{
	minWidth = _minWidth;
}

void Layoutable::setMaxWidth(int _maxWidth)
{
	maxWidth = _maxWidth;
}

void Layoutable::setMinHeight(int _minHeight)
{
	minHeight = _minHeight;
}

void Layoutable::setMaxHeight(int _maxHeight)
{
	maxHeight = _maxHeight;
}

void Layoutable::setWidth(int _w)
{
	w = _w;
}

void Layoutable::setHeight(int _h)
{
	h = _h;
}

void Layoutable::setLeft(int _left)
{
	left = _left;
}

void Layoutable::setTop(int _top)
{
	top = _top;
}
/*
void Layoutable::setParent(Layoutable* _parent)
{
	parent = _parent;
}
*/

void Layoutable::setBackgroundColor(Uint32 _backgroundColor)
{
	backgroundColor = _backgroundColor;
}