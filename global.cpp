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
	tool = 0;
	Uint32 colorSelect = color(0);

	bucketContinguous = true;
	bucketTolerance = 0;

	gradientType = 0;
	gradientAlpha = 255;
}