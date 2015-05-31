#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"
#include "touch.c"
#include "cat.c"
#include "ls.c"
#include <string.h>


int main(){
	superBlock *sb = initSGF();
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	//creerFicher(sb,1,"testDeFichier");
	touch(sb,1,"testDeFichier");
	modifContenu(sb,4,"coucou Félicien comment ca va la famille ?\n");
	cat(sb,4);
	ls(sb,1);
	
	return 0;
}
