#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
//#include <SDL/SDL_rotozoom.h>

#include "main.h"
#include "fonctions.h"


void afficher_ecran(Case carte[][NB_PIXEL_HAUT], SDL_Surface *ecran)
{
    int i, j, k, l;
    double zoom = 0.19;
    char chaine[5]  = "";
    SDL_Surface *rect = NULL, *fleche = NULL, *flecheR = NULL, *fleches_rot[4] = {NULL}, *flechesR_rot[4] = {NULL};
    SDL_Rect position;

    TTF_Font *police = NULL;
    SDL_Color noir = {0, 0, 0}, blanc = {255, 255, 255};

    /*fleche = SDL_LoadBMP("images/fleche.bmp");
    fleches_rot[DROITE] = rotozoomSurface(fleche, 270, zoom, 1);
    fleches_rot[GAUCHE] = rotozoomSurface(fleche, 90, zoom, 1);
    fleches_rot[HAUT] = rotozoomSurface(fleche, 180, zoom, 1);
    fleches_rot[BAS] = rotozoomSurface(fleche, 0, zoom, 1);

    fleche = SDL_LoadBMP("images/fleche_rouge.bmp");
    flechesR_rot[DROITE] = rotozoomSurface(fleche, 270, zoom, 1);
    flechesR_rot[GAUCHE] = rotozoomSurface(fleche, 90, zoom, 1);
    flechesR_rot[HAUT] = rotozoomSurface(fleche, 180, zoom, 1);
    flechesR_rot[BAS] = rotozoomSurface(fleche, 0, zoom, 1);*/

    TTF_Init();
    police = TTF_OpenFont("assets/prototype.ttf", TAILLE_PIXEL / 2);

    if (police == NULL)
    {
        erreur("Le fichier police n'a pas pu être trouvé\n");
    }

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    for (i = 0 ; i < NB_PIXEL_LARGE ; ++i)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT ; ++j)
        {
            SDL_LockSurface(ecran);

            switch (carte[i][j].couleur)
            {
            case ROUGE :
                for (k = 0 ; k < TAILLE_PIXEL ; ++k)
                {
                    for (l = 0 ; l < TAILLE_PIXEL ; ++l)
                        set_pixel(ecran, i * TAILLE_PIXEL + k, j * TAILLE_PIXEL + l, SDL_MapRGB(ecran->format, 255, 0, 0));
                }
                break;
            case BLEU :
                for (k = 0 ; k < TAILLE_PIXEL ; ++k)
                {
                    for (l = 0 ; l < TAILLE_PIXEL ; ++l)
                        set_pixel(ecran, i * TAILLE_PIXEL + k, j * TAILLE_PIXEL + l, SDL_MapRGB(ecran->format, 0, 0, 255));
                }
                break;
            case VERT :
                for (k = 0 ; k < TAILLE_PIXEL ; ++k)
                {
                    for (l = 0 ; l < TAILLE_PIXEL ; ++l)
                        set_pixel(ecran, i * TAILLE_PIXEL + k, j * TAILLE_PIXEL + l, SDL_MapRGB(ecran->format, 0, 255, 0));
                }
                break;
            case BLANC :
                for (k = 0 ; k < TAILLE_PIXEL ; ++k)
                {
                    for (l = 0 ; l < TAILLE_PIXEL ; ++l)
                        set_pixel(ecran, i * TAILLE_PIXEL + k, j * TAILLE_PIXEL + l, SDL_MapRGB(ecran->format, 255, 255, 255));
                }
                break;
            }
            SDL_UnlockSurface(ecran);

            position.x = i * TAILLE_PIXEL;
            position.y = j * TAILLE_PIXEL;

            if (carte[i][j].nombre >= 0 && carte[i][j].direction == AUCUNE)
            {
                sprintf(chaine, "%d", carte[i][j].nombre);

                if (carte[i][j].couleur == NOIR)
                    rect = TTF_RenderText_Blended(police, chaine,blanc);

                else
                    rect = TTF_RenderText_Blended(police, chaine, noir);

                SDL_BlitSurface(rect, NULL, ecran, &position);
                SDL_FreeSurface(rect);
            }

            if (carte[i][j].couleur != VERT)
            {
                switch (carte[i][j].direction)
                {
                case DROITE :
                    if (carte[i][j].couleur == ROUGE)
                        SDL_BlitSurface(flechesR_rot[DROITE], NULL, ecran, &position);

                    else
                        SDL_BlitSurface(fleches_rot[DROITE], NULL, ecran, &position);
                    break;
                case GAUCHE :
                    if (carte[i][j].couleur == ROUGE)
                        SDL_BlitSurface(flechesR_rot[GAUCHE], NULL, ecran, &position);

                    else
                        SDL_BlitSurface(fleches_rot[GAUCHE], NULL, ecran, &position);
                    break;
                case HAUT :
                    if (carte[i][j].couleur == ROUGE)
                        SDL_BlitSurface(flechesR_rot[HAUT], NULL, ecran, &position);

                    else
                        SDL_BlitSurface(fleches_rot[HAUT], NULL, ecran, &position);
                    break;
                case BAS :
                    if (carte[i][j].couleur == ROUGE)
                        SDL_BlitSurface(flechesR_rot[BAS], NULL, ecran, &position);

                    else
                        SDL_BlitSurface(fleches_rot[BAS], NULL, ecran, &position);
                    break;
                }
            }
        }
    }

    SDL_Flip(ecran);

    /*SDL_FreeSurface(fleche);
    SDL_FreeSurface(flecheR);
    for (i = 0 ; i < 4 ; i++)
    {
        SDL_FreeSurface(fleches_rot[i]);
        SDL_FreeSurface(flechesR_rot[i]);
	}*/
    TTF_CloseFont(police);

    TTF_Quit();
}


void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


void erreur(char *chaine)
{
    FILE *fichier = NULL;

    fichier = fopen("erreur.txt", "a");
    fputs(chaine, fichier);

    fclose(fichier);
}


void clear_map(Case carte[NB_PIXEL_LARGE][NB_PIXEL_HAUT])
{
    int i, j;

    for (i = 0 ; i < NB_PIXEL_LARGE ; ++i)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT ; ++j)
        {
            carte[i][j].direction = AUCUNE;

            switch (carte[i][j].couleur)
            {
            case NOIR :
                carte[i][j].nombre = -1;
                break;
            case ROUGE :
                carte[i][j].couleur = NOIR;
                carte[i][j].nombre = -1;
                break;
            case BLEU :
                carte[i][j].nombre = 0;
                break;
            case VERT :
                carte[i][j].nombre = -2;
                break;
            case BLANC :
                carte[i][j].nombre = -3;
                break;
            }
        }
    }
}


