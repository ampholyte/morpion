#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <SDL.h>

#include "game.h"



Game::Game() {
    empty_game();

    m_empty = NULL;
    m_o = NULL;
    m_x = NULL;
    m_bg = NULL;
    m_wino = NULL;
    m_winx = NULL;

    m_j1 = HUMAN;
    m_j2 = HUMAN;
}



Game::~Game() {
    free_surface();
}



int Game::init(const std::string &filename) {
    SDL_Rect r;
    
    VERBOSE_PRINT();

    free_surface();
    
    std::ifstream file(filename.c_str());
    if (file == NULL) {
        std::cerr << "Game::init_surface : error ifstream : " << filename << std::endl;
        return (-1);
    }

    std::string str;

    file >> str;
    m_o = SDL_LoadBMP(str.c_str());

    file >> str;
    m_x = SDL_LoadBMP(str.c_str());
    
    file >> str;
    m_bg = SDL_LoadBMP(str.c_str());
    
    file >> str;
    m_wino = SDL_LoadBMP(str.c_str());

    file >> str;
    m_winx = SDL_LoadBMP(str.c_str());
    
    file >> str;
    m_empty = SDL_LoadBMP(str.c_str());
    if (m_empty == NULL || m_o == NULL || m_x == NULL || m_winx == NULL || m_wino == NULL || m_bg == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-2);
    }

    m_turn = CIRCLE;

    if (SDL_SetColorKey(m_o, SDL_SRCCOLORKEY, 0) == -1) {
#ifndef NODEBUG
        std::cerr << "Game::init : error SDL_SetColorKey : " << SDL_GetError() << std::endl;
#endif
    }
    
    if (SDL_SetColorKey(m_x, SDL_SRCCOLORKEY, 0) == -1) {
#ifndef NODEBUG
        std::cerr << "Game::init : error SDL_SetColorKey : " << SDL_GetError() << std::endl;
#endif
    }
    
    if (SDL_SetColorKey(m_winx, SDL_SRCCOLORKEY, 0) == -1) {
#ifndef NODEBUG
        std::cerr << "Game::init : error SDL_SetColorKey : " << SDL_GetError() << std::endl;
#endif
    }
    
    if (SDL_SetColorKey(m_wino, SDL_SRCCOLORKEY, 0) == -1) {
#ifndef NODEBUG
        std::cerr << "Game::init : error SDL_SetColorKey : " << SDL_GetError() << std::endl;
#endif
    }
    
    if (SDL_SetAlpha(m_empty, SDL_SRCALPHA, 100) == -1) {
#ifndef NODEBUG
        std::cerr << "Game::init : error SDL_SetAlpha : " << SDL_GetError() << std::endl;
#endif
    }

    file >> r.w >> r.h;
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) { 
            file >> r.x >> r.y;
            m_map[i][j].set_pos(&r);
            m_map[i][j].set_picture(m_empty, m_o, m_x, m_wino, m_winx);
        }
    }

    file.close();

    return (0);
}



int Game::display(SDL_Surface *screen) {
    if (screen == NULL) {
        return (-1);
    } 

    SDL_BlitSurface(m_bg, NULL, screen, NULL);

    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            m_map[i][j].display(screen);
        }
    }

    return (0);
}



void Game::click(int x, int y) {
    bool find = false;
    
    VERBOSE_PRINT();

    if (!m_end) {
        for (int i = 0; i < GAME_SIZE; i++) {
            if (find) {
                break;
            }

            for (int j = 0; j < GAME_SIZE; j++) {
                if (find) {
                    break;
                }

                if (m_map[i][j].is_inside(x, y)) {
                    if (m_map[i][j].is_empty()) {
                        m_map[i][j].set_type(m_turn);

                        m_turn = (m_turn == CIRCLE) ? CROSS : CIRCLE;
                    }
                    
                    find = true;
                }
            }
        }    

        if (find) {
            check_game();
        }
    }
}



void Game::empty_game() {
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            m_map[i][j].init();
        }
    }

    m_turn = CIRCLE;
    m_end = false;
}



void Game::check_game() {
    bool isempty = false;

    m_win = EMPTY;
    m_end = false;
    
    for (int i = 0; i < GAME_SIZE; i++) {
        if (!m_map[i][0].is_empty()) {
            if (m_map[i][0].same_type(m_map[i][1]) && m_map[i][0].same_type(m_map[i][2])) {
                m_end = true;
                m_win = m_map[i][0].get_type();
                m_map[i][0].set_type(WIN);
                m_map[i][1].set_type(WIN);
                m_map[i][2].set_type(WIN);
            }       
        } else {
            isempty = true;
        }
    }
    
    for (int i = 0; i < GAME_SIZE; i++) {
        if (!m_map[0][i].is_empty()) {
            if (m_map[0][i].same_type(m_map[1][i]) && m_map[0][i].same_type(m_map[2][i])) {
                m_end = true;
                m_win = m_map[0][i].get_type();
                m_map[0][i].set_type(WIN);
                m_map[1][i].set_type(WIN);
                m_map[2][i].set_type(WIN);
            }       
        } else {
            isempty = true;
        }
    }

    if (!m_map[0][0].is_empty()) {
        if (m_map[0][0].same_type(m_map[1][1]) && m_map[0][0].same_type(m_map[2][2])) {
                m_end = true;
                m_win = m_map[0][0].get_type();
                m_map[0][0].set_type(WIN);
                m_map[1][1].set_type(WIN);
                m_map[2][2].set_type(WIN);
            
        }
    } else {
        isempty = true;
    }
    
    if (!m_map[0][2].is_empty()) {
        if (m_map[0][2].same_type(m_map[1][1]) && m_map[0][2].same_type(m_map[2][0])) {
                m_end = true;
                m_win = m_map[0][2].get_type();
                m_map[0][2].set_type(WIN);
                m_map[1][1].set_type(WIN);
                m_map[2][0].set_type(WIN);
            
        }
    } else {
        isempty = true;
    }

    if (m_map[1][1].is_empty() || m_map[1][2].is_empty()
            || m_map[2][1].is_empty()
            || m_map[2][2].is_empty()) {
        isempty = true;
    }
          
    m_end = !isempty || m_end; 
}



void Game::free_surface() {
    
    VERBOSE_PRINT();

    if (m_empty != NULL) {
        SDL_FreeSurface(m_empty);
        m_empty = NULL;
    }
    
    if (m_o != NULL) {   
        SDL_FreeSurface(m_o);
        m_o = NULL;
    }

    if (m_x != NULL) {
        SDL_FreeSurface(m_x);
        m_x = NULL;
    }

    if (m_bg != NULL) {
        SDL_FreeSurface(m_bg);
        m_bg = NULL;
    }

    if (m_wino != NULL) {
        SDL_FreeSurface(m_wino);
        m_wino = NULL;
    }

    if (m_winx != NULL) {
        SDL_FreeSurface(m_winx);
        m_winx = NULL; 
    }
}



Case Game::get_case(int i, int j) {
    return (m_map[i][j].get_type());
}



Case Game::get_win() {
    return (m_win);    
}



Case Game::get_turn() {
    return (m_turn);
}



bool Game::get_end() {
    return (m_end);
}



bool Game::is_human() {
    if (m_turn == CIRCLE) {
        return (m_j1 == HUMAN);
    } else {
        return (m_j2 == HUMAN);
    }
}



e_player Game::get_type_player() {
    if (m_turn == CIRCLE) {
        return (m_j1);
    } else {
        return (m_j2);
    }
}



bool Game::is_empty(int i, int j) {
    return (m_map[i][j].is_empty());
}



void Game::play(int i, int j) {
    m_map[i][j].set_type(m_turn);
    m_turn = (m_turn == CIRCLE) ? CROSS : CIRCLE;
    check_game();
}



void Game::revert(int i, int j) {
    m_map[i][j].set_type(EMPTY);
    
    for (int k = 0; k < GAME_SIZE; k++) {
        for (int l = 0; l < GAME_SIZE; l++) {
            m_map[k][l].set_type(m_map[k][l].get_type());
        }
    }

    m_turn = (m_turn == CIRCLE) ? CROSS : CIRCLE;
    check_game();
}



void Game::set_type_player(int i, int type) {
    if (i == 1) {
        m_j1 = (e_player)type;
    } else {
        m_j2 = (e_player)type;
    }
}

