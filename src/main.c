/*
Etat : priorité :
       important :
       mineur : optimisation des performances
                menu(s) -> rappel des touches
                           ?boutons à cliquer (quitter, charger, sauvegarder, etc...)
                           sauvegarde de plusieurs niveaux -> chargement + chargement rapide
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "main.h"
#include "fonctions.h"
#include "fichier.h"
#include "search.h"
#include "solve.h"


int main(int argc, char** argv)
{
    remove("erreur.txt");
    SDL_ShowCursor(SDL_DISABLE);

    int continuer = 1, clicGaucheEnfonce = 0, clicDroitEnfonce = 0, couleur_actuelle = BLANC;
    int i, j;
    Case carte[NB_PIXEL_LARGE][NB_PIXEL_HAUT];

    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
        {
            carte[i][j].nombre = -1;
            carte[i][j].couleur = NOIR;
        }
    }

    SDL_Rect position;
    SDL_Surface *ecran = NULL, *selection = NULL;//, *curseur[5] = {NULL};
    SDL_Event event;

    selection = SDL_LoadBMP("assets/selection.bmp");
    /*curseur[BLANC] = SDL_LoadBMP("assets/curseur_blanc.bmp");
    curseur[BLEU] = SDL_LoadBMP("assets/curseur_bleu.bmp");
    curseur[VERT] = SDL_LoadBMP("assets/curseur_vert.bmp");*/

    if (selection == NULL)
        erreur("Selection n'a pas pu etre ouverte\n");

    if(!charger_carte(carte))
        erreur("La carte par défaut n'a put être ouverte\n");

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE);

    SDL_SetColorKey(selection, SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 255, 255));
    /*SDL_SetColorKey(curseur[BLANC], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 0, 0));
    SDL_SetColorKey(curseur[BLEU], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 0, 0));
    SDL_SetColorKey(curseur[VERT], SDL_SRCCOLORKEY, SDL_MapRGB(ecran->format, 255, 0, 0));*/

    //SDL_ShowCursor(SDL_DISABLE);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT :
            continuer = 0;
            break;
        case SDL_KEYDOWN :
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE :
                continuer = 0;
                break;
            case SDLK_SPACE :
                clear_map(carte);
                break;
            case SDLK_c :
                charger_carte(carte);
                break;
            case SDLK_s :
                sauvegarder_carte(carte);
                break;
            case SDLK_w :
                couleur_actuelle = BLANC;
                break;
            case SDLK_b :
                couleur_actuelle = BLEU;
                break;
            case SDLK_g :
                couleur_actuelle = VERT;
                break;
            case SDLK_a :
                if (balayage_numerique(carte, ecran))
                    resolution_numerique(carte, ecran);
                break;
            case SDLK_z :
                if (balayage_fluxs(carte, ecran))
                    resolution_fluxs(carte, ecran);
                break;
            default :
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN :
            clear_map(carte);
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (couleur_actuelle == BLEU)
                {
                    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
                    {
                        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
                        {
                            if (carte[i][j].couleur == couleur_actuelle)
                            {
                                carte[i][j].couleur = NOIR;
                                carte[i][j].nombre = -1;
                            }
                        }
                    }
                    carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].nombre = 0;
                }

                else if (couleur_actuelle == VERT)
                {
                    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
                    {
                        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
                        {
                            if (carte[i][j].couleur == couleur_actuelle)
                            {
                                carte[i][j].couleur = NOIR;
                                carte[i][j].nombre = -1;
                            }
                        }
                    }
                }

                else//BLANC
                {
                    carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].nombre = -3;
                }

                carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].couleur = couleur_actuelle;
                clicGaucheEnfonce = 1;
            }

            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                carte[event.button.x / TAILLE_PIXEL][event.button.y / TAILLE_PIXEL].couleur = NOIR;
                carte[event.button.x / TAILLE_PIXEL][event.button.y / TAILLE_PIXEL].nombre = -1;
                clicDroitEnfonce = 1;
            }
            break;
        case SDL_MOUSEBUTTONUP :
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                clicGaucheEnfonce = 0;
            }

            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                clicDroitEnfonce = 0;
            }
            break;
        case SDL_MOUSEMOTION :
            if (clicGaucheEnfonce)
            {
                if (couleur_actuelle == BLEU)
                {
                    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
                    {
                        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
                        {
                            if (carte[i][j].couleur == couleur_actuelle)
                            {
                                carte[i][j].couleur = NOIR;
                                carte[i][j].nombre = -1;
                            }
                        }
                    }

                    carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].nombre = 0;
                }

                else if (couleur_actuelle == VERT)
                {
                    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
                    {
                        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
                        {
                            if (carte[i][j].couleur == couleur_actuelle)
                            {
                                carte[i][j].couleur = NOIR;
                            }
                        }
                    }
                }

                else//BLANC
                {
                    carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].nombre = -3;
                }

                carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].couleur = couleur_actuelle;
            }

            else if (clicDroitEnfonce)
            {
                carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].couleur = NOIR;
                carte[event.motion.x / TAILLE_PIXEL][event.motion.y / TAILLE_PIXEL].nombre = -1;
            }
            break;
        }
        afficher_ecran(carte, ecran);

        position.x = event.motion.x / TAILLE_PIXEL * TAILLE_PIXEL;
        position.y = event.motion.y / TAILLE_PIXEL * TAILLE_PIXEL;
        SDL_BlitSurface(selection, NULL, ecran, &position);
        /*position.x = event.motion.x;
        position.y = event.motion.y;

        switch (couleur_actuelle)
        {
        case BLEU :
            SDL_BlitSurface(curseur[BLEU], NULL, ecran, &position);
            break;
        case VERT :
            SDL_BlitSurface(curseur[VERT], NULL, ecran, &position);
            break;
        default :
            SDL_BlitSurface(curseur[BLANC], NULL, ecran, &position);
            break;
        }*/

        SDL_Flip(ecran);
    }

    SDL_ShowCursor(SDL_ENABLE);

    SDL_FreeSurface(selection);
    /*for (i = 0 ; i < 5 ; i++)
        SDL_FreeSurface(curseur[i]);*/
    SDL_Quit();

    return EXIT_SUCCESS;
}
