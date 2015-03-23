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
	void updateFocus();

	void addChild(Layout* child);

	Layout* getParent() const { return parent;}

	void setStyle(Style _style);
	void setParent(Layout* _parent);

private:
	void init();

	bool focused;
	Layout *parent;
	Style style;
	std::vector<Layout *> children;
};

#endif