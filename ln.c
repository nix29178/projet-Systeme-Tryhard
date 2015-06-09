#include "blocks.h"

int ln(superBlock *sb, int inodeBase, int dossier, char *nomlien){ //fait un ln et retourne l'inode du lien (0 en cas d'erreur)
	inode *base = noInodeToInode(sb, inodebase);
	if(base->typeBlock!=1){
		printf("impossible de faire un ln sur un dossier\n");
		return 0;
	}
	int i=2,ok=0;
	if(noInodeToInode(sb, dossier)->typeBlock!=0){
		printf("impossible de créer le lien ici\n");
		return 0;
	}
	blockD *dossier = noInodeToBlockD(sb, dossier);
	for(i;i<20;i++){
		if(tmpD->inodes[i]==0){
			ok=1;
		}
		if(strcmp(tmpD->sousDirect[i], nomlien)==0){
			printf("nom deja pris\n");
			return 0;
		}
	}
	if(ok==0){
		printf("Dossier plein");
		return 0;
	}
	inode *tmpI = inodeLibre(sb->inodes);
	tmpI->typeBlock=1;
	tmpI->block=base->block; //on créé l'inode
	tmpD->inodes[i]=tmpI->noInode;
	tmpD->sousDirect[i]=nomlien;
	return tmpI->noInode;
	
}
