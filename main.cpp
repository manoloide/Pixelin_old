#include "SDL2/SDL.h"
#include <stdio.h>


SDL_Window *window = NULL;
SDL_Surface* screen = NULL;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Pixelin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
}

void close()
{

    SDL_DestroyWindow(window);
    SDL_Quit();

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

        bool quit = false;
        int mouseX = 0;
        int mouseY = 0;
        
        SDL_Event e;

        while( !quit )
        {

            while( SDL_PollEvent( &e ) != 0 )
            {

                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                SDL_GetMouseState( &mouseX, &mouseY );
            }

            SDL_UpdateWindowSurface( window );
            SDL_Delay(2);
        }
    }

    close();
    return 0;
}