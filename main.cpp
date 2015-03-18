#include "SDL2/SDL.h"
#include <stdio.h>
#include <math.h> 

#include "graphics.h"
#include "utilities.h"

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
Graphics canvas(200, 200);

bool quit = false;

int amouseX = 0; 
int amouseY = 0;
int mouseX = 0;
int mouseY = 0;
bool mousePressed = false;

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

void render()
{
    //SDL_SetRenderDrawColor(image, 0xff, 0xff, 0xff, 0xff );
    //SDL_RenderDrawLine(image, amouseY, amouseY, mouseX, mouseY);
    //SDL_RenderDrawLine(image, amouseX, amouseX, mouseX, mouseY);
    //setPixel(image, mouseX, mouseY, 255, 0, 0);


    if(mousePressed)
    {   
        canvas.stroke(5);
        canvas.line(amouseX, amouseY, mouseX, mouseY);
    }

    //image(screen, canvas,  screen->w/2, screen->h/2);
    SDL_BlitSurface(canvas.get(), NULL, screen, NULL);
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

        screen = SDL_GetWindowSurface(window);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 100, 100, 100));
        canvas.background(220);
        /*
        canvas = SDL_CreateRGBSurface(0,200,200,32,0,0,0,0);
        SDL_FillRect(canvas, NULL, SDL_MapRGB(canvas->format, 250, 250, 250));
        */
        SDL_Event e;

        while( !quit )
        {

            while( SDL_PollEvent( &e ) != 0 )
            {

                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                if( e.type == SDL_MOUSEBUTTONUP )
                {
                    mousePressed = false;
                }
                if( e.type == SDL_MOUSEBUTTONDOWN )
                {
                    mousePressed = true;
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