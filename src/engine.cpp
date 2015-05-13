#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#include "defines.h"
#include "engine.h"
#include "game.h"
#include "menu.h"
#include "ia.h"


Engine::Engine() {
    m_game = new Game();
    m_menu = new Menu();
    m_ia = new Ia();
    m_ismenu = true;
}



Engine::~Engine() {
    delete m_game;
    delete m_menu;
    delete m_ia;
}



int Engine::init() {
    std::ifstream file(ENGINE_CONFIG);
    int err;

    if (file == NULL) {
        std::cerr << "Engine::init : error ifstream : " << ENGINE_CONFIG << std::endl;
        return (-1);
    }

    std::string str1, str2;
    file >> str1 >> str2;

    err = m_game->init(str1);
    if (err != 0) {
#ifndef NODEBUG
        std::cerr << "Engine::init : error m_game->init : Code error : " << err << std::endl;
#endif
        return (-2);
    }
    
    err = m_menu->init(str2);
    if (err != 0) {
#ifndef NODEBUG
        std::cerr << "Engine::init : error m_menu->init : Code error : " << err << std::endl;
#endif
        return (-3);
    }

    return (0);
}



void Engine::click(int x, int y) { 
    VERBOSE_PRINT();

    if (m_ismenu) {
        m_menu->click(x, y);
    } else {
        if (m_game->get_end()) {
            m_game->empty_game();
        } else {
            m_game->click(x, y);
        }
    }
}



int Engine::display(SDL_Surface *screen) {
    if (screen == NULL) {
        return (-1);
    }

    if (m_ismenu) {
        m_menu->display(screen);
    } else {
        m_game->display(screen);
    }

    return (0);
}



void Engine::init_game() {
    m_game->empty_game();
}



void Engine::swap_function() {
    m_ismenu = !m_ismenu;
    update_type_player();
}



void Engine::set_function_game() {
    m_ismenu = false;
    update_type_player();
}



void Engine::set_function_menu() {
    m_ismenu = true;
}



void Engine::check() {
    if (!m_ismenu) {
        if (!m_game->get_end()) {
            if (!m_game->is_human()) {
                switch (m_game->get_type_player()) {
                    case EASY :
                        m_ia->calc_ia(m_game, 2);
                        break;
                    case MEDIUM :
                        m_ia->calc_ia(m_game, 4);
                        break;
                    case HARD :
                        m_ia->calc_ia(m_game, 9);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}



void Engine::update_type_player() {
    m_game->set_type_player(1, m_menu->get_type(1));
    m_game->set_type_player(2, m_menu->get_type(2));
}


void Engine::end() {
    SDL_Event ev;

    ev.type = SDL_QUIT;
    SDL_PushEvent(&ev);
}
