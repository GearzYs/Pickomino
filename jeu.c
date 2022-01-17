#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef struct player{
    char username[16];
    int pickominos[16];
    int nombreDeDominos;
    int points;
    int IA;
}player;

void afficheurDee(int values[],short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],short nombredee,struct player players[],short nbrJoueur,short id);

void priseDomino(int dominos[][2],int total,int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id);

void initJoueurs();

void buffer(FILE *c){
    char temp;
    while((temp=fgetc(c))!='\n'&&temp != EOF);
}

void afficheurPlateau(int dominos[][2]){
    int nombreDomino=16;
    for (int i = 0; i<nombreDomino;i++) {
        printf("┌──┐ ");
    }
    printf("\n");
    for (int i = 0; i<nombreDomino;i++) {
        if (dominos[i][0]==0){
            printf("│XX│ ");
        }
        else {
            printf("│%d│ ",dominos[i][0]);
        }
    }
    printf("\n");
    for(int i = 0;i<nombreDomino;i++){
        printf("├──┤ ");
    }
    printf("\n");
    for (int i = 0; i<nombreDomino;i++) {
        if (dominos[i][0]==0){
            printf("│XX│ ");
        }
        else {
            printf("│ %d│ ",dominos[i][1]);
        }
    }
    printf("\n");
    for (int i = 0; i<nombreDomino;i++) {
        printf("└──┘ ");
    }
    printf("\n");
}

void somme(int listeChoixJoueur[],short compteurchoix,int coefChoixJoueur[],int dominos[][2],int values[],short nombredee,struct player players[],short nbrJoueur,short id){
    int total=0;
    for (int i=0;i<compteurchoix;i++) {
        if (listeChoixJoueur[i]==6){
            total+=(listeChoixJoueur[i]-1)*coefChoixJoueur[i];
        }
        else {
            total+=listeChoixJoueur[i]*coefChoixJoueur[i];
        }
    }
    printf("Le total est : %d \n",total);
    priseDomino(dominos,total,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
}

void askContinue(int listeChoixJoueur[],short compteurchoix,int coefChoixJoueur[],int dominos[][2],int values[],short nombredee,struct player players[],short nbrJoueur,short id){
    char temp[2];
    if (players[id].IA==0){
        printf("Voulez vous relancer les dés ? 'o' pour oui et 'n' pour non. \n");
        scanf("%s",temp);
    }
    else {
        temp[0]='o';
    }
    if (temp[0]=='o'){
        afficheurDee(values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,nombredee,players,nbrJoueur,id);
    }
    if (temp[0]=='n'){
        somme(listeChoixJoueur,compteurchoix,coefChoixJoueur,dominos,values,nombredee,players,nbrJoueur,id);
    }
    else {
        printf("Veuillez indiquer une bonne valeur.\n");
        askContinue(listeChoixJoueur,compteurchoix,coefChoixJoueur,dominos,values,nombredee,players,nbrJoueur,id);
    }
}

void priseDes(int choixDuJoueur,int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],struct player players[],short nbrJoueur,short id) {
    for (int i=0;i<nombredee;i++) {
        if (values[i]==choixDuJoueur) {
            coefChoixJoueur[compteurchoix-1]+=1;
        }
    }
    nombredee-=coefChoixJoueur[compteurchoix-1];
    if (nombredee==0){
        afficheurDee(values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,nombredee,players,nbrJoueur,id);
    }
    else {
        askContinue(listeChoixJoueur,compteurchoix,coefChoixJoueur,dominos,values,nombredee,players,nbrJoueur,id);
    }
}

void initValues(int values[]){
    for (int i=0;i<8;i++){
        values[i]=0;
    }
}

void tourPlayer(struct player players[],short nbrJoueur,short id,int values[],short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],short nombredee){
    id++;
    if (id>=nbrJoueur){
        id=0;
    }
    printf("Au tour de %s :\n",players[id].username);
    afficheurDee(values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,nombredee,players,nbrJoueur,id);
}

void addPickoPlayer(struct player players[],int total,short nbrJoueur,short id,int dominos[][2]){
    players[id].pickominos[players[id].nombreDeDominos]=total;
    players[id].points+=dominos[total-21][1];
    players[id].nombreDeDominos++;
    printf("%s a gagné %d points et a un total de %d points.\n",players[id].username,dominos[total-21][1],players[id].points);
    id++;
    if (id>=nbrJoueur){
        id=0;
    }
}

void saveBinary(int dominos[][2],struct player players[],short nbrJoueur,short id){
    FILE* save;
    save=fopen("save.bin","wb");
    if(save==NULL){
        printf("Impossible de sauvegarder");
    }
    fwrite(&nbrJoueur,sizeof(short),1,save);
    fwrite(&id,sizeof(short),1,save);
    fwrite(dominos,sizeof(int),16,save);
    fwrite(players,sizeof(player),nbrJoueur,save);
    fclose(save);
}

void readSave(int dominos[][2],int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id) {
    FILE* save;
    save=fopen("save.bin","rb");
    if (save==NULL){
        printf("Pas de sauvegarde, début d'une nouvelle partie.\n");
    }
    else {
        fread(&nbrJoueur,sizeof(short),1,save);
        fread(&id,sizeof(short),1,save);
        fread(dominos,sizeof(int),16,save);
        fread(players,sizeof(player),nbrJoueur,save);
        fclose(save);
        printf("Bonjour et bienvenue dans le jeu Pickomino. La sauvegarde est automatique.\nVoici le plateau :\n");
        afficheurPlateau(dominos);
        tourPlayer(players,nbrJoueur,id,values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,nombredee);
    }
}

void resetGame(int dominos[][2],int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id){
        afficheurPlateau(dominos);
        nombredee=8;
        initValues(listeChoixJoueur);
        initValues(values);
        initValues(coefChoixJoueur);
        compteurchoix=0;
        tourPlayer(players,nbrJoueur,id,values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,nombredee);
}

void endGame(struct player players[],short nbrJoueur){
    printf("Plus de dominos disponible, partie terminé !\nVoici le classement:\n");
    remove("save.bin");
    short equal=0;
    int points[7];
    int idsjoueurs[7];
    short idgagnant;
    for (int i=0;i<nbrJoueur;i++){
        points[i]=players[i].points;
        idsjoueurs[i]=i;
    }
    //tri par insertion
    for (int i=1;i<nbrJoueur;i++){
        int x=points[i];
        int y=idsjoueurs[i];
        int j=i;
        while (j>0 && points[j-1]<x){
            points[j]=points[j-1];
            idsjoueurs[j]=idsjoueurs[j-1];
            j--;
        }
        points[j]=x;
        idsjoueurs[j]=y;
        idgagnant=y;
    }
    short temp1=points[1];
    short temp2=idsjoueurs[1];
    for (int i=0;i<nbrJoueur;i++){
        printf("%s a %d points.\n",players[idsjoueurs[i]].username,players[idsjoueurs[i]].points);
        if (temp1==points[i]){
            if (players[temp2].pickominos[players[temp2].nombreDeDominos]<players[i].pickominos[players[i].nombreDeDominos]){
                temp2=idsjoueurs[i];
                equal=1;
            }
        }
    }
    if (equal==1){
    printf("Le gagnant est donc %s avec %d points et le plus grand pickomino %d !\n",players[temp2].username,players[temp2].points,players[temp2].pickominos[players[temp2].nombreDeDominos]);
    }
    else{
        printf("Le gagnant est donc %s avec %d points !\n",players[idsjoueurs[0]].username,players[idsjoueurs[0]].points);
    }
    exit(0);
}

void partiePerdu(int dominos[][2],int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id){
    printf("Dernier domino de %s :\n",players[id].username);
    int i=15;
    if (players[id].nombreDeDominos!=0){
        players[id].nombreDeDominos--;
        dominos[players[id].pickominos[players[id].nombreDeDominos]-21][0]=players[id].pickominos[players[id].nombreDeDominos];
        while (dominos[i][0]==0){
            i--;
        }
        dominos[i][0]=0;
        printf("Plus grand domino retiré.\n");
    }
    else {
        printf("Inexistant.");
        while (dominos[i][0]==0){
            i--;
        }
        dominos[i][0]=0;
        printf("Plus grand domino retiré.\n");
    }
    for (int i=0;i<16;i++){
        if(dominos[i][0]!=0){
            saveBinary(dominos,players,nbrJoueur,id);
            resetGame(dominos,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
        }
    }
    endGame(players,nbrJoueur);
}

void priseDomino(int dominos[][2],int total,int values[],short nombredee,short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],struct player players[],short nbrJoueur,short id) {
    if (total>=21 && total<=36){
        int temp=16-(37-total);
        if (dominos[temp][0]!=0) {
            dominos[temp][0]=0;
            addPickoPlayer(players,total,nbrJoueur,id,dominos);
            saveBinary(dominos,players,nbrJoueur,id);
            resetGame(dominos,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
        }
        else {
            printf("Parti Perdu, domino déjà pris.\n");
            partiePerdu(dominos,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
        }
    }
    else {
        printf("Parti Perdu, inexistant.\n");
        partiePerdu(dominos,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
    }
}

void checkIfVInDices(int listeChoixJoueur[],short compteurchoix, int coefChoixJoueur[], int dominos[][2],int values[],short nombredee,struct player players[],short nbrJoueur,short id){
    for (int i=0; i<compteurchoix;i++){
        if (listeChoixJoueur[i]==6){
            somme(listeChoixJoueur,compteurchoix,coefChoixJoueur,dominos,values,nombredee,players,nbrJoueur,id);
        }
        if (listeChoixJoueur[i]!=6 && i==compteurchoix-1){
            printf("Partie perdu, pas de V. \n");
            partiePerdu(dominos,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
        }
    }
}

int isIn(int desgarde[],int nombre,int j){
    for(int i=0;i<nombre;i++){
        if(desgarde[i]==j){
            return 1;
        }
    }
    return 0;
}

void choixJoueur(short nombredee,int values[],short compteurchoix,int listeChoixJoueur[], int coefChoixJoueur[],int dominos[][2],struct player players[],short nbrJoueur,short id){
    //check if there are still a dice
    if (nombredee==0) {
        printf("Il n'y a plus de dés à prendre. \n");
        checkIfVInDices(listeChoixJoueur,compteurchoix,coefChoixJoueur,dominos,values,nombredee,players,nbrJoueur,id);
    }
    //check if the remaining dice are not already in listeChoixJoueur
    int compteur1=0;
    for (int i=0; i<nombredee;i++){
        for (int j=0;j<compteurchoix;j++){
            if (listeChoixJoueur[j]==values[i]){
                compteur1++;
            }
        }
        if (compteur1==nombredee){
            printf("Vous ne pouvez pas prendre ces dés. \n");
            nombredee=0;
            checkIfVInDices(listeChoixJoueur,compteurchoix,coefChoixJoueur,dominos,values,nombredee,players,nbrJoueur,id);
        }
    }
    int temp=0;
    if (players[id].IA==0){
        char choixDuJoueur[2];
        compteur1=0;
        reask:
        printf("Quel est votre choix ? : ");
        scanf("%s", choixDuJoueur);
        temp=(int)choixDuJoueur[0];
    }
    // IA
    if(players[id].IA==1){
        printf("Quel est votre choix ? : ");
        int possible[6];
        int sommepossible[6];
        short compteur=0;
        for(int i=1;i<=6;i++){
            if(isIn(listeChoixJoueur,8-nombredee,i)==0){
                for(int j=0;j<nombredee;j++){
                    if(values[j]==i){
                        possible[compteur]=i;
                        compteur++;
                        goto down;
                    }
                }
            }
            down:printf("");
        }
        short temp1=0;
        for (int i=0;i<compteur;i++){
            temp1=0;
            for(int j=0;j<nombredee;j++) {
                if (values[j]==possible[i]){
                    temp1++;
                }
            }
            sommepossible[i]=possible[i]*temp1;
        }
        short higherSomme=sommepossible[0];
        short temp2=possible[0];
        for (int i=1;i<compteur;i++){
            if(sommepossible[i]>higherSomme){
                higherSomme=sommepossible[i];
                temp2=possible[i];
            }
        }
        temp=temp2;
        if (temp==6){
            temp=86;
        }
        else {
            temp+=48;
        }
        sleep(2);
        printf("%d\n",temp2);
        sleep(1);
        // Fin IA
    }
    if ((temp>=49 && temp<=53) || temp==86){
        if ((temp>=49 && temp<=53)) {
            temp-=48;
        }
        else {
            temp=6;
        }
    //check if the value is already in listeChoixJoueur
        for (int i=0; i<compteurchoix;i++){
            if (temp==listeChoixJoueur[i]){
                printf("Vous avez déjà choisi ce chiffre. \n");
                goto reask;
            }
        }
    //check if the value is in the dices
        int i=0;
        while (values[i]!=temp && i<nombredee) {
            i++;
        }
        if (i<nombredee) {
            listeChoixJoueur[compteurchoix]=temp;
            compteurchoix++;
            i=nombredee;
            priseDes(temp,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,players,nbrJoueur,id);
        }
        else{
            printf("Votre chiffre n'est pas dans les dés tirés. \n");
            goto reask;
        }
    }
    else {
        printf("Veuillez entrer une bonne valeur.\n");
        goto reask;
    }
}

void afficheurDee(int values[],short compteurchoix,int listeChoixJoueur[],int coefChoixJoueur[],int dominos[][2],short nombredee,struct player players[],short nbrJoueur,short id) {
    initValues(values);
    for (int i=0; i<nombredee; i++) {
        values[i] = (rand() % 6) + 1;
    }
    for (int i=0; i<nombredee; i++) {
        if (values[i]!=0){
            printf("┌─────┐");
        }
    }
    printf("\n");
    for (int i=0; i<nombredee; i++) {
        if (values[i]==6) {
            printf("│\\   /│");
        }
        else if (values[i]==1){
            printf("│     │");
        }
        else if (values[i]==2||values[i]==3){
            printf("│O    │");
        }
        else if (values[i]==4||values[i]==5){
            printf("│O   O│");
        }
        
    }
    printf("\n");
    for (int i=0; i<nombredee; i++) {
        if (values[i]==6) {
            printf("│ \\ / │");
        }
        else if (values[i]==1||values[i]==3||values[i]==5){
            printf("│  O  │");
        }
        else if (values[i]==2||values[i]==4){
            printf("│     │");
        }
    }
    printf("\n");
    for (int i=0; i<nombredee; i++) {
        if (values[i]==6) {
            printf("│  V  │");
        }
        else if (values[i]==1){
            printf("│     │");
        }
        else if (values[i]==2||values[i]==3){
            printf("│    O│");
        }
        else if (values[i]==4||values[i]==5){
            printf("│O   O│");
        }
    }
    printf("\n");
    for (int i=0; i<nombredee; i++) {
        if (values[i]!=0) {
            printf("└─────┘");
        }

    }
    printf("\n");
    choixJoueur(nombredee,values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,players,nbrJoueur,id);
}

void jeu(struct player players[7],short nbrJoueur){
    short nombredee=8;
    short compteurchoix=0;
    int listeChoixJoueur[6];
    int values[8];
    short id=-1;
    int coefChoixJoueur[8]={0,0,0,0,0,0,0,0};
    int dominos[][2]={{21,1},{22,1},{23,1},{24,1},{25,2},{26,2},{27,2},{28,2},{29,3},{30,3},{31,3},{32,3},{33,4},{34,4},{35,4},{36,4}};
    readSave(dominos,values,nombredee,compteurchoix,listeChoixJoueur,coefChoixJoueur,players,nbrJoueur,id);
    if (nbrJoueur==0){
        initJoueurs();
    }
    printf("Bonjour et bienvenue dans le jeu Pickomino. La sauvegarde est automatique.\nVoici le plateau :\n");
    afficheurPlateau(dominos);
    tourPlayer(players,nbrJoueur,id,values,compteurchoix,listeChoixJoueur,coefChoixJoueur,dominos,nombredee);
}

void initJoueurs(){
    short nbrJoueur;
    short temp=1;
    player players[7];
    char name[16];
    reaskplayer:
    printf("Combien de joueurs ? ");
    fscanf(stdin,"%hd",&nbrJoueur);
    buffer(stdin);
    if (nbrJoueur>=2 && nbrJoueur<=7){
        for (int i=0;i<nbrJoueur;i++) {
            printf("Entrez le nom du joueur %d. Ecrire IA avant le nom du joueur pour les IA : ",i+1);
            fscanf(stdin,"%s",name);
            if (name[0]=='I' && name[1]=='A' && name[2]=='\0'){
                sprintf(name,"%s%hd",name,temp);
                temp++;
                players[i].IA=1;
            }
            else if (name[0]=='I' && name[1]=='A'){
                players[i].IA=1;
            }
            else{
                players[i].IA=0;
            }
            for (int j=0;j<16;j++) {
                players[i].pickominos[j]=0;
            }
            players[i].nombreDeDominos=0;
            players[i].points=0;
            strcpy(players[i].username,name);
            buffer(stdin);
        }
        jeu(players,nbrJoueur);        
    }
    else {
        printf("Veuillez entrer un chiffre compris entre 2 et 7.\n");
        goto reaskplayer;
    }
}
