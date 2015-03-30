#include "tools.h"


Tools::Tools(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(color(70));
	sizeBox = 32;
	borderBox = 5;
	limitBorder = 5;
	tool = 1;
}

void Tools::update()
{
	tool = global->tool;
	if(events->mouseClicked)
	{
		int tt = (sizeBox+borderBox);
		int cc = (getWidth()-limitBorder)/tt;
		int mx = events->mouseX-limitBorder-realLeft;
		int my = events->mouseY-limitBorder-realTop;

		int v = (mx/tt)+(my/tt)*(cc);
		if(v >= 0 && v < 7 && (mx/tt) < cc){
			tool = v;
		}
		global->tool = tool;
	}

}

void Tools::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	int cc = (getWidth()-limitBorder)/(sizeBox+borderBox);
	for(int i = 0; i < 7; i++)
	{
		int xx = limitBorder+(sizeBox+borderBox)*(i%cc);
		int yy = limitBorder+(sizeBox+borderBox)*(i/cc);
		SDL_Rect aux = {xx, yy, sizeBox, sizeBox};
		col = color(120);
		if(i == tool)
		{
			col = color(160);
		}
		SDL_FillRect(getSurface(), &aux, col);
	}

}