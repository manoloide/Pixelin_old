#include "graphics.h"

Graphics::Graphics(int _w, int _h)
{
	w = _w;
	h = _h;
	surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
}

Graphics::~Graphics()
{
	SDL_FreeSurface(surface);
}

SDL_Surface* Graphics::get()
{
	return surface;
}

void Graphics::setPixel(int x, int y, Uint32 color)
{

	if( x < 0 || x >= w || y < 0 || y >= h)
	{
		return;
	}

	Uint8 *  bufp= (Uint8 *)surface->pixels + y*surface->pitch + x*surface->format->BytesPerPixel;
	switch (surface->format->BytesPerPixel) {
		case 4:
		bufp[3] = color >> 24;
		case 3:
		bufp[2] = color >> 16;
		case 2:
		bufp[1] = color >> 8;
		case 1:
		bufp[0] = color;
	}
	return;
}

void Graphics::line(int x0, int y0, int x1, int y1)
{
	float ww = x1-x0;
	float hh = y1-y0;
	float len = sqrt((w*w)+(h*h));
	if(len < 1)
	{
		setPixel(x0, y0, strokeColor);
	}
	else
	{
		float dx = ww/len;
		float dy = hh/len;
		for(int i = 0; i < len; i++)
		{
			int xx = floor(x0+dx*i); 
			int yy = floor(y0+dy*i);
			setPixel(xx, yy, strokeColor);
		}
	}
}

void Graphics::background(Uint8 g)
{
	SDL_FillRect(surface, NULL, color(g));
}

void Graphics::image(SDL_Surface *img, int x, int y, int w, int h)
{
	SDL_Rect ao;
    ao.x = 0;//screen->w/2-image->w/2;
    ao.y = 0;//screen->h/2-image->h/2;
    ao.w = img->w;
    ao.h = img->h;

    SDL_Rect ar;
    ar.x = x;//screen->w/2-image->w/2;
    ar.y = y;//screen->h/2-image->h/2;
    ar.w = img->w*2;
    ar.h = img->h*2;
    SDL_BlitSurface( img, &ao, surface, &ar );
}

void Graphics::image(SDL_Surface *img, int x, int y)
{
	SDL_Rect rect;
    rect.x = x;//screen->w/2-image->w/2;
    rect.y = y;//screen->h/2-image->h/2;
    rect.w = img->w*2;
    rect.h = img->h*2;
    SDL_BlitSurface( img, NULL, surface, &rect );
}


void Graphics::fill(Uint8 r, Uint8 g, Uint8 b)
{
	fillColor = color(r, g, b);
}
void Graphics::fill(Uint8 g){
	fill(g, g, g);
}

void Graphics::stroke(Uint8 r, Uint8 g, Uint8 b)
{
	strokeColor = color(r, g, b);
}

void Graphics::stroke(Uint8 g)
{
	stroke(g, g, g);
}

Uint32 Graphics::color(Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(surface->format, r, g, b);
}

Uint32 Graphics::color(Uint8 g)
{
	return color(g, g, g);
}
