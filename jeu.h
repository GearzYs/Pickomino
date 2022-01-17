//Structure définissant les joueurs.
struct player;

//Fonction permmettant l'affichage des dés.
void afficheurDee(int values[],short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],short nombredee,struct player players[],short nbrJoueur,short id);

//Fonction permettant le prise des Dominos.
void priseDomino(int dominos[][2],int total,int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id);

//Fonction permettant de vider le buffer.
void buffer(FILE *c);

//Fonction permettant l'affichage des dominos.
void afficheurPlateau(int dominos[][2]);

//Fonction permettant de faire la somme des dés.
void somme(int listeChoixJoueur[],short compteurchoix,int coefChoixJoueur[],int dominos[][2],int values[],short nombredee,struct player players[],short nbrJoueur,short id);

//Fonction qui demande au joueur si il veut continuer ou non de lancer les dés.
void askContinue(int listeChoixJoueur[],short compteurchoix,int coefChoixJoueur[],int dominos[][2],int values[],short nombredee,struct player players[],short nbrJoueur,short id);

//Fonction permettant la prise des dés lancé en fonction du choix du joueur.
void priseDes(int choixDuJoueur,int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],struct player players[],short nbrJoueur,short id);

//Fonction permettant la remise à zéro de la liste en entrée.
void initValues(int values[]);

//Fonction permettant de passer au tour suivant.
void tourPlayer(struct player players[],short nbrJoueur,short id,int values[],short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],short nombredee);

//Fonction permettant d'ajouter le pickomino au joueur.
void addPickoPlayer(struct player players[],int total,short nbrJoueur,short id,int dominos[][2]);

//Fonction permettant la sauvegarde en binaire de la partie.
void saveBinary(int dominos[][2],struct player players[],short nbrJoueur,short id);

//Fonction permettant la lecture de la sauvegarde binaire.
void readSave(int dominos[][2],int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id);

//Fonction permettant la réinitialisation des variables.
void resetGame(int dominos[][2],int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id);

//Fonction permettant la fin du jeu.
void endGame(struct player players[],short nbrJoueur);

//Fonction permettant de gérer le cas "Partie perdu".
void partiePerdu(int dominos[][2],int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id);

//Fonction permettant de gérer la prise du Domino.
void priseDomino(int dominos[][2],int total,int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id);

//Fonction permettant de vérifier si il y a un V dans la liste.
void checkIfVInDices(int listeChoixJoueur[],short compteurchoix, int coefChoixJoueur[], int dominos[][2],int values[],short nombredee,struct player players[],short nbrJoueur,short id);

//Fonction permettant de vérifier si j appartient à la liste dicekeep
int isIn(int dicekeep[],int numberdice,int j);

//Fonction permettant de prendre le choix du joueur à savoir quel dés le joueur prend-t'il.
void choixJoueur(short nombredee,int values[],short compteurchoix,int listeChoixJoueur[], int coefChoixJoueur[],int dominos[][2],struct player players[],short nbrJoueur,short id);

//Fonction permettant l'initialisation du jeu
void jeu(struct player players[7],short nbrJoueur);

//Fonction permettant l'initiation des joueurs.
void initJoueurs();
