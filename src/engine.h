#ifndef DEF_ENGINE_H
#define DEF_ENGINE_H

#include <string.h>
#include <SDL.h>
#include "game.h"
#include "menu.h"

class Engine {
    private :
        Game *m_game;
        Menu *m_menu;
        bool m_ismenu;

    public : 
        Engine();
        ~Engine();

        int init();
        void click(int x, int y);
        int display(SDL_Surface *screen);
        void init_game();
        void set_function_game();
        void set_function_menu();
        void swap_function();
        void end();
};

#endif
