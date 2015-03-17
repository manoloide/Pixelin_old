#include "SDL2/SDL.h"
#include <stdio.h>


SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *image = NULL;

bool quit = false;
int amouseX = 0; 
int amouseY = 0;
int mouseX = 0;
int mouseY = 0;


void setPixel(SDL_Surface *Surface, int x, int y,Uint8 R, Uint8 G,Uint8 B)
{

    if( x < 0 || x >= Surface->w || y < 0 || y >= Surface->h)
    {
        return;
    }
    Uint32 color = SDL_MapRGB(Surface->format, R, G, B);
    Uint8 *  bufp= (Uint8 *)Surface->pixels + y*Surface->pitch + x*Surface->format->BytesPerPixel;
    switch (Surface->format->BytesPerPixel) {
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

void init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Pixelin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
}

void close()
{

    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void render()
{
    //SDL_SetRenderDrawColor(image, 0xff, 0xff, 0xff, 0xff );
    //SDL_RenderDrawLine(image, amouseY, amouseY, mouseX, mouseY);
    setPixel(image, mouseX, mouseY, 255, 0, 0);
    SDL_Rect srect;
    srect.x = screen->w/2-image->w/2;
    srect.y = screen->h/2-image->h/2;
    srect.w = image->w;
    srect.h = image->h;
    SDL_BlitSurface( image, NULL, screen, &srect );
}

int main(int argc, char* argv[]) 
{
    init();

    if (window == NULL) 
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    else
    {

        screen = SDL_GetWindowSurface( window );
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 100, 100, 100));
        image = SDL_CreateRGBSurface(0,200,200,32,0,0,0,0);
        SDL_FillRect(image, NULL, SDL_MapRGB(image->format, 250, 250, 250));
        
        SDL_Event e;

        while( !quit )
        {

            while( SDL_PollEvent( &e ) != 0 )
            {

                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                amouseX = mouseX; 
                amouseY = mouseY;
                SDL_GetMouseState( &mouseX, &mouseY );
            }

            render();

            SDL_UpdateWindowSurface( window );
            SDL_Delay(2);
        }
    }

    close();
    return 0;
}