#ifndef LAYOUT_H
#define LAYOUT_H

#include "SDL2/SDL.h"
#include <vector>

class Layout
{
public:
	enum Style { Vertical, Horizontal };
	Layout();
	Layout(Layout* _parent);
	~Layout();

	void resize();
	void resize(int w, int h);
	void show();
	virtual void redraw();
	void updateFocus();

	void addChild(Layout* child);

	int getWidth() const { return w;}
	int getHeight() const { return h;}
	int getLeft() const { return left;}
	int getTop() const { return top;}

	int getMinWidth() const { return minWidth;}
	int getMaxWidth() const { return maxWidth;}
	int getMinHeight() const { return minHeight;}
	int getMaxHeight() const { return maxHeight;}

	bool getFocus() const { return focused;}
	Uint32 getBackgroundColor() const { return backgroundColor;}
	SDL_Surface* getSurface() const { return surface;}
	Layout* getParent() const { return parent;}

	void setWidth(int _w);
	void setHeight(int _h);
	void setLeft(int _left);
	void setTop(int _top);

	void setMinWidth(int _minWidth);
	void setMaxWidth(int _maxWidth);
	void setMinHeight(int _minHeight);
	void setMaxHeight(int _maxHeight);

	void setBackgroundColor(Uint32 _backgroundColor);
	void setStyle(Style _style);
	void setParent(Layout* _parent);

private:
	void init();

	bool focused;
	int w, h;
	int left, top;
	int minWidth, maxWidth;
	int minHeight, maxHeight;
	
	Uint32 backgroundColor;
	SDL_Surface *surface;

	Layout *parent;
	Style style;
	std::vector<Layout *> children;
};

#endif