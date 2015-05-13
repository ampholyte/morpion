#ifndef DEF_MENU_H
#define DEF_MENU_H

#include <string>
#include <SDL.h>
#include "defines.h"

class Menu {
    private :
        SDL_Surface *m_pictures[4], *m_typej[4], *m_labelj[2];
        SDL_Rect m_title, m_new, m_quit;
        SDL_Rect m_labelj1, m_labelj2;
        SDL_Rect m_typej1, m_typej2;
        int m_j1, m_j2;

    public :
        Menu();
        ~Menu();

        int init(const std::string &filename);
        void click(int x, int y);
        int display(SDL_Surface *screen);
        int get_type(int i);
};

#endif
