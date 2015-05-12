#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#include "defines.h"
#include "engine.h"
#include "menu.h"

extern Engine engine;



Menu::Menu() {
    for (int i = 0; i < NB_MENU_ITEM; i++) {
        m_pictures[i] = NULL;
    }
}



Menu::~Menu() {
    for (int i = 0; i < NB_MENU_ITEM; i++) {
        if (m_pictures[i] != NULL) {
            SDL_FreeSurface(m_pictures[i]);
            m_pictures[i] = NULL;
        }
    }
}



int Menu::init(const std::string &filename) {
    std::ifstream file(filename.c_str());

    if (file == NULL) {
        std::cerr << "Menu::init : error ifstream : " << filename << std::endl;
        return (-1);
    }

    std::string str;

    file >> str;
    m_pictures[0] = SDL_LoadBMP(str.c_str());

    file >> str;
    m_pictures[1] = SDL_LoadBMP(str.c_str());
    file >> m_title.x >> m_title.y;

    file >> str;
    m_pictures[2] = SDL_LoadBMP(str.c_str());
    file >> m_new.x >> m_new.y;

    file >> str;
    m_pictures[3] = SDL_LoadBMP(str.c_str());
    file >> m_quit.x >> m_quit.y;
   
    for (int i = 0; i < NB_MENU_ITEM; i++) {
        if (m_pictures[i] == NULL) {
            std::cerr << "Menu::init error SDL_LoadBMP : " << SDL_GetError() << std::endl;
            return (-2);
        }

        SDL_SetColorKey(m_pictures[i], SDL_SRCCOLORKEY, 0);
    }

    m_title.w = m_pictures[1]->w;
    m_title.h = m_pictures[1]->h;

    m_new.w = m_pictures[2]->w;
    m_new.h = m_pictures[2]->h;
    
    m_quit.w = m_pictures[3]->w;
    m_quit.h = m_pictures[3]->h;

    file.close();

    return (0);
}



void Menu::click(int x, int y) {
    if ((m_new.x < x && (m_new.x + m_new.w) > x) && (m_new.y < y && (m_new.y + m_new.h) > y)) {
        engine.init_game();
        engine.set_function_game(); 
    }
    
    if ((m_quit.x < x && (m_quit.x + m_quit.w) > x) && (m_quit.y < y && (m_quit.y + m_quit.h) > y)) {
        engine.end();
    }
}



int Menu::display(SDL_Surface *screen) {
    if (screen == NULL) {
        return (-1);
    }

    for (int i = 0; i < NB_MENU_ITEM; i++) {
        if (m_pictures[i] == NULL) {
            return (-2);
        }        
    }

    SDL_BlitSurface(m_pictures[0], NULL, screen, NULL);
    SDL_BlitSurface(m_pictures[1], NULL, screen, &m_title);
    SDL_BlitSurface(m_pictures[2], NULL, screen, &m_new);
    SDL_BlitSurface(m_pictures[3], NULL, screen, &m_quit);

    return (0);
}
