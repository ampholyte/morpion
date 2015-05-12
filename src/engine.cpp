#include <iostream>
#include <SDL.h>

#include "engine.h"
#include "game.h"



Engine::Engine()  {
}



Engine::~Engine() {
}



int Engine::init() { 
    return (m_game.init());
}



void Engine::click(int x, int y) {
    
    VERBOSE_PRINT();
    
    if (m_game.get_end()) {
        m_game.empty_game();
    } else {
        m_game.click(x, y);
    }
}



int Engine::display(SDL_Surface *screen) {
    if (screen == NULL) {
        return (-1);
    }

    m_game.display(screen);

    return (0);
}
