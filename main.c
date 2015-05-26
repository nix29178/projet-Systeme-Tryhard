#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"


int main(){
	superBlock *sb = initSGF();
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	creerFicher(sb,1,"testDeFichier");
	creerFicher(sb,1,"testDeFichier2");
	
	modifContenu(sb,4, "Bonjour je m'appelle Nicolas Le Bourhis et j'atteste que Cosmin est le +++ beau gosse de la terre");
	//char *test = lireFichier(sb,4);
	//printf("%s\n",test);
	creerFicher(sb,1,"testDeFichier3");
	supprFichier(sb, 4,1);
	modifContenu(sb,5, "azertyaz dzaza azd az azdazdazd");
	creaDir(sb,1,"testDirMille");
	int i;
	for(i=0;i<19;i++)
	    creerFicher(sb,1,"a");
	toStringBlocksF(sb);
	toStringInode(sb);
	toStringBlockD(sb,1);
	
	return 0;
}
