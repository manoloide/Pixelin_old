#include "events.h"

Events* Events::instance = 0;
Events* Events::Instance ()
{
  if (instance == 0)
  {
    instance = new Events;
  }
  return instance;
}
Events::Events()
{
	Ctrl = Alt = Shift = false;

	mouseButton = 0;
	mouseWheel = 0;
	mousePressed = false;
	amouseX = amouseY = 0;
	mouseX =  mouseY = 0;
}

void Events::update()
{
	mouseClicked = false;
	mouseDragged = false;
	mouseReleased = false;
	mouseWheel = 0;

	
}