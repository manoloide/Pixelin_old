#include "utilities.h"

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

int constrain(int v, int mn, int mx){
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