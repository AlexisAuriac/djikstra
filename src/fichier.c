#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "main.h"
#include "fichier.h"
#include "fonctions.h"


int charger_carte(Case carte[][NB_PIXEL_HAUT])
{
    int i, j;

    FILE *fichier = NULL;

    fichier = fopen("assets/carte.txt", "r");

    if (fichier == NULL)
        return 0;

    else if (!test_carte(fichier))
    {
        fclose(fichier);
        clear_map(carte);
        return 0;
    }

    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
        {
            carte[i][j].direction = AUCUNE;

            switch (fgetc(fichier))
            {
            case '0' :
                carte[i][j].couleur = NOIR;
                carte[i][j].nombre = -1;
                break;
            case '1' :
                carte[i][j].couleur = ROUGE;
                break;
            case '2' :
                carte[i][j].couleur = BLEU;
                carte[i][j].nombre = 0;
                break;
            case '3' :
                carte[i][j].couleur = VERT;
                carte[i][j].nombre = -2;
                break;
            case '4' :
                carte[i][j].couleur = BLANC;
                carte[i][j].nombre = -3;
                break;
            }
        }
    }

    fclose(fichier);
    return 1;
}


int sauvegarder_carte(Case carte[][NB_PIXEL_HAUT])
{
    int i, j;

    FILE *fichier = NULL;

    fichier = fopen("assets/carte.txt", "w+");

    if (fichier == NULL)
    {
        return 0;
    }

    for (i = 0 ; i < NB_PIXEL_LARGE ; i++)
    {
        for (j = 0 ; j < NB_PIXEL_HAUT ; j++)
        {
            if (carte[i][j].couleur == ROUGE)
                fprintf(fichier, "%d", NOIR);

            else
                fprintf(fichier, "%d", carte[i][j].couleur);
        }
    }

    fclose(fichier);
    return 1;
}


int test_carte(FILE* fichier)
{
    int i, j;
    int nbre_caractere = 0;

    while (getc(fichier) != EOF)
        nbre_caractere++;

    rewind(fichier);

    if (nbre_caractere != NB_PIXEL_LARGE * NB_PIXEL_HAUT)
        return 0;

    for (i = 0 ; i < nbre_caractere ; i++)
    {
        j = fgetc(fichier);

        if (j - '0' < 0 || j - '0' > 4)
            return 0;
    }

    rewind(fichier);

    return 1;
}
