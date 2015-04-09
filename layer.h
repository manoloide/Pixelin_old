#ifndef LAYER_H
#define LAYER_H

#include "SDL2/SDL.h"

#include "graphics.h"

class Layer{
public:
	Layer(int _w, int _h);
	~Layer();

	void resize(int _w, int _h);

	Graphics* getGraphics() const { return graphic;}
	char* getName() const { return name;}
	int getAlpha() const { return alpha;}

	void setName(char* _name);
	void setAlpha(int _alpha);

protected:
	char* name;
	int w, h;
	int alpha;
	Graphics* graphic;
};

#endif