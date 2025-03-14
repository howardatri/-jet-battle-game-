#ifndef OBJECT_H
#define OBJECT_H
#include <SDL.h>

struct player
{
    SDL_Texture *texture=nullptr;
    SDL_FPoint position={0,0};
    int width=0;
    int height=0;
    int speed=200;
    Uint32 coolDown=500;
    Uint32 lastShootTime=0;

};
struct ProjectilePlayer
{
    SDL_Texture *texture=nullptr;
    SDL_FPoint position={0,0};
    int width=0;
    int height=0;
    int speed=400;
};












#endif