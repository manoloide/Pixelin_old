#include "coloreditor.h"


ColorEditor::ColorEditor(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	global = Global::Instance();
	setBackgroundColor(color(50));

	colorSelect = &global->colorSelect;//color((rand() % 256), (rand() % 256), (rand() % 256));
	//printf("%i %i %i %i\n", red(colorSelect), getParent()->getWidth(), getMinWidth(), getMaxWidth());
	sred = new Slide(this, 80, 20, getWidth()-180, 10, 0, 255, red(*colorSelect));
	sgreen = new Slide(this, 80, 40, getWidth()-180, 10, 0, 255, green(*colorSelect));
	sblue = new Slide(this, 80, 60, getWidth()-180, 10, 0, 255, blue(*colorSelect));

}

void ColorEditor::update()
{
	int mx = events->mouseX-realLeft;
	int my = events->mouseY-realTop;

	sred->update(mx, my);
	sgreen->update(mx, my);
	sblue->update(mx, my);	

	*colorSelect = color(sred->val, sgreen->val, sblue->val);
}

void ColorEditor::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Rect viewColor = {20, 20, 50, 50};
	SDL_FillRect(getSurface(), &viewColor, *colorSelect);

	sred->draw(0, 0);
	sgreen->draw(0, 0);
	sblue->draw(0, 0);
}