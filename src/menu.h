#ifndef DEF_MENU_H
#define DEF_MENU_H

#include <string>
#include <SDL.h>
#include "defines.h"

class Menu {
    private :
        SDL_Surface *m_pictures[4];
        SDL_Rect m_title, m_new, m_quit;

    public :
        Menu();
        ~Menu();

        int init(const std::string &filename);
        void click(int x, int y);
        int display(SDL_Surface *screen);
};

#endif
