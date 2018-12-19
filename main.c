#include "math.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "SDL.h"
#include "liste.h"
#include "sprite.h"
#include "SDL_ttf.h" 


/* MAIN */
int main(int argc, char* argv[])
{
  /* INITIALISATION DES VARAIBLES */
  SDL_Surface *fenetre, *fond, *temp = NULL, *temp1 = NULL;
  SDL_Event event;
  SDL_Rect rcBackground;
  int colorkey, i, j, gameover;
  int niveau = 1;
  float angle;
  sprite_list_t liste_serpent= NULL, liste_serpent1= NULL;
  sprite_t heros = NULL;
  sprite_t serpent, serpent1;
  bool test = NULL, test5 = false, test6 = false, test7 = false, test8 = false, test9 = false;
  SDL_Color couleurBlanc = {255, 255, 255, 255};
  float taille_heros_x = 32.25;

  unsigned int coll_bulle = 0;
  unsigned int coll_petit = 0;
  unsigned int coll_kaa = 0;
  unsigned int vie_du_boss = 0;
  
  /* INITIALISATION FICHIER DE SAUVEGARDE*/
  FILE* fichier = NULL;
  fichier = fopen("niveau.txt","a+"); /* "a+" --> ajout en lecture / écriture à la fin du fichier.
					Si le fichier n'existe pas, il sera créé.*/

					
  /* INITIALISATION SDL */
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  TTF_Font *police = TTF_OpenFont("Images/flic.ttf",300);
  SDL_Surface *texte1 = TTF_RenderText_Solid(police,"GAMEOVER",couleurBlanc);
  SDL_Surface *texte2 = TTF_RenderText_Solid(police,"YOU WON",couleurBlanc);
  SDL_Surface *menu = TTF_RenderText_Solid(police,"Appuyer P pour Jouer",couleurBlanc);

  /* BARRE DE TITRE */
  SDL_WM_SetCaption("Snake", "Snake");
  
  /* CREATION DE LA FENETRE */
  fenetre = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /* set keyboard repeat */
  SDL_EnableKeyRepeat(5, 5);
  
  /* CHARGEMENT ARRIERE PLAN */
  temp  = SDL_LoadBMP(BACKGROUND);
  fond = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  /* CHARGEMENT DU PERSONNAGE */
  heros = new_sprite(PERSONNAGE1, fenetre);
  sprite_t  p2 = new_sprite(PERSONNAGE2, fenetre);
  sprite_t  p3 = new_sprite(PERSONNAGE3, fenetre);
  sprite_t  p4 = new_sprite(PERSONNAGE4, fenetre);
  sprite_t  p5 = new_sprite(PERSONNAGE5, fenetre);

  /* CHARGEMENT DE LA BULLE */
  char fname1[1024];
  sprintf(fname1, BULLE);
  sprite_t bulle = new_sprite(fname1, fenetre);
  bulle->angle = 0;
  bulle->coordo_perso.x = 50;
  bulle->coordo_perso.y = SCREEN_HEIGHT;
  bulle->x = bulle->coordo_perso.x;
  bulle->y = bulle->coordo_perso.y;
  bulle->pos_perso.x = 0;
  bulle->pos_perso.y = 0;
  bulle->pos_perso.w = 40;
  bulle->pos_perso.h = 43;
  
  
  /* CHARGEMENT PETIT SERPENT */
  char fname5[1024];
  sprintf(fname5, PETIT);
  sprite_t petit = new_sprite(fname5, fenetre);
  
  petit->angle = 0;
 
  petit->coordo_perso.x = (rand()%SCREEN_WIDTH) ;
  petit->coordo_perso.y = (rand()%SCREEN_HEIGHT);
  
  petit->x = petit->coordo_perso.x;
  petit->y = petit->coordo_perso.y;
  
  petit->pos_perso.x = 0;
  petit->pos_perso.y = 0;
  petit->pos_perso.w = 40;
  petit->pos_perso.h = 30;
  
  
  /* CHARGEMENT DE SERPENT 2 */
  char fname6[1024];
  sprintf(fname6, KAA);
  sprite_t kaa = new_sprite(fname6, fenetre);
  
  kaa->angle = 0;
  
  kaa->coordo_perso.x = (rand()%SCREEN_WIDTH) ;
  kaa->coordo_perso.y = (rand()%SCREEN_HEIGHT);
  
  kaa->x = kaa->coordo_perso.x;
  kaa->y = kaa->coordo_perso.y;
  
  kaa->pos_perso.x = 0;
  kaa->pos_perso.y = 0;
  kaa->pos_perso.w = 80;
  kaa->pos_perso.h = 80;
  
  
  /* CHARGEMENT DES SERPENTS */
  for (i = 0 ; i < 3 ; i++)
    {
      char fname3[1024];
      sprintf(fname3, SERPENT);
      sprite_t serpent = new_sprite(fname3, fenetre);
      
      serpent->angle = 180;
      
      serpent->coordo_perso.x = rand_a_b(0,1200) ;
      serpent->coordo_perso.y = rand_a_b(0,900);
      
      serpent->x = serpent->coordo_perso.x;
      serpent->y = serpent->coordo_perso.y;
      
      serpent->pos_perso.x = 0;
      serpent->pos_perso.y = 0;
      serpent->pos_perso.w = 168;
      serpent->pos_perso.h = 142;
      
      liste_serpent = cons_liste(serpent, liste_serpent);
    }
  
  /* CHARGEMENT DES SERPENTS 1 */
  for (i = 0 ; i < 2 ; i++)
  {
      char fname4[1024];
      sprintf(fname4, SERPENT1);
      sprite_t serpent1 = new_sprite(fname4, fenetre);
      
      serpent1->angle = 0;
      
      serpent1->coordo_perso.x = rand_a_b(0,1200) ;
      serpent1->coordo_perso.y = rand_a_b(200,500);
      
      serpent1->x = serpent1->coordo_perso.x;
      serpent1->y = serpent1->coordo_perso.y;
      
      serpent1->pos_perso.x = 0;
      serpent1->pos_perso.y = 0;
      serpent1->pos_perso.w = 150;
      serpent1->pos_perso.h = 134;
      
      liste_serpent1 = cons_liste(serpent1, liste_serpent1);
  }

  /* CHARGEMENT DU BOSS */
  char fname7[1024];
  sprintf(fname7, BOSS);
  sprite_t boss = new_sprite(fname7, fenetre);
  boss->angle = 0;
  boss->coordo_perso.x = 50;
  boss->coordo_perso.y = SCREEN_HEIGHT;
  boss->x = bulle->coordo_perso.x;
  boss->y = bulle->coordo_perso.y;
  boss->pos_perso.x = 0;
  boss->pos_perso.y = 0;
  boss->pos_perso.w = 450;
  boss->pos_perso.h = 450;
  
  int menu1 = 1;
  gameover = 0;
  int fini = 0;
  int victoire = 0;

  while (!gameover)
    { 
      void HandleEvent(SDL_Event event)
      {
      /* QUITTER LE JEU AVEC LE CLAVIER */
	switch (event.key.keysym.sym) 
	  {
	  case SDLK_ESCAPE:
	  case SDLK_q:
	    gameover = 1;
	    break;
	  }
	
	Uint8 *move = SDL_GetKeyState(NULL);
	
	if (move[SDLK_LEFT])
	  {   
	    heros->pos_perso.x = 0;
	    heros->coordo_perso.x = heros->coordo_perso.x - 15;
	  }
	if (move[SDLK_RIGHT])
	  {
	    heros->pos_perso.x = (taille_heros_x);
	    heros->coordo_perso.x = heros->coordo_perso.x + 15;
	  }
	if (move[SDLK_UP]) 
	  {
	    heros->coordo_perso.y = heros->coordo_perso.y  - 15;
	  }
	if (move[SDLK_DOWN])
	  {
	    heros->coordo_perso.y = heros->coordo_perso.y + 15;
	  }
      }
      
      
      if (SDL_PollEvent(&event))
	{
	  HandleEvent(event);
	}
      
      /* DESSINER ARRIERE PLAN */
      SDL_BlitSurface(fond, NULL, fenetre, NULL);
      
      /* DESSINER LE PERSONNAGE PRINCIPAL */
      SDL_BlitSurface(heros->bmp, &heros->pos_perso, fenetre, &heros->coordo_perso);
      
      /* CHUTE DU PERSONNAGE */
      heros->coordo_perso.y = heros->coordo_perso.y + 1;
      
      
      /* COLLISION PERSONNAGE AVEC L'ÉCRAN */ 
      if (heros->coordo_perso.x < 0)
	heros->coordo_perso.x = heros->coordo_perso.x;
      
      if (heros->coordo_perso.x >=  SCREEN_WIDTH - TAILLE_HEROS_X)
	heros->coordo_perso.x = SCREEN_WIDTH - TAILLE_HEROS_X;
      
      if (heros->coordo_perso.y < 0)
	heros->coordo_perso.y= heros->coordo_perso.y;
      
      if (heros->coordo_perso.y >= SCREEN_HEIGHT - TAILLE_HEROS_Y)
	heros->coordo_perso.y = SCREEN_HEIGHT - TAILLE_HEROS_Y;
      
      
      /* DESSINER LA BULLE */ 
      if(!coll_bulle)
	{
	  SDL_BlitSurface(bulle->bmp, &bulle->pos_perso, fenetre, &bulle->coordo_perso);
	  bulle->coordo_perso.y = bulle->coordo_perso.y - 5;
	  if (bulle->coordo_perso.y < 0)
	    bulle->coordo_perso.y= SCREEN_HEIGHT - 43;
	  if (bulle->coordo_perso.y > SCREEN_HEIGHT - 43) 
	    bulle->coordo_perso.y = 0;
	}
      
      /* DESSINER LE PETIT SNAKE */
      if(!coll_petit)
	{
	  SDL_BlitSurface(petit->bmp, &petit->pos_perso, fenetre, &petit->coordo_perso);
	  petit->coordo_perso.x = petit->coordo_perso.x + 8*cos(petit->angle);
	  petit->coordo_perso.y = petit->coordo_perso.y + 8*cos(petit->angle);
	  
	  if (petit->coordo_perso.y < 0)
	    petit->coordo_perso.y= SCREEN_HEIGHT - 30;
	  if (petit->coordo_perso.y > SCREEN_HEIGHT - 30) 
	    petit->coordo_perso.y = 0;
	  if (petit->coordo_perso.x < 0)
	    petit->coordo_perso.x= SCREEN_WIDTH - 40;
	  if (petit->coordo_perso.x > SCREEN_WIDTH - 40) 
	    petit->coordo_perso.x = 0;
	}
      
      /* DESSINER SERPENT 2 */
      if(!coll_kaa)
	{
	  SDL_BlitSurface(kaa->bmp, &kaa->pos_perso, fenetre, &kaa->coordo_perso);
	  kaa->coordo_perso.x = kaa->coordo_perso.x - 2*cos(kaa->angle);
	  kaa->coordo_perso.y = kaa->coordo_perso.y - 2*cos(kaa->angle);
	  
	  if (kaa->coordo_perso.y < 0)
	    kaa->coordo_perso.y= SCREEN_HEIGHT - 80;
	  if (kaa->coordo_perso.y > SCREEN_HEIGHT - 80) 
	    kaa->coordo_perso.y = 0;
	  if (kaa->coordo_perso.x < 0)
	    kaa->coordo_perso.x= SCREEN_WIDTH - 80;
	  if (kaa->coordo_perso.x > SCREEN_WIDTH - 80) 
	    kaa->coordo_perso.x = 0;
	}
	
      
      /* DESSINER LA LISTE DES SERPENTS */
      sprite_list_t tmp_liste_serpent = liste_serpent;
      while (tmp_liste_serpent != NULL)
	{
	  tmp_liste_serpent->tete->x = tmp_liste_serpent->tete->x  + 9*cos(tmp_liste_serpent->tete->angle);
	  tmp_liste_serpent->tete->y = tmp_liste_serpent->tete->y + 0*cos(tmp_liste_serpent->tete->angle);
	  
	  tmp_liste_serpent->tete->coordo_perso.x = (int)tmp_liste_serpent->tete->x;
	  tmp_liste_serpent->tete->coordo_perso.y = (int)tmp_liste_serpent->tete->y;
	  SDL_BlitSurface(tmp_liste_serpent->tete->bmp, &(tmp_liste_serpent->tete->pos_perso), fenetre, &(tmp_liste_serpent->tete->coordo_perso));
	  
	  /* COLLISION DES SERPENTS AVEC LES COTÉS DE L'ÉCRAN */
	  
	  if (tmp_liste_serpent->tete->x > SCREEN_WIDTH - 168)
	    tmp_liste_serpent->tete->x = 0;
	  
	  if (tmp_liste_serpent->tete->x < 0)
	    tmp_liste_serpent->tete->x = SCREEN_WIDTH - 168;
	  
	  if (tmp_liste_serpent->tete->y > SCREEN_HEIGHT - 142)
	    tmp_liste_serpent->tete->y = 0;
	  
	  if (tmp_liste_serpent->tete->y < 0)
	    tmp_liste_serpent->tete->y = SCREEN_HEIGHT - 142;
	  
	  tmp_liste_serpent = tmp_liste_serpent->reste;
	}
      
      
      /* DESSINER LA LISTE DES SERPENTS 1 */
      sprite_list_t tmp_liste_serpent1 = liste_serpent1;
      while (tmp_liste_serpent1 != NULL)
	{
	  tmp_liste_serpent1->tete->x = tmp_liste_serpent1->tete->x  + 7*cos(tmp_liste_serpent1->tete->angle);
	  tmp_liste_serpent1->tete->y = tmp_liste_serpent1->tete->y + 0*cos(tmp_liste_serpent1->tete->angle);
	  
	  tmp_liste_serpent1->tete->coordo_perso.x = (int)tmp_liste_serpent1->tete->x;
	  tmp_liste_serpent1->tete->coordo_perso.y = (int)tmp_liste_serpent1->tete->y;
	  SDL_BlitSurface(tmp_liste_serpent1->tete->bmp, &(tmp_liste_serpent1->tete->pos_perso), fenetre, &(tmp_liste_serpent1->tete->coordo_perso));
	  
	  /* COLLISION DES SERPENTS 1 AVEC LES COTÉS DE L'ÉCRAN */
	  
	  if (tmp_liste_serpent1->tete->x > SCREEN_WIDTH - 150)
	    tmp_liste_serpent1->tete->x = 0;
	  
	  if (tmp_liste_serpent1->tete->x < 0)
	    tmp_liste_serpent1->tete->x = SCREEN_WIDTH - 150;
	  
	  if (tmp_liste_serpent1->tete->y > SCREEN_HEIGHT - 134)
	    tmp_liste_serpent1->tete->y = 0;
	  
	  if (tmp_liste_serpent1->tete->y < 0)
	    tmp_liste_serpent1->tete->y = SCREEN_HEIGHT - 134;
	  
	  tmp_liste_serpent1 = tmp_liste_serpent1->reste;
	}
           
      
      /*  COLLISION DE LA BULLE AVEC LE PERSONNAGE */
      if(collision(heros,bulle))
	{
	  free_sprite(bulle);
	  coll_bulle = 1;
	  heros = p2;
	  taille_heros_x = 62.4;
	  niveau = 1;
	  printf("Niveau : %u \n",niveau);
	  test5 = true;
	}  
      
      /* COLLISION DU PETIT SNAKE AVEC LE PERSONNAGE PRINCIPAL */
   
      if(!test6 && test5 && collision(heros,petit))
	{
	  free_sprite(petit);
	  coll_petit = 1;
	  heros = p3;
	  taille_heros_x = 93.75;
	  niveau = 2;
	  printf("Niveau : %u \n",niveau);
	  test6 = true;
	}
	
      /* COLLISION DE SERPENT 2 (KAA) AVEC LE PERSONNAGE PRINCIPAL */

      if(!test7 && test6 && collision(heros,kaa))
	{
	  free_sprite(kaa);
	  coll_kaa = 1;
	  heros = p4;
	  taille_heros_x = 125;
	  niveau = 3;
	  printf("Niveau : %u \n",niveau);
	  test7 = true;
	}
      else{
	if (collision(heros, kaa))
	  {
	    printf("GAME OVER\n");
	    fini = 1;
	    free_sprite(heros);
	    fprintf(fichier, "Vous avez échoué au niveau : %d ", niveau);
	  }
      }
      
    
      /* COLLISION DES SERPENTS AVEC LE PERSONNAGE PRINCIPAL */
      sprite_list_t tmp_liste_de_serpent = liste_serpent;
      while (tmp_liste_de_serpent != NULL) 
	{
	  if (!test7)
	    {
	      if (collision(heros,tmp_liste_de_serpent->tete))
		{
		  printf("GAMEOVER\n");
		  fini = 1;
		  free_sprite(heros);
		  fprintf(fichier, "Vous avez échoué au niveau : %d \n", niveau);
		}
	      tmp_liste_de_serpent = tmp_liste_de_serpent->reste;
	    }
	
	  else{
	    if (collision(heros,tmp_liste_de_serpent->tete))
	      {
		sprite_list_remove(&liste_serpent, tmp_liste_de_serpent->tete);
		niveau = niveau+1;
		printf("Niveau : %d\n",niveau);
	      }
	    tmp_liste_de_serpent = tmp_liste_de_serpent->reste; 
	  }
	}
    

      /* COLLISION DES SERPENTS 1 AVEC LE PERSONNAGE PRINCIPAL */
      sprite_list_t tmp_liste_de_serpent1 = liste_serpent1;
      while (tmp_liste_de_serpent1 != NULL) 
	{
	  if (!test7)
	    {
	      if (collision(heros,tmp_liste_de_serpent1->tete)) 
		{
		  printf("GAMEOVER\n");
		  fini = 1;
		  free_sprite(heros);
		  fprintf(fichier, "Vous avez échoué au niveau : %d \n", niveau);
		}
	      tmp_liste_de_serpent1 = tmp_liste_de_serpent1->reste;
	    }
	  else{
	    if (collision(heros,tmp_liste_de_serpent1->tete))
	      {
		sprite_list_remove(&liste_serpent1, tmp_liste_de_serpent1->tete);
		niveau = niveau + 1;
		printf("Niveau : %d\n",niveau);
	      }
	    tmp_liste_de_serpent1 = tmp_liste_de_serpent1->reste; 
	  }
	}
      
      /* BOSS DE FIN */
      if (niveau == 8)
	{
	  heros = p5;
	  taille_heros_x = 156.25;
	  SDL_BlitSurface(boss->bmp, &boss->pos_perso, fenetre, &boss->coordo_perso);
	  boss->coordo_perso.x = boss->coordo_perso.x - 2*cos(boss->angle);
	  boss->coordo_perso.y = boss->coordo_perso.y - 2*cos(boss->angle);
	    
	  if (boss->coordo_perso.y < 0)
	    boss->coordo_perso.y= SCREEN_HEIGHT - 80;
	  if (boss->coordo_perso.y > SCREEN_HEIGHT - 80) 
	    boss->coordo_perso.y = 0;
	  if (boss->coordo_perso.x < 0)
	    boss->coordo_perso.x= SCREEN_WIDTH - 80;
	  if (boss->coordo_perso.x > SCREEN_WIDTH - 80) 
	    boss->coordo_perso.x = 0;
	 
	  /* COLLISION ENTRE LE BOSS ET LE HEROS */
	  if (collision(heros,boss))
	    {
	      free_sprite(boss);
	      victoire = 1;
	      printf("Bravo ! Vous avez gagné ! \n");
	    }          
	}

      /* SI LE JOUEUR A GAGNÉ*/
      if (victoire)
	{
	  SDL_Rect pos_texte2;
	  pos_texte2.x = 100;
	  pos_texte2.y= SCREEN_HEIGHT / 2;
	  SDL_BlitSurface(texte2,NULL,fenetre,&pos_texte2);
	  fprintf(fichier, "Vous avez fini le jeu !! BRAVO !\n");
	}
      
      /* SI LE JEU EST FINI*/
      if (fini)
      {
	  SDL_Rect pos_texte1;
	  pos_texte1.x = 100;
	  pos_texte1.y= SCREEN_HEIGHT /2;
	  SDL_BlitSurface(texte1,NULL,fenetre,&pos_texte1);
      }
      
      /* ACTUALISER LA FENETRE */
      SDL_UpdateRect(fenetre, 0, 0, 0, 0);
      SDL_Delay(25);
    }
    
    /* CLEAN UP */
    SDL_FreeSurface(fond);
    TTF_Quit();
    SDL_Quit();
    fclose(fichier); // Fermeture du fichier
    return 0;
}
