#include <iostream>
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
}



Game::~Game() {
    free_surface();
}



int Game::init() {
    int err;
    
    VERBOSE_PRINT();

    err = init_surface();
    if (err != 0) {
#ifndef NODEBUG
        std::cerr << "Game::init : error init_surface => Code error : " << err << std::endl;
#endif
        return (1);
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

    build_game();

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
    
    VERBOSE_PRINT();

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
        if (m_map[0][2].same_type(m_map[1][1]) && m_map[0][2].same_type(m_map[0][2])) {
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



int Game::init_surface() {
    
    VERBOSE_PRINT();

    free_surface();

    m_o = SDL_LoadBMP(IMAGE_O);
    if (m_o == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-1);
    }

    m_x = SDL_LoadBMP(IMAGE_X);
    if (m_x == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-2);
    }
    
    m_bg = SDL_LoadBMP(IMAGE_BG);
    if (m_bg == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-3);
    }
    
    m_wino = SDL_LoadBMP(IMAGE_WINO);
    if (m_wino == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-4);
    }

    m_winx = SDL_LoadBMP(IMAGE_WINX);
    if (m_winx == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-5);
    }
    
    m_empty = SDL_LoadBMP(IMAGE_EMPTY);
    if (m_empty == NULL) {
        std::cerr << "Game::init_surface : error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-6);
    }
   

    return (0);
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



void Game::build_game() {
    SDL_Rect r;
    int w, h;
    
    VERBOSE_PRINT();

    w = SCREEN_WIDTH / 3;
    h = SCREEN_HEIGHT / 3;    

    r.w = 150;
    r.h = 150;

    for (int i = 0; i < GAME_SIZE; i++) {
        r.y = i * h;
        for (int j = 0; j < GAME_SIZE; j++) { 
            r.x = j * w;

            m_map[i][j].set_pos(&r);
            m_map[i][j].set_picture(m_empty, m_o, m_x, m_wino, m_winx);
        }
    }
}



bool Game::get_end() {
   
    VERBOSE_PRINT();
  
    return (m_end);
}
