#include "blocks.h"

void cp(superBlock *sb, int InodeFichier, char *nomNouveauFichier,int InodeNouveauDossier,int userCo)
{
	inode* ino = noInodeToInode(sb,InodeFichier);
	int ok=0,InodeNouveauFichier=0,i=0;
	
		if(ino->typeBlock==1)
	{
		if(verifDroit(sb,InodeFichier, userCo, 1)==1 && verifDroit(sb,InodeNouveauDossier, userCo, 2)==1){
					char *cont;  
					cont = lireFichier(sb,InodeFichier);
					blockD*TempD=noInodeToBlockD(sb,InodeNouveauDossier);
					
					for(i=0;i<20;i++)
					{
						if(TempD->inodes[i]!=0)
						{
							ok=0;
						}
						else
						{
							ok=1;
							break;
						}
					}
				if(ok=1)
				{
					InodeNouveauFichier=creerFicher(sb,InodeNouveauDossier,nomNouveauFichier);
					modifContenu(sb,InodeNouveauFichier,cont);
				}
				else if(ok==0)
				{
					printf("Le dossier dans lequel vous voulez copier est plein \n");
				}
			}
			else{
				printf("Action interdite\n");
			}
		}
		else
		{
			printf("Vous essayez de copier autre chose qu'un fichier\n");
		}
	}
		
		
			
		
