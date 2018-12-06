#include "liste.h"
#include "sprite.h"

sprite_list_t sprite_list_new_empty(void)
{
  return NULL;
}


sprite_list_t cons_liste (sprite_t a, sprite_list_t L)
{
  sprite_list_t new_list = sprite_list_new_empty();
  new_list = (sprite_list_t) malloc(sizeof(struct sprite_list));
  new_list->tete = a;
  new_list->reste = L;
  return new_list;

}


bool sprite_list_is_empty(sprite_list_t L)
{
 return (L == NULL) ;
}


sprite_t sprite_list_head(sprite_list_t L)
{
   if (sprite_list_is_empty(L)) 
     {	
    return NULL ;
     }	
   else
     {
    return L->tete ;	
     }

}

void sprite_list_remove(sprite_list_t* L, sprite_t tete)
{
 if (*L == NULL)
    {
      printf("*** ERREUR, appel de sprite_list_pop sur une liste vide ***\n");
      return;
    }
  sprite_list_t tmp = *L;
  if (tmp->tete == tete) {
    free(tete);
    *L = (*L)->reste;
    return;
  }
  else { 
    while (tmp != NULL && tmp->reste != NULL) {
      if (tmp->reste->tete == tete) {
	free(tete);
	tmp->reste = tmp->reste->reste;
      }
      tmp = tmp->reste;
    } 
  }
}


