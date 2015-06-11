#include "blocks.h"

int cd(superBlock *sb, int inodeAct, char * dest){
	
	int inodeDest = chemin(sb,inodeAct,dest);
	if(noInodeToInode(sb, inodeDest)->typeBlock!=0){
		printf("cd impossible sur un fichier\n");
		return inodeAct;
	}
	else{
		return inodeDest;
	}
}


