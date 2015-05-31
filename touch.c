#include "blocks.h"

void touch(superBlock *sb, int argInode, char *nomFichier){
	 
	 blockD *tmpD=noInodeToBlockD(sb,argInode);
	 int ok=1,i=2;
	 while(ok==1 && tmpD->inodes[i]!=0){
		 if(strcmp(nomFichier, tmpD->sousDirect[i])==0){
			 ok=0;
		 }
		 i++;
	 }
	 if(i==20){
		printf("dossier plein\n");
	 }
	 else if(ok==1){
	     creerFicher(sb, argInode, nomFichier);
	     printf("fichier %s créé\n",nomFichier);
	 }
	 else{
		 printf("un fichier ou dossier avec ce nom existe deja\n");
     }
}
