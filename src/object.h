#ifndef DEF_OBJECT_H
#define DEF_OBJECT_H

#include <vector>
#include <SDL.h>
#include "defines.h"


class Object {
    private :
        std::vector<SDL_Surface *> m_pictures;
        int m_current;
        Case m_type;
        SDL_Rect m_pos;

    public :
        Object();
        ~Object();

        void set_pos(SDL_Rect *p);
        void set_picture(SDL_Surface *empty, SDL_Surface *o, SDL_Surface *w, SDL_Surface *wino, SDL_Surface *winx);
        void set_type(Case type);
        Case get_type();

        void init();
        bool same_type(Object &obj); 
        int display(SDL_Surface *dest);
        bool is_empty(); 
        bool is_inside(int x, int y); 
};

#endif
