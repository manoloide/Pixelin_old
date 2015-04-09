#include "graphics.h"

Graphics::Graphics(int _w, int _h)
{
	w = _w;
	h = _h;
	surface = SDL_CreateRGBSurface(0, w, h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	//loadImage("img.bmp");
}

Graphics::~Graphics()
{
	//saveImage("img.bmp");
	SDL_FreeSurface(surface);
}

SDL_Surface* Graphics::get()
{
	return surface;
}

void Graphics::resize(int _w, int _h)
{
	w = _w; 
	h = _h;
 
	SDL_Surface* aux = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(aux, NULL, surface, NULL);

	SDL_FreeSurface(surface);
	surface = aux;
}

void Graphics::loadImage(char* src)
{
	/*
	SDL_Surface* temp = NULL;
	if((temp = IMG_Load(src)) == NULL) 
	{
		printf("no load image");
	}
	else
	{
		surface = SDL_ConvertSurface(temp, surface->format, NULL);
	}
	//SDL_FreeSurface(temp);
	SDL_FreeSurface(surface);
	*/
	SDL_Surface* temp = SDL_LoadBMP(src);
	if(temp != NULL)
	{
		surface = temp;//SDL_ConvertSurface(temp, 32, NULL);
	}

	w = surface->w;
	h = surface->h;
}

void Graphics::saveImage(char* src)
{
	SDL_SaveBMP(surface, src);
}

Uint32 Graphics::getPixel(int x, int y)
{	
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[ ( y * w ) + x ];

}

void Graphics::setPixel(int x, int y, Uint32 col)
{

	if( x < 0 || x >= w || y < 0 || y >= h)
	{
		return;
	}

	if(alpha(col) < 255)
	{
		col = lerpColor(getPixel(x, y), color(red(col), green(col), blue(col)), alpha(col)/256.);
	}

	Uint8 *bufp = (Uint8 *)surface->pixels + y*surface->pitch + x*surface->format->BytesPerPixel;
	switch (surface->format->BytesPerPixel) 
	{
		case 4:
		bufp[3] = col >> 24;
		case 3:
		bufp[2] = col >> 16;
		case 2:
		bufp[1] = col >> 8;
		case 1:
		bufp[0] = col;
	}
	return;
}

void Graphics::line(int x0, int y0, int x1, int y1)
{
	float ww = x1-x0;
	float hh = y1-y0;
	float len = sqrt((w*w)+(h*h));
	//strokeColor = 0x66FF0000;
	Uint32 sc = strokeColor;//color(red(strokeColor), green(strokeColor), blue(strokeColor), 20);
	if(len < 1)
	{
		setPixel(x0, y0, sc);
	}
	else
	{
		float dx = ww/len;
		float dy = hh/len;
		for(int i = 0; i < len; i++)
		{
			int xx = floor(x0+dx*i); 
			int yy = floor(y0+dy*i);
			setPixel(xx, yy, sc);
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
	fillColor = color(g);
}

void Graphics::stroke(Uint8 r, Uint8 g, Uint8 b)
{
	strokeColor = color(r, g, b);
}

void Graphics::stroke(Uint8 g)
{
	strokeColor = color(g);
}