#include <iostream>
#include <ctime>

#include "ia.h"
#include "game.h"
#include "defines.h"



Ia::Ia() {
    std::srand(time(NULL));
}



Ia::~Ia() {
}



int Ia::calc_score(int cpttot, int cptplayer) {
    switch (cpttot) {
        case 1 : 
            return (10 * cptplayer);
            break;
        case 2 :
            return (30 * cptplayer);
            break;
        default :
            break;
    }

    return (0);
}



int Ia::eval(Game *game) {
    int cptplayer, cpttot;
    int score;

    if (game->get_end()) {
        if (game->get_win() == m_current) {
            return (1000 - nb_case(game));
        } else if (game->get_win() == EMPTY) {
            return (0);
        } else {
            return (-1000 + nb_case(game));
        }
    }

    score = 0;
    cptplayer = 0;
    cpttot = 0;
    for (int i = 0; i < GAME_SIZE; i++) {
        if (!game->is_empty(i, i)) {
            cpttot++;

            if (game->get_case(i, i) == m_current) {
                cptplayer++;
            } else {
                cptplayer--;
            }
        }
    }
    score += calc_score(cpttot, cptplayer);
    
    cptplayer = 0;
    cpttot = 0;
    for (int i = 0; i < GAME_SIZE; i++) {
        if (!game->is_empty(i, (GAME_SIZE - 1) - i)) {
            cpttot++;

            if (game->get_case(i, (GAME_SIZE - 1) - i) == m_current) {
                cptplayer++;
            } else {
                cptplayer--;
            }
        }
    }
    score += calc_score(cpttot, cptplayer);

    for (int i = 0; i < GAME_SIZE; i++) {
        cptplayer = 0;
        cpttot = 0;
        
        for (int j = 0; j < GAME_SIZE; j++) {
            if (game->get_case(i, j) != EMPTY) {
                cpttot++;
                
                if (game->get_case(i, j) == m_current) {
                    cptplayer++;
                } else {
                    cptplayer--;
                }
            }
        }

        score += calc_score(cpttot, cptplayer);
    }
    
    for (int i = 0; i < GAME_SIZE; i++) {
        cptplayer = 0;
        cpttot = 0;
        
        for (int j = 0; j < GAME_SIZE; j++) {
            if (game->get_case(j, i) != EMPTY) {
                cpttot++;
                
                if (game->get_case(j, i) == m_current) {
                    cptplayer++;
                } else {
                    cptplayer--;
                }
            }
        }

        score += calc_score(cpttot, cptplayer);
    }
       
    return (score);
}



void Ia::calc_ia(Game *game, int depth) {
    int tmp, a, b;
    int maxi, maxj;

    VERBOSE_PRINT();
    
    a = MINEVAL;
    b = MAXEVAL;
    maxi = -1;
    maxj = -1;
    
    m_current = game->get_turn();

    if (depth != 0 || !game->get_end()) {
        for (int i = 0; i < GAME_SIZE; i++) {
            for (int j = 0; j < GAME_SIZE; j++) {
                if (game->is_empty(i, j)) {
                    game->play(i, j);

                    tmp = calc_min(game, depth - 1, a, b);

                    if (a < tmp) {
                        a = tmp;
                        maxi = i;
                        maxj = j;
                    }

                    game->revert(i, j);
                }
            }   
        }

        game->play(maxi, maxj);
    }
}



int Ia::calc_min(Game *game, int depth, int a, int b) {
    int tmp;


    if (depth == 0 || game->get_end()) {
        return eval(game);
    }

    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (game->is_empty(i, j)) {
                game->play(i, j);
                tmp = calc_max(game, depth - 1, a, b);
                game->revert(i, j);

                if (b > tmp) {
                    b = tmp;
                }

                if (b <= a) {
                    return (b);
                }
            }
        }
    }

    return (b);
}



int Ia::calc_max(Game *game, int depth, int a, int b) {
    int tmp;

    if (depth == 0 || game->get_end()) {
        return eval(game);
    }

    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (game->is_empty(i, j)) {
                game->play(i, j);
                tmp = calc_min(game, depth - 1, a, b);
                game->revert(i, j);
                
                if (a < tmp) {
                    a = tmp;
                }

                if (b <= a) {
                    return (a);
                }

            }
       }
    }

    return (a);
}



int Ia::nb_case(Game *game) {
    int cpt = 0;

    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (game->get_case(i, j) != EMPTY) {
                cpt++;
            }
        }
    }

    return (cpt);
}
