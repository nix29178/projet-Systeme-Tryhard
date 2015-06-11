#include "blocks.h"

int mkdir(superBlock *sb, int InodeParent, char *nomDossier, int userCo)
{
	if(verifDroit(sb,InodeParent,userCo,2)==0){
		printf("action interdite\n");
		return 0;
	}
	inode* ino = noInodeToInode(sb,InodeParent);
	int ok=0,Inode=0,nom=1,i=0;

	if(ino->typeBlock==0)
	{
		blockD*d=noInodeToBlockD(sb,InodeParent);
		
		for(i=0;i<20;i++)
		{
			if(d->inodes[i]!=0 && strcmp(d->sousDirect[i],nomDossier)==0)
			{
				nom=0;
			}
			
		}
		
		for(i=0;i<20;i++)
		{
			if(d->inodes[i]!=0)
			{
				ok=0;
			}
			else
			{
				ok=1;
				break;
			}
		}
		 
		if(ok==1 && nom==1)
		{
			creaDir(sb,InodeParent,nomDossier);
		}
		else if(ok==0)
		{
			printf("Le dossier est plein ! Supprimez des fichiers ou dossiers \n");
		}
		else if(nom==0)
		{
			printf("Il existe déjà un dossier ou fichier ayant ce nom\n");
		}
	else
	{
		printf("Ce n'est pas l'inode d'un dossier\n");
	}
}
return 0;
}
			
		
	
