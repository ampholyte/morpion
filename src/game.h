#ifndef DEF_GAME_H
#define DEF_GAME_H

#include <SDL.h>
#include "defines.h"
#include "object.h"


typedef enum e_player {
    HUMAN, EASY, MEDIUM, HARD
};



class Game {
    private :
        Object m_map[GAME_SIZE][GAME_SIZE];
        SDL_Surface *m_empty, *m_o, *m_x, *m_bg, *m_wino, *m_winx;
        Case m_turn, m_win;
        e_player m_j1, m_j2;
        bool m_end;

        void free_surface();
        void check_game();


    public :
        Game();
        ~Game();
        
        bool get_end();
        Case get_win();
        Case get_turn();
        Case get_case(int i, int j);
        e_player get_type_player();
        void set_type_player(int i, int type);

        int init(const std::string &filename);
        void click(int x, int y);
        int display(SDL_Surface *screen);
        void empty_game();
        bool is_human();
        bool is_empty(int i, int j);
        void play(int i, int j);
        void revert(int i, int j);

};


#endif
