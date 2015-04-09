#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utilities.h"

class Graphics 
{
public:
	Graphics(int _w, int _h);
	~Graphics();

	//void resize(int _w, int _h);

	SDL_Surface* get();

	void resize(int _w, int _h);

	void loadImage(char* src);
	void saveImage(char* src);
	
	Uint32 getPixel(int x, int y);
	void setPixel(int x, int y, Uint32 color, bool replace);
	void setPixel(int x, int y, Uint32 color);
	
	void line(int x0, int y0, int x1, int y1);
	//void rect();

	void background(Uint8 g);
	void background(Uint8 r, Uint8 g, Uint8 b);

	void image(SDL_Surface *img, int x, int y);
	void image(SDL_Surface *img, int x, int y, int w, int h);

	void fill(Uint8 g);
	void fill(Uint8 r, Uint8 g, Uint8 b);
	//void fill(int g, int a);
	//void fill(int r, int g, int b, int a);
	void stroke(Uint8 g);
	void stroke(Uint8 r, Uint8 g, Uint8 b);

	Uint32 fillColor, strokeColor;
	
	int w, h;
	SDL_Surface* surface;
protected:
};

#endif