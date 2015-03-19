#ifndef LAYOUT_H
#define LAYOUT_H

#include "SDL2/SDL.h"
#include "layoutable.h"
#include <vector>

class Layout : public Layoutable
{
public:
	enum Style { Vertical, Horizontal };
	Layout();
	Layout(Layout* _parent);
	~Layout();

	void resize();
	void resize(int w, int h);
	void show();
	void redraw();

	void addChild(Layout* child);

	void setStyle(Style _style);
	void setParent(Layout* _parent);

private:
	void init();

	Layout *parent;
	Style style;
	std::vector<Layout *> children;
};

#endif