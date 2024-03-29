#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h> 

#include "coloreditor.h"
#include "events.h"
#include "global.h"
#include "layout.h"
#include "swatches.h"
#include "toolmenu.h"
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
View* view;

bool quit = false;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    IMG_Init(flags);

    window = SDL_CreateWindow("Pixelin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_RESIZABLE);
}

void close()
{
    //provicional delete view
    delete view;
    //delete all interface
    //delete baseLayout;

    SDL_DestroyWindow(window);
    IMG_Quit();
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
    //resize(screenWidth, screenHeight);
    baseLayout->show();
    SDL_BlitSurface(baseLayout->getSurface(), NULL, screen, NULL);
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
        ToolMenu* toolMenu = new ToolMenu(baseLayout);
        toolMenu->setMaxHeight(28);
        Layout* v3 = new Layout(baseLayout);
        Layout* v4 = new Layout(baseLayout);
        v4->setMaxHeight(28);

        Tools* tools =  new Tools(v3);
        tools->setMaxWidth(80);
        view =  new View(v3);
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

            SDL_PumpEvents();
            events->amouseX = events->mouseX; 
            events->amouseY = events->mouseY;
            SDL_GetMouseState( &events->mouseX, &events->mouseY);
            if(events->amouseX != events->mouseX || events->amouseY != events->mouseY)
            {
                events->mouseDragged = true;
            }

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
                    events->mouseReleased = true;
                }
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    events->mouseButton = e.button.button;
                    events->mousePressed = true;
                    events->mouseClicked = true;

                    events->cmouseX = events->mouseX;
                    events->cmouseY = events->mouseY;
                }
                if( e.type == SDL_MOUSEWHEEL)
                {
                    events->mouseWheel = e.wheel.y;
                }
            }


            render();
            

            SDL_UpdateWindowSurface( window );
            SDL_Delay(20);
        }
    }

    //SDL_SaveBMP(view->getCanvas()->get(), "img.bmp");

    close();
    return 0;
}