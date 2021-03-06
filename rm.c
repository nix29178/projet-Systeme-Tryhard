#include "blocks.h"

int rmdir(superBlock *sb, int argInode, int userCo){
	if(verifDroit(sb,argInode,userCo,2)==0){
		printf("action interdite\n");
		return 0;
	}
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

int unlink(superBlock *sb, int argInode, int parent,int userCo){
	int type = noInodeToInode(sb, argInode)->typeBlock;
	if(verifDroit(sb,argInode,userCo,2)==0){
		printf("action interdite\n");
		return 0;
	}
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
