# **Pickomino**

This is a school project in french of a game called Pickomino codded in C, to launch the game, download jeu.c, jeu.h and main.c, open new terminal in the dir where are located theses files, run `gcc main.c -Wall -pedantic` and after, run `./a.out`.

## Introduction

Pour l’UE de Structures de Données et Programmation C, l’enseignante de cette Unité d’Enseignement nous propose un projet à développer en Langage C, un des langages de programmation les plus utilisé permettant un dialogue directe avec la machine, un jeu de société nommé Pickomino est un jeu de dés de 2 à 7 joueurs ayant pour but de récupérer le plus grand nombre de dominos afin d’avoir le plus de points possible. Pour ce projet, je suis seul.

## I – Les règles

Avant de commencer le projet, nous devons savoir quoi et comment faire le jeu dès le début avant d’avancer tête baisser. Pour cela nous devons analyser chaque aspect du jeu en décryptant les règles en plusieurs parties.

	
**a) Les dominos**

Les dominos se divisent en deux parties, la partie du haut constituant la somme des dés et la partie du bas constituant les points.

Le plateau du jeu de départ est constitué de 16 dominos allant de 21 à 36. Chaque dominos possèdent un chiffre allant de 1 à 4 de cette façon :

- les 4 premiers dominos ont une valeur d’un point.
- les 4 dominos suivants ont une valeur de 2 points.
- les 4 dominos suivants ont une valeur de 3 points.
- les 4 derniers dominos ont une valeur de 4 points.

Représentation du plateau de départ:

┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐┌──┐

│21││22││23││24││25││26││27││28││29││30││31││32││33││34││35││36│

├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤├──┤

│ 1││ 1││ 1││ 1││ 2││ 2││ 2││ 2││ 3││ 3││ 3││ 3││ 4││ 4││ 4││ 4│

└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘└──┘

**b) Les dés**

Les dés sont des dés à 6 faces, avec les faces de 1 à 5 et une face spéciale ‘V’ (de valeur 5).

**c) Le déroulement**

8 dés sont lancés aléatoirement à chaque tour, le joueur décide de choisir une valeur de dé afin de prendre tous les dés ayant la même face.

Exemple : Si le 1er lancer donne V 3 2 5 V 5 5 1 et que le joueur décide de garder tous les 5, vu qu’il y a trois dés qui sont tombé sur la face 5, il les met de côté et il reste donc 5 dés à jouer.

À chaque tour, le joueur décide oui ou non de continuer à jouer.

Continuons avec ce même exemple, le joueur lance les 5 dès qu’il lui reste à jouer ce qui donne 5 V 2 5 V. Le joueur ne peut pas reprendre les même dés, ainsi, impossible de prendre les dés 5. Le joueur décide donc de prendre les dés V, il met donc de côté les deux dés avec la valeur V et décide de rejouer avec les 3 dés restant.

Le joueur effectue le 3ème lancé avec les 3 dés qu’il lui reste à jouer ce qui donne 2 2 2, il décide donc de récupérer les dés 4.

Nous devons maintenant faire le total des points, 5*3+V*2+2*3=31

Le joueur a donc gagné le pickomino 31 qui a été retiré du plateau et a remporté 3 points.

Le joueur peut raté son tour et donc, ne gagner aucun pickomino dans les cas suivants :  

 1. Le joueur ne peut pas mettre des dés de côté car il a déjà choisi ces valeurs auparavant.
 2. Le joueur n’a pris aucun V.
 3. Si la somme des dés est inférieur à 21 ou supérieur à 36.
 4. Si la somme est égal à un pickomino plus disponible.

Le jeu se termine quand tous les pickominos ont été pris du plateau. Le vainqueur est celui qui accumule le plus de points.

## II – Les Bases

**a) Les joueurs**

Afin d’établir les variables du joueurs, il est bien trop compliquer d’initier variable par variable chaque joueur, afin de faciliter la tâche, j’ai utilisé les structures en C.

**Qu’est-ce qu’une structure ?**

Une structure en C est une sorte de dictionnaire portant un nom regroupant des variables.

Cela permet qu’une seule variable en regroupe plusieurs.

Notre joueur a besoin de stocker les informations suivantes :

 - Le pseudo
 - Les pickominos obtenus
 - Le nombre de pickominos obtenus
 - Les points

Ainsi, la structure dans le code ressemble à ceci :

```c
typedef struct player{
	char username[16];
	int pickominos[16];
	int nombreDeDominos;
	int points;
}player;
```
Nous allons détailler chaque variable :

 - char username[16] peut prendre uniquement 15 caractères (15 caractères +’/0’=16), elle stocke le pseudo du joueur
 - int pickominos[16] stocke les pickominos que le joueur possède
 - int nombreDeDominos stocke le nombre de pickominos que le joueur possède
 - int points stocke le nombre de points que le joueur possède

Afin de faciliter la gestion des joueurs dans le programme, j’ai créé une liste players qui peut posséder au maximum 7 joueurs et qui permet le stockage de toutes les informations des joueurs.

Le programme demande dès le début le nombre de joueurs qui est stocké dans une variable nommé « nbrJoueur », et boucle jusqu’au chiffre indiqué pour demander le pseudo des joueurs qui est stocké dans une variable temporaire nommé « name ». Si le nombre indiqué n’est pas compris entre 2 et 7 joueurs ou n’est pas un chiffre, le programme repose la question en indiquant de choisir une valeur comprise entre 2 et 7.

Pour cela, j’ai fait la fonction buffer permettant d’éviter que la fonction bug en redemandant à l’infini au joueur d’entrer une bonne valeur.

J’utilise la fonction strcpy incluse dans la librairie string.h afin de copier une chaine de caractère dans une autre variable.

Ensuite, chaque valeur des variable sont inités à 0, de même que les 16 pickominos.

La variable id permet de définir qui est en train de jouer dans le programme.

**b) Les pickominos**

La fonction afficheurPlateau gère l’affichage des pickominos.

J’inities au début de mon programme une variable nommé dominos de la manière suivant :

Int dominos[][2]= {{21,1},{22,1},{23,1},{24,1},{25,2},{26,2},{27,2}, {28,2},{29,3},{30,3},{31,3},{32,3},{33,4},{34,4},{35,4},{36,4}};

Ainsi, dominos[i][j] :

i : numéro du pickomino – 21 pour obtenir l’indice du pickomino dans la liste

j : si j==0 -> numéro du pickomino

si j==1 -> points du pickomino

J’ai fait une fonction afficheurPlateau qui prend en entrée une liste de liste et permet l’affichage graphique des dominos de la façon suivante :

 1. Premiere ligne => ┌──┐
 2. Deuxième ligne => │%d│
 3. Troisième ligne => ├──┤
 4. Quatrième ligne => │ %d│
 5. Cinquième ligne => └──┘

A la deuxième ligne, la variable affiché est dominos[i][0] et à la quatrième ligne, la variable affiché est dominos[i][1].

Le programme boucle i fois le nombre de dés.

Pour les dominos pris, la valeur de dominos[i][0] et dominos[i][1] devient 0. Ainsi, dans l’affichage des dominos, si la valeur==0 alors, le programme affiche XX à la place de la valeur inscrit dans le domino.

**c) Les dés**

Pour l’affichage des dés, la fonction afficheurDee génère une liste qui génère aléatoirement un chiffre entre 1 et 6 et cela n fois le nombre de dés.

Ensuite, elle les affichent de cette façon :

1ère ligne -> ┌─────┐

2ème ligne -> si values[i]==6 : │\\  /│  
sinon si values[i]==1 : │  │

sinon si values[i]==2 ou values[i]==3 : │o  │

sinon si values[i]==4 ou values[i]==5 : │o  o│

3ème ligne -> si values[i]==6 : │ \\ / │  
sinon si values[i]==1 ou values[i]==3 ou  
values[i]==5 : │  o  │

sinon si values[i]==2 ou values[i]==4 : │ │

4ème ligne -> si values[i]==6 : │ v │  
						sinon si values[i]==1 : │  │

sinon si values[i]==2 ou values[i]==3 : │ o│

sinon si values[i]==4 ou values[i]==5 : │o  o│

5ème ligne -> └─────┘

Ce qui donne par exemple pour l’affichage de 8 dés :
![Screenshot 2022-01-17 at 15 57 56](https://user-images.githubusercontent.com/50799531/149902134-b01944cb-817e-44bc-b981-1d8bf4126772.png)


## III- Le code

**a) La fonction choixJoueur**

La fonction choixJoueur est l’une des fonctions principale permettant de demander et de valider le choix du joueur pour la prise des dés.

Comme vu dans les règles, il y a 6 valeurs possible pour un dé, 1 2 3 4 5 et V. Toute la difficulté réside dans le V car c’est un caractère.

Ainsi, afin de résoudre ce problème, nous avons tout de même initié la liste avec un type int mais uniquement l’affichage est V.

C’est à dire, dans le code, V est reconnu comme 6, le scanf qui demande au joueur de prendre un dé enregistre la réponse dans une variable char.

Si le joueur décide de prendre un chiffre, dans le code ascii, le 1 correspond à 49 et le 5 correspond à 53, ainsi, il est ensuite converti en int en soustrayant par 48 afin de permettre tous les autres calcule dans le programme.

Si le joueur décide de prendre V, dans la table ascii V correspond à 86, ainsi, il est transformé en int en devenant 6 afin de permettre tous les autres calculs dans le programme.

Cette fonction vérifie :

 1. si il reste toujours des dés
 2. si le joueur peut prendre les dés restant ou si il les a déjà choisi auparavant
 3. si le choix du joueur est bien uniquement une valeur compris entre 1 et 5 ou V
 4. si le choix du joueur a déjà été choisi auparavant
 5. si le choix du joueur correspond bien à au minimum un dé dans la liste des dés tirés

Chaque choix que le joueur fait est stocké dans la liste listeChoixJoueur à la position compteurchoix.

L’occurrence des dés est stocké dans la liste coefChoixJoueur à la position compteurchoix.

**b) Prise du domino**

Lorsqu’il ne reste plus de dés ou que le joueur décide de ne pas continuer, le programme lance la fonction somme qui calcule le total des dés.

Afin de prendre le domino correspondant au total des dés pris, on soustrait le total à 21 si la valeur est comprise entre 21 et 36 afin d’obtenir la position du domino dans la liste.

Si le domino est bien présent dans le plateau, elle attribut 0 à la valeur dominos[i][0], ainsi, le programme considère un domino pris lorsque la valeur du haut est égal à 0.

**c) Tour Perdu**

Comme vu dans les règles, le tour est perdu si le joueur n’a pas pris de V, ainsi, la fonction checkVInDices vérifie cette règle.

Elle prend vérifie si le choix du joueur est dans la liste listeChoixJoueur.

Le tour est perdu si la somme des dés pris est égal à un domino inexistant c’est à dire :

 - Si la somme est inférieur à 21
 - Si la somme est supérieur à 36
 - Si la somme est égal à un domino déjà pris

Ces conditions sont gérées par la fonction priseDomino. Si la somme n’est pas comprise entre 21 et 36, la fonction renvoie « Parti Perdu, inexistant. » et si domino[total-21][0]==0 alors, le programme concidère que le domino est déjà pris et donc renvoie « Parti Perdu, domino déjà pris ».

Si un tour est perdu, le dernier domino de la pile du joueur (à savoir players[id].pickominos[players[id].nombreDeDominos]) est remis dans le plateau (donc dans la liste dominos) si players[id].nombreDeDominos est différent de 0 avant que le programme prend le domino ayant la plus grande valeur.

Afin de prendre le domino ayant la plus grande valeur, j’utilise une boucle while qui boucle jusqu’à que dominos[i][0] est différent de 0 et décrémente i qui est initié à 15 au départ.

**d) Tour gagné**

Quand le tour est gagné, la fonction priseDomino appel la fonction addPickoPlayer.

Cette fonction ajoute à la liste du joueur en train de jouer (à savoir players[id]) le pickomino gagné, ajoute les points à la variable points du joueur (à savoir domino[total-21][1]) et incrémente de 1 la variable nombreDeDominos du joueur.

Ensuite, elle incrémente la variable id de 1 avant de réinitialiser les variables afin de passer au tour suivant, donc, au joueur suivant.

**e) La sauvegarde**

J’ai décidé de sauvegarder les parties en binaire afin que la triche soit plus compliqué que simplement changer les valeurs dans le fichier de sauvegarde.

Ainsi, la fonction saveBinary est appelé à chaque fin de tour afin que la sauvegarde soit automatique.

On ouvre le fichier « save.bin » qui est créé s’il est inexistant et on indique qu’on veut écrire en binaire

On écrite en binaire 4 variables qui définissent le cours de la partie à savoir :

 - Les dominos (int dominos[][])
 - Les joueurs (player players[])
 - Le nombre de joueurs (short nbrJoueur)
 - L’id du joueur en train de jouer (short id)

Pour finir, nous fermons la lecture du fichier.

Ensuite, pour la lecture de la sauvegarde, lorsque le programme se lance, si un fichier nommé « save.bin » est trouvé dans le même dossier que le programme, la sauvegarde sera pris et à l’initiation des variables au début du programme, les variables de la sauvegarde seront prisent.

**f) Fin du jeu**

La fin du jeu est déclenchée quand toutes les valeurs des dominos (à savoir dominos[i][0]) est égal à 0.

Tout d’abord, elle crée 2 listes, une nommé points avec les points de chaque joueur, une autre nommé idsjoueurs avec les ids de chaque joueur. Chaque indice de idsjoueurs correspond à l’indice des points dans la liste points.

On fait un tri par insertion decroissant de la liste points et on change la liste idsjoueurs pour que chaque indice de idsjoueurs correspondent toujours à l’indice des points dans la liste.

Si deux joueurs ont le même nombre de point, le joueur qui possède le plus grand pickomino remporte la partie.

Ainsi, la fonction endGame vérifie qui a le plus grand nombre de point. Si plusieurs joueurs ont le même nombre de points, il vérifie qui a le pickomino le plus grand et le déclare vinqueur.

Pour finir, elle supprime la sauvegarde et met fin au processus.

## IV – L’IA

Afin de désigner une IA, le game master devra indiquer IA, ainsi, le nom de joueur de l’IA sera IA avec son numéro. Exemple : IA1, IA2, etc…

L’IA vérifie d’abord les possibilités de prise de dés, ainsi, tous les dés qu’il peut prendre est inscrit dans une liste nommée possibilite.

Par la suite, elle fait la somme de chaque possibilité dans la liste des dés donc possibilite[i] fois le nombre d’occurrence dans la liste des dés.

Ensuite, l’IA vérifie quelle est la plus grosse somme et stock la valeur du dé correspondant à cette dernière.

Pour finir, le programme converti le résultat en ascii en ajoutant 48 si le dé est compris entre 1 et 5 ou devient 86 si le résultat est 6 donc V

Si il y a deux fois le dé 5 et deux fois le dé V, l’IA préfèrera prendre les V.

Pour que le joueur puisse comprendre quel choix l’IA a fait, j’ai fait un printf qui simule une entrée de scanf.

## Conclusion

Ce projet m’a permis d’apprendre le langage de programmation C qui est le langage le plus important. Tout développeur se doit de toucher le C au moins une fois dans sa vie afin de comprendre le dialogue code/machine. De plus, ce projet m’a permis de me prouver que je peux réussir un projet, qui est de base en binôme, seul.
