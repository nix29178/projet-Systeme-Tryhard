#include "blocks.h"

void touch(superBlock *sb, int argInode, char *nomFichier){
	 
	 blockD *tmpD=noInodeToBlockD(sb,argInode);
	 int ok=1,i=2,vide=0;
	 for(i;i<20;i++){
		 if(tmpD->inodes[i]!=0 && strcmp(nomFichier, tmpD->sousDirect[i])==0){
			 ok=0;
			 break;
		 }
	 }
	 for(i=2;i<20;i++){
		if(tmpD->inodes[i]==0){
			vide=i;
			break;
		}
	 }
	 if(vide==0){
		printf("dossier plein\n");
	 }
	 else if(ok==0){
		 printf("un fichier ou dossier avec ce nom existe deja\n");
     }
     else{
	     creerFicher(sb, argInode, nomFichier);
	     printf("fichier %s créé\n",nomFichier);
	 }
}
