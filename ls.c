#include "blocks.h"

void ls(superBlock *sb, int argInode){//affiche le contenu d'un dossier
    blockD *tmpD = noInodeToBlockD(sb, argInode);
    inode *tmpI;
    user *tmpU;
    char type;
    int i;
    for(i=2; i<20;i++){
		if(tmpD->inodes[i]!=0 ){
			tmpI=noInodeToInode(sb, tmpD->inodes[i]);
			tmpU=noUserToUser(sb, tmpI->proprio);
			if(tmpI->typeBlock==0){
				type='d';
				printf("%s - d\t- proprio : %s - %d - %d\n",tmpD->sousDirect[i],tmpU->nom,tmpI->droitU,tmpI->droitA);
			}
			else
				printf("%s - f - %d octets\t- proprio : %s - %d - %d\n",tmpD->sousDirect[i],tailleFichier(sb,argInode),tmpU->nom,tmpI->droitU,tmpI->droitA);
			
		}
	}
	printf("\n");	
}

int tailleFichier(superBlock *sb, int argInode){ //trouve la taille en octet d'un fichier
	int taille=0;
	blockF *tmpF = noInodeToBlockF(sb,argInode);
	while(tmpF!=NULL){
		taille+=8;
		tmpF=tmpF->nextF;
	}
	return taille;
}
