#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"
#include "touch.c"
#include "cat.c"
#include "ls.c"
#include "chemin.c"
#include "rm.c"
#include "ln.c"
#include <string.h>


int main(){
	superBlock *sb = initSGF();
	touch(sb,1, "test");
	modifContenu(sb,2,"Coucoucou beaucoup de test toussa\n");
	char * coucou=lireFichier(sb,2);
	printf("%s\n",coucou);
	printf("nb inode : %d / %d\nnb blockF : %d / %d",sb->nbBlockI, sb->maxBlockI,sb->nbBlockF, sb->maxBlockF);
	//ln(sb,2,1,"testLien");
	//creaDir(sb,1,"test3");
	//touch(sb,1,"testDeFichier");
	//modifContenu(sb,4,"coucou Félicien comment ca va la famille ?\n");
	//cat(sb,4);
	//ls(sb,1);
	rmfile(sb,2,1);
	toStringBlockD(sb, 1);
	toStringBlocksF(sb);
	//int res = chemin(sb, 1, "test1/a/test3");
	//printf("res : %d\n",res);
	
	return 0;
}
