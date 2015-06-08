#include "blocks.h"

int rmdir(superBlock *sb, int argInode){
	int type = noInodeToInode(sb, argInode)->typeBlock;
	if(argInode==1){
		printf("vous ne pouvez pas supprimer la racine\n");
		return 0;
	}
	if(type==2){
		printf("erreur fatale\n");
		exit(2);
	}
	else if(type==1){
		printf("ce n'est pas un répertoire\n");
		return 0;
	}
	else if(type==0){
		int ok=1,i;
		blockD *tmpD=noInodeToBlockD(sb, argInode);
		for(i=2;i<20;i++){
			if(tmpD->inodes[i]!=0){
				ok=0;
			}
		}
		if(ok==1){
			supprDir(sb,argInode);
			return 1;
		}
		else{
			printf("dossier non vide\n");
			return 0;
		}
	}
}

int rmfile(superBlock *sb, int argInode, int parent){
	int type = noInodeToInode(sb, argInode)->typeBlock;
	if(type==2){
		printf("erreur fatale\n");
		exit(2);
	}
	else if(type==0){
		printf("ce n'est pas un fichier\n");
		return 0;
	}
	else if(type==1){
		supprFichier(sb,argInode,parent);
	}
}
