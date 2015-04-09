#include "layer.h"


Layer::Layer(int _w, int _h)
{
	w = _w; 
	h = _h;

	graphic = new Graphics(w, h);
}

Layer::~Layer()
{
	delete graphic;
}

void Layer::resize(int _w, int _h)
{
	graphic->resize(_w, _h);
}

void Layer::setName(char* _name)
{
	name = _name;
}

void Layer::setAlpha(int _alpha)
{
	alpha = _alpha;
}
