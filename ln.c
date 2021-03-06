#include "blocks.h"

int ln(superBlock *sb, int inodeBase, int dossier, char *nomlien, int userCo){ //fait un ln et retourne l'inode du lien (0 en cas d'erreur)
	if(verifDroit(sb,dossier,userCo,2)==0 || verifDroit(sb,inodeBase,userCo,1)==0){
		printf("Action interdite\n");
	    return 0;
	}
	inode *base = noInodeToInode(sb, inodeBase);
	if(base->typeBlock!=1){
		printf("impossible de faire un ln sur un dossier\n");
		return 0;
	}
	int i=2,ok=0;
	if(noInodeToInode(sb, dossier)->typeBlock!=0){
		printf("impossible de créer le lien ici\n");
		return 0;
	}
	blockD *tmpD = noInodeToBlockD(sb, dossier);
	
	for(i;i<20;i++){
		if(tmpD->inodes[i]!=0 && strcmp(tmpD->sousDirect[i], nomlien)==0){
			printf("nom deja pris\n");
			return 0;
		}
	}
	for(i=2;i<20;i++){
		if(tmpD->inodes[i]==0){
			ok=1;
			break;
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
