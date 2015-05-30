#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"
#include "touch.c"
#include <string.h>


int main(){
	superBlock *sb = initSGF();
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	//creerFicher(sb,1,"testDeFichier");
	touch(sb,1,"testDeFichier");
	touch(sb,1,"testDeFichier");
	
	return 0;
}
