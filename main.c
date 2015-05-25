#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

int main(){

	superBlock *sb = initSGF();
	//printf("%s\n",sb->blocksD->nom);
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	creerFicher(sb,1,"testDeFichier");
	
	toStringBlockD(sb->blocksD);
	
    supprDir(sb,2);
	toStringBlockD(sb->blocksD);
	creaDir(sb,1,"test3");
	toStringBlockD(sb->blocksD);
	
	supprFichier(sb,4,1);
	toStringBlockD(sb->blocksD);
	toStringInode(sb);
	return 0;
}
