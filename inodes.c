#include <stdio.h>
#include <stdlib.h>
#include "inodes.h"

dossier *initSGF(){
	
    dossier *racine =malloc(sizeof(dossier)); 
    racine->nom = "/";
    racine->parent = NULL;
    racine->suivant = NULL;
    racine->sousDossiers=NULL;
    racine->fichiers=NULL;
    return racine;
}

void afficherContenuD(dossier *actuel){
	
	if(actuel->sousDossiers!=NULL){
		dossier *tmpD=actuel->sousDossiers;
	    while(tmpD->suivant != NULL){
		    printf("%s   -    dossier\n", tmpD->nom);
		    tmpD = tmpD->suivant;
		}
		printf("%s    -    dossier\n", tmpD->nom);
	} 

	if(actuel->fichiers!=NULL){
		fichier *tmpF=actuel->fichiers;
	    while(tmpF->suivant != NULL){
		    printf("%s    -   fichier\n", tmpF->nom);
		    tmpF = tmpF->suivant;
		}
		printf("%s   -    fichier\n", tmpF->nom);
	} 
	printf("\n");	
}

void creerSousDossier(dossier *actuel, char *nom){

	dossier *nouveau = malloc(sizeof(dossier));
	nouveau->parent = actuel;
	nouveau->suivant=actuel->sousDossiers;
	nouveau->fichiers=NULL;
	nouveau->sousDossiers=NULL;
	nouveau->nom = nom;
	
	actuel->sousDossiers=nouveau;
}

void creerFichierVide(dossier *actuel, char *nom){

	fichier *nouveau = malloc(sizeof(fichier));
	nouveau->parent = actuel;
	nouveau->suivant=actuel->fichiers;
	nouveau->contenu=NULL;
	nouveau->nom = nom;
	
	actuel->fichiers=nouveau;
}
