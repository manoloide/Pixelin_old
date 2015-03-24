#include "SDL2/SDL.h"
#include <stdio.h>
#include <math.h> 


#include "canvas.h"
#include "graphics.h"
#include "layout.h"
#include "utilities.h"

void init();
void close();
void resize();
void resize(int, int);
void render();

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
int screenWidth = 640;
int screenHeight = 480;

Graphics* canvas;

Layout* baseLayout;// = new Layout();

bool quit = false;

int amouseX = 0; 
int amouseY = 0;
int mouseX = 0;
int mouseY = 0;
bool mousePressed = false;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Pixelin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);
}

void close()
{

    SDL_DestroyWindow(window);
    SDL_Quit();

}

void resize(int w, int h)
{
    SDL_FreeSurface(screen);
    screen = SDL_GetWindowSurface(window);

    screenWidth = w;
    screenHeight = h;
    baseLayout->resize(w, h);
    baseLayout->show();

    //render();
}

void render()
{
    //SDL_SetRenderDrawColor(image, 0xff, 0xff, 0xff, 0xff );
    //SDL_RenderDrawLine(image, amouseY, amouseY, mouseX, mouseY);
    //SDL_RenderDrawLine(image, amouseX, amouseX, mouseX, mouseY);
    //setPixel(image, mouseX, mouseY, 255, 0, 0);


    if(mousePressed)
    {   
        //printf("%i %i %i %i\n", amouseX, amouseY, mouseX, mouseY);
        canvas->stroke(5);
        canvas->line(amouseX, amouseY, mouseX, mouseY);
    }

    baseLayout->show();
    //image(screen, canvas,  screen->w/2, screen->h/2);
    SDL_BlitSurface(baseLayout->getSurface(), NULL, screen, NULL);
    //SDL_BlitSurface(canvas->get(), NULL, screen, NULL);
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
        canvas = new Graphics(200, 200);
        canvas->background(220);

        baseLayout = new Layout();
        baseLayout->setStyle(baseLayout->Vertical); 

        Layout* v1 = new Layout(baseLayout);
        v1->setMaxHeight(22);
        Layout* v2 = new Layout(baseLayout);
        v2->setMaxHeight(28);
        Layout* v3 = new Layout(baseLayout);
        Layout* v4 = new Layout(baseLayout);
        v4->setMaxHeight(28);

        Layout* h1 =  new Layout(v3);
        h1->setMaxWidth(80);
        Canvas* h2 =  new Canvas(v3);
        Layout* h3 =  new Layout(v3);
        h3->setMaxWidth(180);


        baseLayout->resize(screenWidth, screenHeight);
        baseLayout->show();

        SDL_Event e;

        while( !quit )
        {

            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.window.event == SDL_WINDOWEVENT_RESIZED){
                    resize(e.window.data1, e.window.data2); 
                }
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
                if( e.type == SDL_MOUSEMOTION )
                {
                    mouseX = e.motion.x;
                    mouseY = e.motion.y;
                    /*
                    amouseX = mouseX; 
                    amouseY = mouseY;
                    SDL_GetMouseState( &mouseX, &mouseY );
                    */
                }
            }

            render();

            SDL_UpdateWindowSurface( window );
            SDL_Delay(2);
        }
    }

    close();
    return 0;
}