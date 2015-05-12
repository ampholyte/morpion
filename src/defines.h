#ifndef DEF_DEFINES_H
#define DEF_DEFINES_H

#define NODEBUG
#define NOVERBOSE

#include <iostream>
#include <SDL.h>

#define IMAGE_EMPTY "../images/empty.bmp"
#define IMAGE_O "../images/o.bmp"
#define IMAGE_X "../images/x.bmp"
#define IMAGE_BG "../images/bg.bmp"
#define IMAGE_WINO "../images/wino.bmp"
#define IMAGE_WINX "../images/winx.bmp"

#ifndef NOVERBOSE
#define VERBOSE_PRINT() {std::cerr << __FILE__ << " : "<< __func__ << " l." << __LINE__ << std::endl;}
#else
#define VERBOSE_PRINT()
#endif

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int GAME_SIZE = 3;
const int NB_PICTURES = 5;


typedef enum {
    EMPTY = 0,
    CROSS,
    CIRCLE,
    WIN
} Case;


#endif
