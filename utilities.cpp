#include "utilities.h"

/*
int min(int v1, int v2){
	int aux = v1;
	if(aux > v2){
		aux = v2;
	}
	return aux;
}

int max(int v1, int v2){
	int aux = v1;
	if(aux < v2){
		aux = v2;
	}
	return aux;
}

int constrain(float v, float mn, float mx){
	return min(mx, max(v, mn));
}
*/
float dist(float x1, float y1, float x2, float y2){
	return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}

float min(float v1, float v2){
	float aux = v1;
	if(aux > v2){
		aux = v2;
	}
	return aux;
}

float max(float v1, float v2){
	float aux = v1;
	if(aux < v2){
		aux = v2;
	}
	return aux;
}

float constrain(float v, float mn, float mx){
	return min(mx, max(v, mn));
}

float map(float v, float min1, float max1, float min2, float max2){
	return min2 + (max2 - min2) * ((v - min1) / (max1 - min1));
}

Uint32 color(Uint8 g){
	color(g, g, g, 255);
}

Uint32 color(Uint8 g, Uint8 a){
	color(g, g, g, a);
}

Uint32 color(Uint8 r, Uint8 g, Uint8 b){
	color(r, g, b, 255);
}

Uint32 color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	return (Uint32) a <<24 | r << 16 | g << 8 | b;
}

Uint8 red(Uint32 col){
	Uint32 temp =  col&0x00FF0000;
	temp =  temp>>16;
	return (Uint8) temp;
}

Uint8 green(Uint32 col){
	Uint32 temp =  col&0x0000FF00;
	temp =  temp>>8;
	return (Uint8) temp;
}

Uint8 blue(Uint32 col){
	Uint32 temp =  col&0x000000FF;
	temp =  temp>>0;
	return (Uint8) temp;
}

Uint8 alpha(Uint32 col){
	Uint32 temp =  col&0xFF000000;
	temp =  temp>>24;
	return (Uint8) temp;
}

Uint32 lerpColor(Uint32 c1, Uint32 c2, float v){
	if(v <= 0) return c1;
	if(v >= 1) return c2;
	int r = map(v, 0, 1, red(c1), red(c2));
	int g = map(v, 0, 1, green(c1), green(c2));
	int b = map(v, 0, 1, blue(c1), blue(c2));
	int a = map(v, 0, 1, alpha(c1), alpha(c2));
	return color(r, g, b, a);
}

Uint32 getPixel(SDL_Surface* surface, int x, int y)
{	
	int w = surface->w;
	int h = surface->h;
	if( x < 0 || x >= w || y < 0 || y >= h)
	{
		return NULL;
	}
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[ ( y * w ) + x ];

}

void setPixel(SDL_Surface* surface, int x, int y, Uint32 col)
{
	int w = surface->w;
	int h = surface->h;
	if( x < 0 || x >= w || y < 0 || y >= h)
	{
		return;
	}

	if(alpha(col) < 255)
	{
		col = lerpColor(getPixel(surface, x, y), color(red(col), green(col), blue(col)), alpha(col)/256.);
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


SDL_Surface* mixerSurface(SDL_Surface* s1, SDL_Surface* s2)
{
	SDL_Surface* aux = SDL_CreateRGBSurface(0, s1->w, s1->h, 32, 0, 0, 0, 0);

	for(int j = 0; j < aux->h; j++)
	{
		for(int i = 0; i < aux->w; i++)
		{
			Uint32 c1 = getPixel(s1, i, j);
			Uint32 c2 = getPixel(s2, i, j);
			if(c2 == NULL){
				setPixel(aux, i, j, c1);
			}else{
				setPixel(aux, i, j, c2);
			}
			/*
			if(alpha(c2) == 255)
			{
				setPixel(aux, i, j, c2);
			}else if(alpha(c2) == 0){
				setPixel(aux, i, j, c1);
			}else{
				setPixel(aux, i, j, lerpColor(c1, c2, alpha(c2)/256.));
			}*/
			}
		}

		return aux;

	}