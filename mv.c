#include "blocks.h"

int mv(superBlock *sb,int dossieract, int inodeBase, int inodeDossier, char *nom, int userCo){
	if(verifDroit(sb,inodeDossier,userCo,2)==0 || verifDroit(sb,inodeBase,userCo,1)==0){
		printf("Action interdite\n");
	    return 0;
	}
	inode *base = noInodeToInode(sb, inodeBase);
	if(base->typeBlock!=1){
		printf("impossible de faire un mv sur un dossier\n");
		return 0;
	}
	int i=2,ok=0;
	if(noInodeToInode(sb, inodeDossier)->typeBlock!=0){
		printf("impossible de créer le lien ici\n");
		return 0;
	}
	blockD *tmpD = noInodeToBlockD(sb, inodeDossier);
	
	for(i;i<20;i++){
		if(tmpD->inodes[i]!=0 && strcmp(tmpD->sousDirect[i], nom)==0){
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
	tmpD->sousDirect[i]=nom;
	unlink(sb, inodeBase,dossieract, userCo);
	return tmpI->noInode;
}
