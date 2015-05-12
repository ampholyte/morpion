#ifndef DEF_IA_H
#define DEF_IA_H

#include "defines.h"
#include "game.h"

const int MINEVAL = -100000;
const int MAXEVAL = 100000;



class Ia {
    private :
        Case m_current;

    public :
        Ia();
        ~Ia();

        void calc_ia(Game *game, int depth);

        int calc_min(Game *game, int depth);
        int calc_max(Game *game, int depth);

        int calc_score(int x, int y);
        int eval(Game *game);
        int nb_case(Game *game);
};

#endif
