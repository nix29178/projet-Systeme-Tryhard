#include "blocks.h"

int df(superBlock *sb){

	printf("Inodes alloués : %d/%d\n",sb->nbBlockI,sb->maxBlockI);
	printf("BlockF alloués : %d/%d\n",sb->nbBlockF,sb->maxBlockF);
	printf("BlockD alloués : %d/%d\n",sb->nbBlockD,sb->maxBlockD);
}
