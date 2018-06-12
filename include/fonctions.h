#ifndef FONCTIONS
#define FONCTIONS

void afficher_ecran(Case carte[][NB_PIXEL_HAUT], SDL_Surface *ecran);
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void erreur(char *chaine);
void clear_map(Case carte[NB_PIXEL_LARGE][NB_PIXEL_HAUT]);

#endif // FONCTIONS
