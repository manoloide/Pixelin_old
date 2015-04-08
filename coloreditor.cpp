#include "coloreditor.h"


ColorEditor::ColorEditor(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(color(50));

	//color((rand() % 256), (rand() % 256), (rand() % 256));
	//printf("%i %i %i %i\n", red(colorSelect), getParent()->getWidth(), getMinWidth(), getMaxWidth());
	colorSelect = global->colorSelect;

	addElement(sred = new Slide(this, 80, 20, getWidth()-180, 10, 0, 255, red(colorSelect)));
	addElement(sgreen = new Slide(this, 80, 40, getWidth()-180, 10, 0, 255, green(colorSelect)));
	addElement(sblue = new Slide(this, 80, 60, getWidth()-180, 10, 0, 255, blue(colorSelect)));

	addElement(selector = new Selector(this, 220, 20, 50, 10, 5, 0));
	addElement(black = new Button(this, 220, 60, 10, 10, false));

}

void ColorEditor::update()
{
	colorSelect = global->colorSelect;

	sred->setVal(red(colorSelect));
	sgreen->setVal(green(colorSelect));
	sblue->setVal(blue(colorSelect));

	int mx = events->mouseX-realLeft;
	int my = events->mouseY-realTop;

	for(int i = 0; i < elements.size(); i++)
	{
		GuiElement* element = elements[i];
		element->update(mx, my);	
	}

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

	for(int i = 0; i < elements.size(); i++)
	{
		GuiElement* element = elements[i];
		element->draw(0, 0);	
	}
}