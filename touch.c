#include "blocks.h"

int touch(superBlock *sb, int argInode, char *nomFichier, int userCo){
	 
	 blockD *tmpD=noInodeToBlockD(sb,argInode);
	 inode *tmpI=noInodeToInode(sb,argInode);
	 if(userCo!=0 || userCo==tmpI->proprio && (tmpI->droitU==1) || 
					userCo!=tmpI->proprio && (tmpI->droitA==1)){
		
		printf("action interdite\n");
		return -1;				
	 }
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
		return 0;
	 }
	 else if(ok==0){
		 printf("un fichier ou dossier avec ce nom existe deja\n");
		 return 0;
     }
     else{
	     creerFicher(sb, argInode, nomFichier);
	     printf("fichier %s créé\n",nomFichier);
	     return 1;
	 }
}
