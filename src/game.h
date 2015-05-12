#ifndef DEF_GAME_H
#define DEF_GAME_H

#include <SDL.h>
#include "defines.h"
#include "object.h"



class Game {
    private :
        Object m_map[GAME_SIZE][GAME_SIZE];
        SDL_Surface *m_empty, *m_o, *m_x, *m_bg, *m_wino, *m_winx;
        Case m_turn, m_win;
        bool m_end;

        int init_surface();
        void free_surface();
        void build_game();
        void check_game();


    public :
        Game();
        ~Game();
        
        bool get_end();

        int init();
        void click(int x, int y);
        int display(SDL_Surface *screen);
        void empty_game();

};


#endif
