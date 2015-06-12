#include "blocks.h"

void ls(superBlock *sb, int argInode){
    blockD *tmpD = noInodeToBlockD(sb, argInode);
    inode *tmpI;
    user *tmpU;
    char type;
    int i;
    for(i=2; i<20;i++){
		if(tmpD->inodes[i]!=0 ){
			tmpI=noInodeToInode(sb, tmpD->inodes[i]);
			tmpU=noUserToUser(sb, tmpI->proprio);
			if(tmpI->typeBlock==0)
				type='d';
			else
				type='f';
			printf("%s - %c\t- proprio : %s - %d - %d\n",tmpD->sousDirect[i],type,tmpU->nom,tmpI->droitU,tmpI->droitA);
		}
	}
	printf("\n");	
}
