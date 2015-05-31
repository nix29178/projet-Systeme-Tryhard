#include "blocks.h"

void cat(superBlock *sb, int argInode){
	printf("%s\n",lireFichier(sb, argInode));
}
