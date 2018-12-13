#ifndef SPRITE_H
#define SPRITE_H

#include "math.h"
#include "config.h"

#include <stdbool.h>
#include "SDL.h"


typedef struct sprite
{
  SDL_Surface *bmp;
  SDL_Rect pos_perso;
  SDL_Rect coordo_perso;
  int colorkey;
  
  float angle;
  float x, y;
}*sprite_t;

void free_sprite(sprite_t  image);
sprite_t new_sprite(const char * image, SDL_Surface * screen);
bool collision( sprite_t perso, sprite_t serpent);
unsigned int collision_boss( sprite_t boss, sprite_t perso );
int rand_a_b(int a, int b);
#endif


