#include "blocks.h"
#include <string.h>

int validAbsolut(superBlock *sb, char *chemin){ //verifie qu'un chemin absolu existe (0 pour faux 1 pour vrai)
	if(chemin[0]!='/'){ //on verifie que le chemin commence bien par un /
		return 0;
	}
	else{
		blockD *tmpD = noInodeToBlockD(sb,1);
		int i,j,k,total,ok;
		char *tmpString;
		ok=0;
		i=1;
		j=0;
		k=0;
		total = strlen(chemin);
		while(ok==0){
		while(chemin[j+i]!='/' && j<total){ //on compte le nombre de caractères 
			j++;
		}
		tmpString = malloc(sizeof(char)*(j-i));
		for(k=0; k<j;k++){
			tmpString[k]=chemin[i+k]; //on met le nom dans une variables
		}
		for(k=2;k<20;k++){
			if(strcmp(tmpD->sousDirect[k],tmpString)==0){ //on compare avec le contenu du dossier en cours
				ok=1;
				break;
			}
		}
		
		if(ok==0){ //nom non trouvé on renvoie faux
			return 0;
		}
		else if(j==total){ //nom trouvé et fin de la chaine de caractère on renvoie vrai
			return 1;
		}
		else{
			ok=0; 
			if(noInodeToInode(sb,tmpD->inodes[k])->typeBlock==0){// nom trouvé mais pas fini on continu)
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
