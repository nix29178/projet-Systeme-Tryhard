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
	//ln(sb,2,1,"testLien");
	printf("fichier créé\n");
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
