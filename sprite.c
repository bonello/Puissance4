#include "config.h"
#include "sprite.h"
#include <string.h>

void free_sprite(sprite_t image)
{
  SDL_FreeSurface(image->bmp);
  free(image);
}

sprite_t new_sprite (const char * image, SDL_Surface *screen)
{
  sprite_t n_sprite = (sprite_t)malloc(sizeof(struct sprite));

  SDL_Surface * temp = SDL_LoadBMP (image);
  n_sprite -> bmp = SDL_DisplayFormat (temp);
  SDL_FreeSurface (temp);
  n_sprite->colorkey = SDL_MapRGB(screen->format, 255, 0, 0);
  SDL_SetColorKey(n_sprite->bmp, SDL_SRCCOLORKEY | SDL_RLEACCEL, n_sprite->colorkey);
 
  
  if(strcmp(image,PERSONNAGE1) == 0)
    {
      n_sprite->coordo_perso.x = SCREEN_WIDTH;
      n_sprite->coordo_perso.y = SCREEN_HEIGHT / 2;
      n_sprite->pos_perso.x = 0;
      n_sprite->pos_perso.y = 0;
      n_sprite->pos_perso.w = TAILLE_HEROS_X;
      n_sprite->pos_perso.h = TAILLE_HEROS_Y;
    }
  if(strcmp(image,PERSONNAGE2) == 0)
    {
      n_sprite->coordo_perso.x = SCREEN_WIDTH / 2;
      n_sprite->coordo_perso.y = SCREEN_HEIGHT / 2;
      n_sprite->pos_perso.x = 0;
      n_sprite->pos_perso.y = 0;
      n_sprite->pos_perso.w = 62.5; //114
      n_sprite->pos_perso.h = 54;
    }
  if(strcmp(image,PERSONNAGE3) == 0)
    {
      n_sprite->coordo_perso.x = SCREEN_WIDTH / 2;
      n_sprite->coordo_perso.y = SCREEN_HEIGHT / 2;
      n_sprite->pos_perso.x = 0;
      n_sprite->pos_perso.y = 0;
      n_sprite->pos_perso.w = 93.75;
      n_sprite->pos_perso.h = 81;
    }
  if(strcmp(image,PERSONNAGE4) == 0)
    {
      n_sprite->coordo_perso.x = SCREEN_WIDTH / 2;
      n_sprite->coordo_perso.y = SCREEN_HEIGHT / 2;
      n_sprite->pos_perso.x = 0;
      n_sprite->pos_perso.y = 0;
      n_sprite->pos_perso.w = 125;
      n_sprite->pos_perso.h = 108;
    }
  if(strcmp(image,PERSONNAGE5) == 0)
    {
      n_sprite->coordo_perso.x = SCREEN_WIDTH / 2;
      n_sprite->coordo_perso.y = SCREEN_HEIGHT / 2;
      n_sprite->pos_perso.x = 0;
      n_sprite->pos_perso.y = 0;
      n_sprite->pos_perso.w = 156.25;
      n_sprite->pos_perso.h = 135;
    }

  return n_sprite;
}

bool collision( sprite_t perso, sprite_t serpent )
{
  double leftb, leftc;
  double rightb, rightc;
  double topb, topc;
  double bottomb, bottomc;

  leftc =  perso->coordo_perso.x;
  rightc =  perso->coordo_perso.x + perso->pos_perso.w;
  topc =  perso->coordo_perso.y;
  bottomc = perso->coordo_perso.y + perso->pos_perso.h;
 
  leftb = serpent->coordo_perso.x;
  rightb = serpent->coordo_perso.x + serpent->pos_perso.w;
  topb = serpent->coordo_perso.y;
  bottomb = serpent->coordo_perso.y + serpent->pos_perso.h;

  if( bottomb <= topc || topb >= bottomc || rightb <= leftc || leftb >= rightc )
    {
      return false;
    }

  return true;
}

/* COLLISION AVEC LE BOSS */
unsigned int collision_boss(sprite_t boss, sprite_t perso)
{
  double leftb, leftc;
  double rightb, rightc;
  double topb, topc;
  double bottomb, bottomc;

  leftc =  perso->coordo_perso.x;
  rightc =  perso->coordo_perso.x + perso->pos_perso.w;
  topc =  perso->coordo_perso.y;
  bottomc = perso->coordo_perso.y + perso->pos_perso.h;
 
  leftb = boss->coordo_perso.x;
  rightb = boss->coordo_perso.x + boss->pos_perso.w;
  topb = boss->coordo_perso.y;
  bottomb = boss->coordo_perso.y + boss->pos_perso.h;

  if( bottomb <= topc || topb >= bottomc || leftb >= rightc)
  {
      return 1;
  }
  else
  {
      if(rightb == leftc)
	return 2;
  }
  return 0;
}

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}
