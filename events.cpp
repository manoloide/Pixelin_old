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
	mouseButton = 0;
	mousePressed = false;
	amouseX = amouseY = 0;
	mouseX =  mouseY = 0;
}