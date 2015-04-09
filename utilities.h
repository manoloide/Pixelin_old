 #ifndef UTILITIES_H
 #define UTILITIES_H

#include "SDL2/SDL.h"

/*
int min(int, int);
int max(int, int);
int constrain(int, int, int);
*/
float dist(float, float, float, float);
float min(float, float);
float max(float, float);
float constrain(float, float, float);

float map(float, float, float, float, float);


Uint32 color(Uint8);
Uint32 color(Uint8, Uint8);
Uint32 color(Uint8, Uint8, Uint8);
Uint32 color(Uint8, Uint8, Uint8, Uint8);


Uint8 red(Uint32);
Uint8 green(Uint32);
Uint8 blue(Uint32);
Uint8 alpha(Uint32);

Uint32 setRed(Uint32, Uint8);
Uint32 setGreen(Uint32, Uint8);
Uint32 setBlue(Uint32, Uint8);
Uint32 setAlpha(Uint32, Uint8);

Uint32 lerpColor(Uint32, Uint32, float);

SDL_Surface* mixerSurface(SDL_Surface* s1, SDL_Surface* s2);

 #endif