#include "swatches.h"


Swatches::Swatches(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(color(40));
	sizeBox = 15;
	borderBox = 1;
	limitBorder = 4;
	for(int i = 0; i < 40; i++)
	{
		colors[i] = color(rand()%256, rand()%256,rand()%256);
	}
}

void Swatches::update()
{
	if(events->mouseClicked)
	{
		int cc = (sizeBox+borderBox);

		int mx = events->mouseX-limitBorder-realLeft;
		int my = events->mouseY-limitBorder-realTop;

		int v = (mx/cc)+(my/cc)*(cc+1);
		global->colorSelect = colors[v];
		printf("%i %i\n", cc, v);
	}

}

void Swatches::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);


	SDL_Rect viewColor = {3, 3, getWidth()-6, getHeight()-6};
	col = color(4);
	SDL_FillRect(getSurface(), &viewColor, col);


	int cc = (getWidth()-limitBorder*2)/(sizeBox+borderBox);
	for(int i = 0; i < 40; i++)
	{
		int xx = limitBorder+(sizeBox+borderBox)*(i%cc);
		int yy = limitBorder+(sizeBox+borderBox)*(i/cc);
		SDL_Rect aux = {xx, yy, sizeBox, sizeBox};
		col = colors[i];
		SDL_FillRect(getSurface(), &aux, col);
	}

}