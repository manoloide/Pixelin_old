#include "swatches.h"


Swatches::Swatches(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(color(40));
	sizeBox = 15;
	borderBox = 0;
	limitBorder = 5;
	for(int i = 0; i < 40; i++)
	{
		colors[i] = color(rand()%256, rand()%256,rand()%256);
	}
}

void Swatches::update()
{
	if(events->mouseClicked)
	{
		int tt = (sizeBox+borderBox);
		int cc = (getWidth()-limitBorder*2)/tt;
		int mx = events->mouseX-limitBorder-realLeft;
		int my = events->mouseY-limitBorder-realTop;

		int v = (mx/tt)+(my/tt)*(cc);
		if(v >= 0 && v < 40 && (mx/tt) < cc){
			global->colorSelect = colors[v];
		}
	}

}

void Swatches::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);


	SDL_Rect viewColor = {limitBorder-1, limitBorder-1, getWidth()-limitBorder*2+2, getHeight()-limitBorder*2+2};
	col = color(10);
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