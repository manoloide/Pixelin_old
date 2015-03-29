 #ifndef UTILITIES_H
 #define UTILITIES_H

#include "SDL2/SDL.h"

int min(int, int);
int max(int, int);
int constrain(int, int, int);

float map(float, float, float, float, float);


Uint32 color(Uint8);
Uint32 color(Uint8, Uint8);
Uint32 color(Uint8, Uint8, Uint8);
Uint32 color(Uint8, Uint8, Uint8, Uint8);


Uint8 red(Uint32);
Uint8 green(Uint32);
Uint8 blue(Uint32);
Uint8 alpha(Uint32);

 #endif