#include "layout.h"

Layout::Layout()
{
	setParent(NULL);
	init();
}

Layout::Layout(Layout* _parent)
{
	setParent(_parent);
	init();
}


Layout::~Layout()
{
	SDL_FreeSurface(surface);
}

void Layout::init()
{
	surface = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
	setBackgroundColor(SDL_MapRGB(surface->format, (rand() % 256), (rand() % 256), (rand() % 256)));

	setLeft(0);
	setTop(0);
	setWidth(640);
	setHeight(480);
	setStyle(Horizontal);

	setMinWidth(0);
	setMaxWidth(0);
	setMinHeight(0);
	setMaxHeight(0);

	if (parent != NULL)
	{	
		parent->addChild(this);
	}
	
	resize();
}

void Layout::resize()
{
	
	surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	redraw();
	int c = children.size();
	if(c > 0)
	{	
		if(style == Horizontal)
		{
			/*
			int nw = w/c;
			for(int i = 0; i < c; i++)
			{
				Layout* l = children.at(i);
				l->setHeight(h);
				l->setTop(0);

				l->setWidth(nw);
				l->setLeft(nw*i);	
				l->resize();	
			}
			*/
			int newWidth = w/c;
			int total = 0;
			int rest = w;
			for (int i = 0; i < c; i++) {
				Layout* l = children.at(i);
				l->setHeight(h);
				l->setTop(0);

				if (l->getMaxWidth() != 0 && newWidth > l->getMaxWidth()) {
					l->setWidth(l->getMaxWidth());
				} else if (l->getMinWidth() != 0 && newWidth < l->getMinWidth()) {
					l->setWidth(l->getMinWidth());
				} else {
					total++;
					l->setWidth(0);
				}
				rest -= l->getWidth();
			}
			if (total > 0) {
				newWidth = rest/total;
				int ap = 0;
				for (int i = 0; i < c; i++) {
					Layout* l = children.at(i);
					l->setLeft(ap);
					if (l->getWidth() == 0) {
						l->setWidth(newWidth);
					}
					ap += l->getWidth();
				}
			}
		}
		if(style == Vertical)
		{
			/*
			int nh = h/c;
			for(int i = 0; i < c; i++)
			{
				Layout* l = children.at(i);
				l->setHeight(nh);
				l->setTop(nh*i);

				l->setWidth(w);
				l->setLeft(0);	
				l->resize();
			}
			*/
			int newHeight = h/c;
			int total = 0;
			int rest = h;
			for (int i = 0; i < c; i++) {
				Layout* l = children.at(i);
				l->setWidth(w);
				l->setLeft(0);

				if (l->getMaxHeight() != 0 && newHeight > l->getMaxHeight()) {
					l->setHeight(l->getMaxHeight());
				} else if (l->getMinHeight() != 0 && newHeight < l->getMinHeight()) {
					l->setHeight(l->getMinHeight());
				} else {
					total++;
					l->setHeight(0);
				}
				rest -= l->getHeight();
			}
			if (total > 0) {
				newHeight = rest/total;
				int ap = 0;
				for (int i = 0; i < c; i++) {
					Layout* l = children.at(i);
					l->setTop(ap);
					if (l->getHeight() == 0) {
						l->setHeight(newHeight);
					}
					ap += l->getHeight();
				}
			}
		}
		for (int i = 0; i < c; i++) {
			Layout* l = children.at(i);
			l->resize();
		}
	}

	update();
}

void Layout::resize(int _w, int _h)
{
	setLeft(0);
	setTop(0);
	setWidth(_w);
	setHeight(_h);

	resize();
}

void Layout::updateFocus()
{
	int mouseX = -1;
	int mouseY = -1;
	SDL_GetMouseState( &mouseX, &mouseY );
	int ml = 0;
	int mt = 0;

	Layout* pp = getParent();
	while(pp != NULL)
	{
		ml += pp->getLeft();
		mt += pp->getTop();
		pp = pp->getParent();
	}

	mouseX -= ml;
	mouseY -= mt;

	if(mouseX >= left && mouseX < left+w && mouseY >= top && mouseY < top+h)
	{
		if(!focused) focused = true;
	}
	else
	{
		if(focused)
		{
			focused = false;
			redraw();
		}
	}


}

void Layout::show()
{
	updateFocus();
	if(focused){
		update();
		redraw();
	} 

	for(int i = 0; i < children.size(); i++)
	{
		Layout* l = children.at(i);
		l->show();
	}

	if(parent != NULL)
	{
		SDL_Rect rect;
		rect.x = left;
		rect.y = top;
		rect.w = w;
		rect.h = h;

		SDL_BlitSurface(surface, NULL, parent->getSurface(), &rect);
	}

}

void Layout::update()
{

}
void Layout::redraw()
{
	Uint32 col = backgroundColor;
	if(focused){
		col = 0xFFFF0000;
	}

	SDL_FillRect(surface, NULL, col);
}

void Layout::addChild(Layout* child){
	children.push_back(child);
	child->setParent(this);
	resize();
}

void Layout::setMinWidth(int _minWidth)
{
	minWidth = _minWidth;
}

void Layout::setMaxWidth(int _maxWidth)
{
	maxWidth = _maxWidth;
}

void Layout::setMinHeight(int _minHeight)
{
	minHeight = _minHeight;
}

void Layout::setMaxHeight(int _maxHeight)
{
	maxHeight = _maxHeight;
}

void Layout::setWidth(int _w)
{
	w = _w;
}

void Layout::setHeight(int _h)
{
	h = _h;
}

void Layout::setLeft(int _left)
{
	left = _left;
}

void Layout::setTop(int _top)
{
	top = _top;
}

void Layout::setBackgroundColor(Uint32 _backgroundColor)
{
	backgroundColor = _backgroundColor;
}

void Layout::setStyle(Style _style)
{
	style = _style;
}

void Layout::setParent(Layout* _parent){
	parent = _parent;
}