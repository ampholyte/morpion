#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#include "defines.h"
#include "engine.h"
#include "game.h"
#include "menu.h"


Engine::Engine() {
    m_game = new Game();
    m_menu = new Menu();
    m_ismenu = true;
}



Engine::~Engine() {
    delete m_game;
    delete m_menu;
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
}



void Engine::set_function_game() {
    m_ismenu = false;
}



void Engine::set_function_menu() {
    m_ismenu = true;
}



void Engine::end() {
    SDL_Event ev;

    ev.type = SDL_QUIT;
    SDL_PushEvent(&ev);
}
