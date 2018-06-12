#ifndef HEADER
#define HEADER

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

enum{NOIR, ROUGE, BLEU, VERT, BLANC};//noir = fond ; rouge = liste ouverte ; bleu = liste fermé + point de départ ; vert = objectif ; blanc = mur
enum{DROITE, GAUCHE, HAUT, BAS, AUCUNE};

#define TAILLE_PIXEL   20     //60
#define NB_PIXEL_LARGE 32    //80
#define NB_PIXEL_HAUT  24    //60
#define LARGEUR_ECRAN  TAILLE_PIXEL * NB_PIXEL_LARGE
#define HAUTEUR_ECRAN  TAILLE_PIXEL * NB_PIXEL_HAUT

typedef struct Case Case;
struct Case
{
    int nombre;
    int couleur;
    int direction;
};

#endif // HEADER


