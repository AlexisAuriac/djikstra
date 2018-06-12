#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "main.h"
#include "solve.h"


void resolution_numerique(Case carte[][NB_PIXEL_HAUT], SDL_Surface* ecran)
{
    int i, j;
    int x = 0, y = 0;
    int trouver = 0, numero = NB_PIXEL_LARGE * NB_PIXEL_HAUT, direction = AUCUNE;

    for (i = 0 ; i < NB_PIXEL_LARGE && !trouver ; i++)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT && !trouver ; j++)
        {
            if (carte[i][j].couleur == VERT)
            {
                x = i;
                y = j;
            }
        }
    }

    while (!trouver)
    {
        if (x < NB_PIXEL_LARGE - 1)
        {
            if (carte[x + 1][y].nombre == 0)
                trouver = 1;

            else if (carte[x + 1][y].nombre > 0 && carte[x + 1][y].nombre < numero)
            {
                numero = carte[x + 1][y].nombre;
                direction = DROITE;
            }
        }

        if (x != 0)
        {
            if (carte[x - 1][y].nombre == 0)
                trouver = 1;

            else if (carte[x - 1][y].nombre > 0 && carte[x - 1][y].nombre < numero)
            {
                numero = carte[x - 1][y].nombre;
                direction = GAUCHE;
            }
        }

        if (y < NB_PIXEL_HAUT - 1)
        {
            if (carte[x][y + 1].nombre == 0)
                trouver = 1;

            else if (carte[x][y + 1].nombre > 0 && carte[x][y + 1].nombre < numero)
            {
                numero = carte[x][y + 1].nombre;
                direction = BAS;
            }
        }

        if (y != 0)
        {
            if (carte[x][y - 1].nombre == 0)
                trouver = 1;

            else if (carte[x][y - 1].nombre > 0 && carte[x][y - 1].nombre < numero)
            {
                numero = carte[x][y - 1].nombre;
                direction = HAUT;
            }
        }

        if (carte[x][y].couleur != VERT)
        {
            carte[x][y].couleur = ROUGE;
        }

        switch (direction)
        {
        case DROITE :
            x++;
            break;
        case GAUCHE:
            x--;
            break;
        case BAS :
            y++;
            break;
        case HAUT :
            y--;
            break;
        }

        afficher_ecran(carte, ecran);
    }
}


void resolution_fluxs(Case carte[][NB_PIXEL_HAUT], SDL_Surface* ecran)
{
    int i, j;
    int x = 0, y = 0;
    int trouver = 0;

    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
        {
            if (carte[i][j].couleur == VERT)
            {
                x = i;
                y = j;
            }
        }
    }

    while (!trouver)
    {
        if (carte[x][y].couleur == BLEU)
        {
            trouver = 1;
        }

        else
        {
            if (carte[x][y].couleur != VERT)
            {
                carte[x][y].couleur = ROUGE;
            }

            switch (carte[x][y].direction)
            {
            case DROITE :
                x++;
                break;
            case GAUCHE :
                x--;
                break;
            case BAS :
                y--;
                break;
            case HAUT :
                y++;
                break;
            }
        }

        afficher_ecran(carte, ecran);
    }
}

