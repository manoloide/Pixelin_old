#include "SDL2/SDL.h"
#include <stdio.h>
#include <math.h> 

#include "coloreditor.h"
#include "events.h"
#include "global.h"
#include "layout.h"
#include "swatches.h"
#include "tools.h"
#include "utilities.h"
#include "view.h"


void init();
void close();
void resize();
void resize(int, int);
void render();

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
int screenWidth = 800;
int screenHeight = 600;

Events* events;
Global* global;
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
    if(global->allRender)
    {
        global->allRender = false;    
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

        events = Events::Instance();
        global = Global::Instance();

        baseLayout = new Layout();
        baseLayout->setStyle(baseLayout->Vertical); 

        Layout* v1 = new Layout(baseLayout);
        v1->setMaxHeight(22);
        Layout* v2 = new Layout(baseLayout);
        v2->setMaxHeight(28);
        Layout* v3 = new Layout(baseLayout);
        Layout* v4 = new Layout(baseLayout);
        v4->setMaxHeight(28);

        Tools* tools =  new Tools(v3);
        tools->setMaxWidth(80);
        View* h2 =  new View(v3);
        Layout* h3 =  new Layout(v3);
        h3->setStyle(baseLayout->Vertical); 
        h3->setMaxWidth(280);
        h3->setMinWidth(280);

        ColorEditor* colorEditor = new ColorEditor(h3);
        colorEditor->setMaxHeight(90);
        Swatches* swatches = new Swatches(h3);
        swatches->setMaxHeight(90);

        baseLayout->resize(screenWidth, screenHeight);
        baseLayout->show();

        SDL_Event e;

        while( !quit )
        {

            events->update();

            while( SDL_PollEvent( &e ) != 0 )
            {
                if(e.window.event == SDL_WINDOWEVENT_RESIZED){
                    resize(e.window.data1, e.window.data2); 
                }
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }

                if(e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        //quit = true;
                    }

                    if(e.key.keysym.sym == SDLK_LALT)
                    {
                        events->Alt = true;
                    }
                    if(e.key.keysym.sym == SDLK_LCTRL)
                    {
                        events->Ctrl = true;
                    }
                    if(e.key.keysym.sym == SDLK_LSHIFT)
                    {
                        events->Shift = true;
                    }
                }
                if(e.type == SDL_KEYUP)
                {
                    if(e.key.keysym.sym == SDLK_LALT)
                    {
                        events->Alt = false;
                    }
                    if(e.key.keysym.sym == SDLK_LCTRL)
                    {
                        events->Ctrl = false;
                    }
                    if(e.key.keysym.sym == SDLK_LSHIFT)
                    {
                        events->Shift = false;
                    }
                }

                if(e.type == SDL_MOUSEBUTTONUP)
                {
                    events->mouseButton = e.button.button;
                    events->mousePressed = false;
                }
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    events->mouseButton = e.button.button;
                    events->mousePressed = true;
                    events->mouseClicked = true;
                }
                if( e.type == SDL_MOUSEWHEEL)
                {
                    events->mouseWheel = e.wheel.y;
                }
            }

            SDL_PumpEvents();
            events->amouseX = events->mouseX; 
            events->amouseY = events->mouseY;
            SDL_GetMouseState( &events->mouseX, & events->mouseY);

            render();

            SDL_UpdateWindowSurface( window );
            SDL_Delay(20);
        }
    }

    close();
    return 0;
}