#include "jeu.c"
#include "jeu.h"

int main(void) {
    int nbrJoueur=0;
    player players[7];
    srand(time(NULL));
    jeu(players,nbrJoueur);
    return 0;
}
