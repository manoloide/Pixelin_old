#include "global.h"

Global* Global::instance = 0;
Global* Global::Instance ()
{
  if (instance == 0)
  {
    instance = new Global;
  }
  return instance;
}
Global::Global()
{
	allRender = false;
	Uint32 colorSelect = color(0);
}