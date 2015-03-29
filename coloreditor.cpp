#include "coloreditor.h"


ColorEditor::ColorEditor(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	setBackgroundColor(0x29352D);

	red = new Slide(this, 80, 20, getWidth()-220, 10, 0, 255, 0);
	green = new Slide(this, 80, 40, getWidth()-220, 10, 0, 255, 0);
	blue = new Slide(this, 80, 60, getWidth()-220, 10, 0, 255, 0);

	colorSelect = SDL_MapRGB(getSurface()->format, (rand() % 256), (rand() % 256), (rand() % 256));
}

void ColorEditor::update()
{
	int mx = events->mouseX-realLeft;
	int my = events->mouseY-realTop;

	red->update(mx, my);
	green->update(mx, my);
	blue->update(mx, my);	

	colorSelect = color(red->val, green->val, blue->val);
}

void ColorEditor::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Rect viewColor = {20, 20, 50, 50};
	SDL_FillRect(getSurface(), &viewColor, colorSelect);

	red->draw(0, 0);
	green->draw(0, 0);
	blue->draw(0, 0);
}