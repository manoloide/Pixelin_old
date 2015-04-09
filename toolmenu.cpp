#include "toolmenu.h"

ToolMenu::ToolMenu(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(color(120));

	addElement(bucketContinguous = new Toggle(this, 10, 5, 18, 18, global->bucketContinguous));
	addElement(bucketTolerance = new Slide(this, 100, 5, 100, 18, 0, 255, global->bucketTolerance));

	addElement(gradientType = new Selector(this, 10, 5, 54, 18, 3, global->gradientType));
	addElement(gradientAlpha = new Slide(this, 100, 5, 100, 18, 0, 255, global->gradientAlpha));
}

ToolMenu::~ToolMenu()
{

}

void ToolMenu::update()
{
	int mx = events->mouseX-realLeft;
	int my = events->mouseY-realTop;

	switch(global->tool)
	{
		case PENCIL: 

			break;
		case BUCKET:
			bucketContinguous->update(mx, my);
			global->bucketContinguous = bucketContinguous->val;
			bucketTolerance->update(mx, my);
			global->bucketTolerance = bucketTolerance->val;
			break;
		case GRADIENT:
			gradientType->update(mx, my);
			global->gradientType = gradientType->val;
			gradientAlpha->update(mx, my);
			global->gradientAlpha = gradientAlpha->val;
			break;
		case ERASER:

			break;
	}
}

void ToolMenu::redraw()
{
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	switch(global->tool)
	{
		case PENCIL: 

			break;
		case BUCKET:
			bucketContinguous->draw(0, 0);
			bucketTolerance->draw(0, 0);
			break;
		case GRADIENT:
			gradientType->draw(0, 0);
			gradientAlpha->draw(0, 0);
			break;
		case 3:

			break;
	}
}