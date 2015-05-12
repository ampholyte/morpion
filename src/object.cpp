#include <iostream>
#include <SDL.h>

#include <cstdio>
#include "object.h"



Object::Object() {
    m_pictures.resize(NB_PICTURES);

    for (int i = 0; i < NB_PICTURES; i++) {
        m_pictures[i] = NULL;
    }

    m_current = 0;
    m_pos.x = 0;
    m_pos.y = 0;
    m_pos.w = 0;
    m_pos.h = 0;
}



Object::~Object() {
}



void Object::set_pos(SDL_Rect *p) {
    m_pos = *p;
}



void Object::set_picture(SDL_Surface *empty, SDL_Surface *o, SDL_Surface *x, SDL_Surface *wino, SDL_Surface *winx) {
    m_pictures[0] = empty;
    m_pictures[1] = o;
    m_pictures[2] = x;
    m_pictures[3] = wino;
    m_pictures[4] = winx;
}



void Object::set_type(Case type) {
    switch (type) {
        case EMPTY :
        case CIRCLE :
        case CROSS :
            m_type = type;
            m_current = type;
            break;
        case WIN :
            m_current = m_type + 2;
            break;
    }
}



Case Object::get_type() {
    return (m_type);
}



void Object::init() {
    m_current = 0;
    m_type = EMPTY;
}



bool Object::same_type(Object &obj) {
    return (obj.m_type == m_type);
}



int Object::display(SDL_Surface *dest) {
    if (dest == NULL) {
        return (-1);
    }

    if (m_pictures[m_current]) {
        SDL_BlitSurface(m_pictures[m_current], NULL, dest, &m_pos);
    }

    return (0);
}



bool Object::is_empty() {
    return (m_type == EMPTY);
}



bool Object::is_inside(int x, int y) {
    return ((x > m_pos.x && x < (m_pos.x + m_pos.w)) && (y > m_pos.y && y < (m_pos.y + m_pos.h)));
}



