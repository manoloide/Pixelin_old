#include "coloreditor.h"

ColorEditor::ColorEditor(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	setBackgroundColor(0x29352D);

	colorSelect = SDL_MapRGB(getSurface()->format, (rand() % 256), (rand() % 256), (rand() % 256));
}

void ColorEditor::update()
{
	if(events->mouseClicked)
	{
		colorSelect = SDL_MapRGB(getSurface()->format, (rand() % 256), (rand() % 256), (rand() % 256));
	}
}

void ColorEditor::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Rect viewColor = {20, 20, 50, 50};
	SDL_FillRect(getSurface(), &viewColor, colorSelect);
}