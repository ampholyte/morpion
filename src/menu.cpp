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

    for (int i = 0; i < 4; i++) {
        m_typej[i] = NULL;
    } 

    m_labelj[0] = NULL;
    m_labelj[1] = NULL;

    m_j1 = 0;
    m_j2 = 0;
}



Menu::~Menu() {
    for (int i = 0; i < NB_MENU_ITEM; i++) {
        if (m_pictures[i] != NULL) {
            SDL_FreeSurface(m_pictures[i]);
            m_pictures[i] = NULL;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (m_typej[i] != NULL) {
            SDL_FreeSurface(m_typej[i]);
            m_typej[i] = NULL;
        }
    }

    if (m_labelj[0] != NULL) {
        SDL_FreeSurface(m_labelj[0]);
        m_labelj[0] = NULL;        
    }
    
    if (m_labelj[1] != NULL) {
        SDL_FreeSurface(m_labelj[1]);
        m_labelj[1] = NULL;        
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


    file >> str;
    m_labelj[0] = SDL_LoadBMP(str.c_str());
    file >> m_labelj1.x >> m_labelj1.y;
   
    file >> str; 
    m_labelj[1] = SDL_LoadBMP(str.c_str());
    file >> m_labelj2.x >> m_labelj2.y;

    if (m_labelj[0] == NULL || m_labelj[1] == NULL) {
        std::cerr << "Menu::init error SDL_LoadBMP : " << SDL_GetError() << std::endl;
        return (-3); 
    }
    SDL_SetColorKey(m_labelj[0], SDL_SRCCOLORKEY, 0);
    SDL_SetColorKey(m_labelj[1], SDL_SRCCOLORKEY, 0);


    for (int i = 0; i < 4; i++) {
        file >> str;
        m_typej[i] = SDL_LoadBMP(str.c_str());
        
        if (m_typej[i] == NULL) {
            std::cerr << "Menu::init error SDL_LoadBMP : " << SDL_GetError() << std::endl;
            return (-4);
        }

        SDL_SetColorKey(m_typej[i], SDL_SRCCOLORKEY, 0); 
    }

    file >> m_typej1.x >> m_typej1.y;
    file >> m_typej2.x >> m_typej2.y;

    file.close();

    return (0);
}



void Menu::click(int x, int y) {
    if ((m_new.x < x && (m_new.x + m_new.w) > x) && (m_new.y < y && (m_new.y + m_new.h) > y)) {
        engine.init_game();
        engine.set_function_game(); 
    } else if ((m_typej1.x < x && (m_typej1.x + m_typej[m_j1]->w > x)) && (m_typej1.y < y && (m_typej1.y + m_typej[m_j1]->h > y))) {
        m_j1 = (m_j1 + 1) % 4;
    } else if ((m_typej2.x < x && (m_typej2.x + m_typej[m_j2]->w > x)) && (m_typej2.y < y && (m_typej2.y + m_typej[m_j2]->h > y))) {
        m_j2 = (m_j2 + 1) % 4;
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

    if (m_labelj[0] == NULL || m_labelj[1] == NULL || m_typej[m_j1] == NULL || m_typej[m_j2] == NULL) {
        return (-3);
    }

    SDL_BlitSurface(m_pictures[0], NULL, screen, NULL);
    SDL_BlitSurface(m_pictures[1], NULL, screen, &m_title);
    SDL_BlitSurface(m_pictures[2], NULL, screen, &m_new);
    SDL_BlitSurface(m_pictures[3], NULL, screen, &m_quit);
    SDL_BlitSurface(m_labelj[0], NULL, screen, &m_labelj1);
    SDL_BlitSurface(m_labelj[1], NULL, screen, &m_labelj2);
    SDL_BlitSurface(m_typej[m_j1], NULL, screen, &m_typej1);
    SDL_BlitSurface(m_typej[m_j2], NULL, screen, &m_typej2);

    return (0);
}



int Menu::get_type(int i) {
    if (i == 1) {
        return (m_j1);
    } else {
        return (m_j2);
    }
}
