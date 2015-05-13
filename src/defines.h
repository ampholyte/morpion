#ifndef DEF_DEFINES_H
#define DEF_DEFINES_H

#include <iostream>
#include <SDL.h>

#define ENGINE_CONFIG "../config/engine.cfg"

//#define NODEBUG
//#define NOVERBOSE

#ifndef NOVERBOSE
#define VERBOSE_PRINT() {std::cerr << __FILE__ << " : "<< __func__ << " l." << __LINE__ << std::endl;}
#else
#define VERBOSE_PRINT()
#endif


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GAME_SIZE = 3;
const int NB_PICTURES = 5;
const int NB_MENU_ITEM = 4;


typedef enum {
    EMPTY = 0,
    CIRCLE,
    CROSS,
    WIN
} Case;


#endif
