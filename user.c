#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blocks.h"

int connexion(superBlock *sb, char *argNom, char *argmdp){ //connexion d'un utilisateur
	user *tmpU = sb->users;
	while(tmpU!=NULL && strcmp(argNom,tmpU->nom)!=0){
		printf("c'est pas %s boloss\n", tmpU->nom);
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

user *initUser(int argnoUser, char *argNom, char *argmdp){
	user *tmpU = malloc(sizeof(user));
	tmpU->noUser = argnoUser;
	tmpU->nom=argNom;
	tmpU->mdp=argmdp;
	tmpU->next=NULL;
	return tmpU;
}

user *noUserToUser(superBlock *sb, int argNumero){
	user *tmpU=sb->users;
	while(tmpU!=NULL && tmpU->noUser!=argNumero){
		tmpU=tmpU->next;
	}
	if(tmpU!=NULL){
		return tmpU;
	}
	else{
	    printf("erreur critique sur user\n");
	    exit(2);
	}
}

user *nomUserToUser(superBlock *sb, char *argNom){
	user *tmpU=sb->users;
	while(tmpU!=NULL && strcmp(tmpU->nom,argNom)==0){
		tmpU=tmpU->next;
	}
	if(tmpU!=NULL){
		return tmpU;
	}
	else{
	    return NULL;
	    exit(2);
	}
}


int chproprio(superBlock *sb, int argInode,int uConnecte, char *argNom){
	// on verifie que le nouveau prorio existe
	user *tmpU = sb->users;
	while(tmpU!=NULL && strcmp(argNom,tmpU->nom)!=0){
		tmpU=tmpU->next;
	}
	if(tmpU==NULL){
		printf("utilisateur non existant\n");
		return -1;
	}
	else{ //si il existe on vérifie qu'on est admin ou proprio
		inode *tmpI=noInodeToInode(sb, argInode);
		if(uConnecte==0 || uConnecte==tmpU->noUser){
			tmpI->proprio=tmpU->noUser;
			printf("changement de proprio ok\n");
			return tmpU->noUser;
		}
		else{
			printf("modification interdite \n");
			return -1;
		}
	}
}

int verifDroit(superBlock *sb, int argInode, int userCo, int action){
	//verifie que l'utilisateur a les droits pour l'action (1 lecture, 2 ecriture)
	if(userCo==0){//cas de l'administrateur, subZero gagne toujours
		return 1; 
	}
	else{
		inode *tmpI=noInodeToInode(sb, argInode);
		if(tmpI->proprio==userCo && (tmpI->droitU==3 || tmpI->droitU==action)){
			return 1; //cas ou l'utilisateur est proprio et les droits correspondent
		}
		else if(tmpI->proprio!=userCo && (tmpI->droitA==3 || tmpI->droitA==action)){
			return 1; //cas ou l'utisaleur n'est pas proprio mais à le droit
		}
		else{
			return 0; //pas le droit :(
		}
	}
}
int chmod(superBlock *sb, int argInode, int userCo, int newDroitU, int newDroitA){
	if(newDroitU<0 || newDroitU>3 ||newDroitA<0 ||newDroitA>3){
		printf("Changement incorrect\n");
		return -1;
	}
	inode *tmpI = noInodeToInode(sb, argInode);
	printf("%d\n", argInode);
	if(argInode ==0 || tmpI==NULL){
		printf("cible incorrecte\n");
		return 0;
	}
	if(userCo==0 || userCo==tmpI->proprio){//cas de l'administrateur, subZero gagne toujours ou utilisateur lambda correct
		tmpI->droitU=newDroitU;
		tmpI->droitA=newDroitA;
		printf("changement de droit ok\n");
		return 1; 
	}
	else{
		printf("changement de droit interdit\n");
		return 0;	
	}
}

int newUser(superBlock *sb, char *argNom, char *mdp){
	user *tmpU=sb->users;
	// on verifie que le nom est pas deja pris
	while(tmpU!=NULL){
		if(strcmp(argNom, tmpU->nom)==0){
			printf("nom deja pris\n");
			return -1;
		}
		tmpU=tmpU->next;
	}
	tmpU = sb->users;
	while(tmpU->next!=NULL){
		tmpU=tmpU->next;
	}
	tmpU->next=initUser(tmpU->noUser+1, argNom, mdp);
	printf("utilisateur %s créé : noUser : %d\n",argNom, tmpU->noUser+1);
	return tmpU->noUser+1;
}

int delUser(superBlock *sb, int userCo, char *argNom){
	if(userCo!=0){
		printf("seul subZero peut supprimer un utilisateur\n");
		return -1;
	}
	else if(strcmp(argNom,"subZero")==0){
		printf("subZero ne peut pas se supprimer\n");
		return -1;
	}
	else{
		user *tmpU=sb->users;
		while(tmpU!=NULL && strcmp(tmpU->next->nom,argNom)!=0)
			tmpU=tmpU->next;
		if(tmpU==NULL){
			printf("utilisateur inexistant\n");
			return -1;
		}
		else{ //cas de suppression on supprime l'utilisateur 
			int noUserSuppr =tmpU->next->noUser;
			tmpU->next=tmpU->next->next;
			inode *tmpI=sb->inodes;
			while(tmpI!=NULL){
				if(tmpI->proprio==noUserSuppr)
					tmpI->proprio=0;
				tmpI=tmpI->next;
			}
			printf("utilisateur supprimé\n");
			return 1;
	   }
	}
}

void tableUser(superBlock *sb, int userCo){

	if(userCo==0){
		user *tmpU=sb->users;
		printf("Mode admin : noUser | Nom | mdp\n");
		while(tmpU!=NULL){
			printf("%d\t| %s\t| %s\n",tmpU->noUser, tmpU->nom, tmpU->mdp);
			tmpU=tmpU->next;
		}
	}
	else{
		user *tmpU=sb->users;
		printf("Mode utilisateur : ");
		while(tmpU!=NULL){
			printf("%s\t",tmpU->nom);
			tmpU=tmpU->next;
		}
		printf("\n");
	}
}
