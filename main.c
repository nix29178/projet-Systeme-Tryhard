#include <stdio.h>
#include "inodes.h"

int main(){

	dossier *racine = initSGF();
	printf("%s\n",racine->nom);
	creerSousDossier(racine, "test");
	creerSousDossier(racine, "test2");
	creerSousDossier(racine, "test3");
	creerFichierVide(racine, "testDeFichier");
	afficherContenuD(racine);

	return 0;
}
