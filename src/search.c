#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "main.h"
#include "search.h"


int balayage_numerique(Case carte[][NB_PIXEL_HAUT], SDL_Surface* ecran)
{
    int i, j;
    int distance = 0, trouver = 0, nbre_cases = 1;

    clear_map(carte);

    while (!trouver && nbre_cases != 0)
    {
        nbre_cases = 0;

        for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
        {
            for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
            {
                if (carte[i][j].nombre == distance)
                {
                    if (i < NB_PIXEL_LARGE && !trouver)
                    {
                        if (carte[i + 1][j].nombre == -1)
                        {
                            carte[i + 1][j].nombre = distance + 1;
                            nbre_cases++;
                        }

                        else if (carte[i + 1][j].couleur == VERT)
                            trouver = 1;
                    }

                    if (i != 0 && !trouver)
                    {
                        if (carte[i -1][j].nombre == -1)
                        {
                            carte[i - 1][j].nombre = distance + 1;
                            nbre_cases++;
                        }

                        else if (carte[i - 1][j].couleur == VERT)
                            trouver = 1;
                    }

                    if (j < NB_PIXEL_HAUT - 1 && !trouver)
                    {
                        if (carte[i][j + 1].nombre == -1)
                        {
                            carte[i][j + 1].nombre = distance + 1;
                            nbre_cases++;
                        }

                        else if (carte[i][j + 1].couleur == VERT)
                            trouver = 1;
                    }

                    if (j != 0 && !trouver)
                    {
                        if (carte[i][j - 1].nombre == -1)
                        {
                            carte[i][j - 1].nombre = distance + 1;
                            nbre_cases++;
                        }

                        else if (carte[i][j - 1].couleur == VERT)
                            trouver = 1;
                    }

                    //afficher_ecran(carte, ecran);
                }
            }
        }
        distance++;
        afficher_ecran(carte, ecran);
    }
    //afficher_ecran(carte, ecran);

    if (trouver)
        return 1;

    else
        return 0;
}


int balayage_fluxs(Case carte[][NB_PIXEL_HAUT], SDL_Surface* ecran)
{
    int i, j;
    int distance = 0, trouver = 0, nbre_cases = 1;

    clear_map(carte);

    while (!trouver && nbre_cases != 0)
    {
        nbre_cases = 0;

        for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
        {
            for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
            {
                if (carte[i][j].nombre == distance)
                {
                    if (i < NB_PIXEL_LARGE && !trouver)
                    {
                        if (carte[i + 1][j].nombre == -1)
                        {
                            carte[i + 1][j].nombre = distance + 1;
                            carte[i + 1][j].direction = GAUCHE;
                            nbre_cases++;
                        }

                        else if (carte[i + 1][j].couleur == VERT)
                        {
                            trouver = 1;
                            carte[i + 1][j].direction = GAUCHE;
                        }
                    }

                    if (i != 0 && !trouver)
                    {
                        if (carte[i - 1][j].nombre == -1)
                        {
                            carte[i - 1][j].nombre = distance + 1;
                            carte[i - 1][j].direction = DROITE;
                            nbre_cases++;
                        }

                        else if (carte[i - 1][j].couleur == VERT)
                        {
                            trouver = 1;
                            carte[i - 1][j].direction = DROITE;
                        }
                    }

                    if (j < NB_PIXEL_HAUT - 1 && !trouver)
                    {
                        if (carte[i][j + 1].nombre == -1)
                        {
                            carte[i][j + 1].nombre = distance + 1;
                            carte[i][j + 1].direction = BAS;
                            nbre_cases++;
                        }

                        else if (carte[i][j + 1].couleur == VERT)
                        {
                            trouver = 1;
                            carte[i][j + 1].direction = BAS;
                        }
                    }

                    if (j != 0 && !trouver)
                    {
                        if (carte[i][j - 1].nombre == -1)
                        {
                            carte[i][j - 1].nombre = distance + 1;
                            carte[i][j - 1].direction = HAUT;
                            nbre_cases++;
                        }

                        else if (carte[i][j - 1].couleur == VERT)
                        {
                            trouver = 1;
                            carte[i][j - 1].direction = HAUT;
                        }
                    }

                    //afficher_ecran(carte, ecran);
                }
            }
        }
        distance++;
        afficher_ecran(carte, ecran);
    }
    if (trouver)
        return 1;

    else
        return 0;
}
