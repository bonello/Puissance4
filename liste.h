
#ifndef LISTE_H
#define LISTE_H

#include "sprite.h"
#include <stdbool.h>

typedef struct sprite_list * sprite_list_t ;

struct sprite_list
{
  sprite_t tete;
  sprite_list_t reste;
};


sprite_list_t sprite_list_new_empty(void);
sprite_list_t cons_liste(sprite_t a, sprite_list_t L);

bool sprite_list_is_empty(sprite_list_t L);
sprite_t sprite_list_head(sprite_list_t L);
void sprite_list_remove(sprite_list_t * L, sprite_t tete);
#endif
