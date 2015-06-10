#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

int connexion(superBlock *sb, char *argNom, char *argmdp){ //connexion d'un utilisateur
	user *tmpU = sb->users;
	while(tmpU!=NULL && strcmp(argNom,tmpU->nom)!=0){
		tmpU=tmpU->next;
	}
	if(tmpU==NULL){
		printf("utilisateur non existant\n");
		return -1;
	}
	else{
		if(strcmp(argmdp,tmpU->mdp)!=0){
			printf("mot de passe incorrect\n");
			return -1;
		}
		else{
			printf("Bienvenue %s\n",argNom);
			
			return tmpU->noUser;
		}
	}
}

user *initUser(superBlock *sb, int argnoUser, char *argNom, char *argmdp){
	user *tmpU = malloc(sizeof(user));
	tmpU->noUser = argnoUser;
	tmpU->nom=argNom;
	tmpU->mdp=argmdp;
	tmpU->next=NULL
	return tmpU;
}
int verifDroit(
