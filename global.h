#ifndef GLOBAL_H
#define GLOBAL_H

#include "SDL2/SDL.h"
#include "utilities.h"

class Global
{
public:
	static Global* Instance();

	bool allRender;
	int tool;
	Uint32 colorSelect;

	int gradientType;
	int gradientAlpha;

protected:
	Global();
	Global(const Global & ) ;
	Global &operator= (const Global & ) ;
private:
	static Global* instance;
};

#endif