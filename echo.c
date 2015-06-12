#include "blocks.h"

void echo (superBlock *sb,int InodeFichier, int userCo) //ecrase le contenu d'un fichier
{
	if(verifDroit(sb, InodeFichier, userCo, 2)==1){
		inode * ino = noInodeToInode(sb,InodeFichier);
		char buffer [1000];
		int longueur=0;
		char*phrase;
		if(ino->typeBlock==1)
		{
			printf("Que voulez vous écrire dans ce fichier ? \n");
			fgets(buffer, 999, stdin);
			longueur=strlen(buffer);
			phrase=malloc(longueur*sizeof(char));
			strcpy(phrase,buffer);
			modifContenu(sb,InodeFichier, phrase);

		}
		else
		{
			printf("Ce n'est pas un fichier que vous voulez modifier \n");
		}
	}
	else{
		printf("Action interdite\n");
	}
}
