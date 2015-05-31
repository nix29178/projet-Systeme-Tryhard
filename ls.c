#include "blocks.h"

void ls(superBlock *sb, int argInode){
    blockD *tmpD = noInodeToBlockD(sb, argInode);
    int i;
    for(i=0; i<20;i++){
		if(tmpD->inodes[i]!=0){
			printf("%s   ",tmpD->sousDirect[i]);
		}
	}
	printf("\n");	
}
