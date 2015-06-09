#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"
#include "touch.c"
#include "cat.c"
#include "ls.c"
#include "chemin.c"
#include "rm.c"
#include <string.h>


int main(){
	superBlock *sb = initSGF();
	creaDir(sb,1,"test1");
	creaDir(sb,2,"a");
	creaDir(sb,3,"test3");
	//creaDir(sb,1,"test3");
	//touch(sb,1,"testDeFichier");
	//modifContenu(sb,4,"coucou Félicien comment ca va la famille ?\n");
	//cat(sb,4);
	//ls(sb,1);
	//rmdir(sb,3);
	//toStringBlockD(sb, 2);
	int res = chemin(sb, 1, "test1/a/test3");
	printf("res : %d\n",res);
	
	return 0;
}
