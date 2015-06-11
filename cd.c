#include "blocks.h"

int cd(superBlock *sb, int inodeAct, char * dest, int userCo){
	
	int inodeDest = chemin(sb,inodeAct,dest);
	if(verifDroit(sb, inodeDest, userCo, 1)==0){
		printf("action interdite\n");
		return inodeAct;
	}
	if(noInodeToInode(sb, inodeDest)->typeBlock!=0){
		printf("cd impossible sur un fichier\n");
		return inodeAct;
	}
	else{
		return inodeDest;
	}
}


