#include <iostream>
#include <SDL.h>

#include "morpion.h"
#include "engine.h"


int main(void) {
    SDL_Event event;
    SDL_Surface *screen;
    Engine engine;
    int done;

    VERBOSE_PRINT();
    
    if (engine.init() != 0) {
#ifndef NODEBUG
        std::cerr << "error engine.init " << std::endl;
#endif
        return (1);
    } 

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr <<  "error SDL_Init : " << SDL_GetError() << std::endl;
        return (1);
    }

    SDL_WM_SetCaption("Morpion", NULL);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
    if (screen == NULL) {
        std::cerr << "error SDL_SetVideoMode : " << SDL_GetError() << std::endl;
        return (1);
    }

    done = 0;
    while (done == 0) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    done = 1; 
                    break;
                case SDL_KEYUP :
                    if (event.key.keysym.sym == SDLK_q) {
                        done = 1;
                    }
                    break;
                case SDL_MOUSEBUTTONUP :
                    engine.click(event.button.x, event.button.y);
                    break;
                default :
                    break;
            }
        }

        engine.display(screen);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(screen);
    screen = NULL;

    SDL_Quit();

    return (0);    
}
