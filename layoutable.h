#ifndef LAYOUTABLE_H
#define LAYOUTABLE_H

#include "SDL2/SDL.h"

class Layoutable
{
public:
	Layoutable();
	~Layoutable();

	void resize();
	void show();
	void redraw();

	int getWidth() const { return w;}
	int getHeight() const { return h;}
	int getLeft() const { return left;}
	int getTop() const { return top;}

	int getMinWidth() const { return minWidth;}
	int getMaxWidth() const { return maxWidth;}
	int getMinHeight() const { return minHeight;}
	int getMaxHeight() const { return maxHeight;}

	SDL_Surface* getSurface() const { return surface;}

	void setWidth(int _w);
	void setHeight(int _h);
	void setLeft(int _left);
	void setTop(int _top);

	void setMinWidth(int _minWidth);
	void setMaxWidth(int _maxWidth);
	void setMinHeight(int _minHeight);
	void setMaxHeight(int _maxHeight);

	void setBackgroundColor(Uint32 _backgroundColor);

protected:
	int w, h;
	int left, top;
	int minWidth, maxWidth;
	int minHeight, maxHeight;
	
	Uint32 backgroundColor;

	SDL_Surface *surface;
};

#endif