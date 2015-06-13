#include "blocks.h"

void cat(superBlock *sb, int argInode, int userCo){ //affiche le contenu d'un fichier
	if(verifDroit(sb,argInode,userCo,1)==1 && noInodeToInode(sb, argInode)->typeBlock==1){
		printf("%s\n",lireFichier(sb, argInode));
			int c=0; // on vide le buffer (probleme sinon)
			while(c!='\n' && c!=EOF){
				c=getchar();
			}
	}
	else
		printf("action interdite\n");
}
