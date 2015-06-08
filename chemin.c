#include "blocks.h"
#include <string.h>

int inodeCheminAbsolu(superBlock *sb, char *chemin){ //retourne l'inode avec chemin absolu (erreur : 0)
	if(chemin[0]!='/'){ //on verifie que le chemin commence bien par un /
		return 0;
	}
	else{
		blockD *tmpD = noInodeToBlockD(sb,1);
		int i,j,k,total,ok;
		char *tmpString=malloc(sizeof(char));
		ok=0;
		i=1;
		j=0;
		k=0;
		total = strlen(chemin);
		
		while(ok==0){
		while(chemin[j+i]!='/' && j+i<total){ //on compte le nombre de caractères ;
			j++;
		}
		tmpString = realloc(tmpString,sizeof(char)*j);
		for(k=0; k<j;k++){
			tmpString[k]=chemin[i+k]; //on met le nom dans une variables
		}
		for(k=2;k<20;k++){
			if(tmpD->inodes[k]!=0 && strcmp(tmpD->sousDirect[k],tmpString)==0){ //on compare avec le contenu du dossier en cours	
				ok=1;
				break;
			}
		}
	
		if(ok==0){ //nom non trouvé on renvoie faux
			return 0;
		}
		else if(j+i==total){ //nom trouvé et fin de la chaine de caractère on renvoie vrai
			return tmpD->inodes[k];
		}
		else{
			ok=0; 
			if(noInodeToInode(sb,tmpD->inodes[k])->typeBlock==0){// nom trouvé mais pas fini on continu
				tmpD=noInodeToBlockD(sb, tmpD->inodes[k]);
				i=j+2;
				j=0;
			}
			else{
				return 0; //cas ou on tombe sur un fichier confondu avec un repertoire
			}
		}
		}				
	}
		
}
