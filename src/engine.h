#ifndef DEF_ENGINE_H
#define DEF_ENGINE_H

#include <SDL.h>
#include "game.h"


class Engine {
    private :
        Game m_game;

    public : 
        Engine();
        ~Engine();

        int init();
        void click(int x, int y);
        int display(SDL_Surface *screen);
};

#endif
