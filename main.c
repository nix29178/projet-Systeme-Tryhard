#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

void test(char *arg){
	int taille =strlen(arg);
	printf("%d\n",taille);
	int i=1;
	printf("[");
	printf("%c",arg[0]);
	
	while(i<taille){
		if(i%8==0){
			printf("]");
			printf("[");
		}
		printf("%c",arg[i]);
		i++;		
	}
	printf("]\n");
}

int main(){
	char * pute= "12345678 9abcd efg123456'789";
    //test(pute);
	superBlock *sb = initSGF();
	creaDir(sb,1,"test1");
	creaDir(sb,1,"test2");
	creerFicher(sb,1,"testDeFichier");
	creerFicher(sb,1,"testDeFichier2");
	
	modifContenu(sb,4, "Bonjour je m'appelle Nicolas Le Bourhis et j'atteste que Cosmin est le +++ beau gosse de la terre");
	char *test = lireFichier(sb,4);
	//printf("%s\n",test);
	//toStringBlocksF(sb);
	
	return 0;
}
