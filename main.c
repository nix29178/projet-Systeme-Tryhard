#include <stdio.h>
#include "blocks.h"

int main(){

	superBlock *sb = initSGF();
	//printf("%s\n",sb->blocksD->nom);
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	creerFicher(sb,1,"testDeFichier");
	
	toStringBlockD(sb->blocksD);

	return 0;
}
