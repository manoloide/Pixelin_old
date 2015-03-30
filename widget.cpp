#include "widget.h"


Widget::Widget(Layout* _parent) : Layout(_parent)
{
	events = Events::Instance();
	global = Global::Instance();

}

Widget::~Widget()
{

}

void Widget::update()
{

}
void Widget::redraw()
{
}