#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"


int main(){
	superBlock *sb = initSGF();
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	creerFicher(sb,1,"testDeFichier");
	
	modifContenu(sb,4, "Bonjour je m'appelle Nicolas Le Bourhis et j'atteste que Cosmin est le +++ beau gosse de la terre");
	char *test = lireFichier(sb,4);
	printf("\naffichage variable : ---- %s\n",test);
	
	return 0;
}
