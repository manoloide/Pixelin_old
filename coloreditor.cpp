#include "coloreditor.h"


ColorEditor::ColorEditor(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(color(50));

	//color((rand() % 256), (rand() % 256), (rand() % 256));
	//printf("%i %i %i %i\n", red(colorSelect), getParent()->getWidth(), getMinWidth(), getMaxWidth());
	colorSelect = global->colorSelect;

	sred = new Slide(this, 80, 20, getWidth()-180, 10, 0, 255, red(colorSelect));
	sgreen = new Slide(this, 80, 40, getWidth()-180, 10, 0, 255, green(colorSelect));
	sblue = new Slide(this, 80, 60, getWidth()-180, 10, 0, 255, blue(colorSelect));

	black = new Button(this, 220, 60, 10, 10, false);

}

void ColorEditor::update()
{
	colorSelect = global->colorSelect;

	sred->setVal(red(colorSelect));
	sgreen->setVal(green(colorSelect));
	sblue->setVal(blue(colorSelect));

	int mx = events->mouseX-realLeft;
	int my = events->mouseY-realTop;

	sred->update(mx, my);
	sgreen->update(mx, my);
	sblue->update(mx, my);	

	black->update(mx, my);
	if(black->click)
	{
		sred->setVal(0);
		sgreen->setVal(0);
		sblue->setVal(0);
	}

	colorSelect = color(sred->val, sgreen->val, sblue->val);
	global->colorSelect = colorSelect;
}

void ColorEditor::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Rect viewColor = {20, 20, 50, 50};
	SDL_FillRect(getSurface(), &viewColor, colorSelect);

	sred->draw(0, 0);
	sgreen->draw(0, 0);
	sblue->draw(0, 0);

	black->draw(0, 0);
}