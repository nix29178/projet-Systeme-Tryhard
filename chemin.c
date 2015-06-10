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

int chemin(superBlock *sb, int dossierAct, char *chemin){
		blockD *tmpD = noInodeToBlockD(sb,dossierAct);
		int i,j,k,total,ok;
		char *tmpString=malloc(sizeof(char));
		ok=0;
		i=0;
		j=0;
		k=0;
		total = strlen(chemin);
		
		while(ok==0){
		while(chemin[j+i]!='/' && j+i<=total){ //on compte le nombre de caractères ;
			j++;
		}
		tmpString = malloc(sizeof(char)*j);
		for(k=0; k<j;k++){
			tmpString[k]=chemin[i+k]; //on met le nom dans une variables
		}
		for(k=0;k<20;k++){
			if(tmpD->inodes[k]!=0 && strcmp(tmpD->sousDirect[k],tmpString)==0){ //on compare avec le contenu du dossier en cours	
				ok=1;
				break;
			}
		}
	
		if(ok==0){ //nom non trouvé on renvoie faux
			return 0;
		}
		else if(j+i>=total){ //nom trouvé et fin de la chaine de caractère on renvoie vrai
			return tmpD->inodes[k];
		}
		else{
			ok=0; 
			if(noInodeToInode(sb,tmpD->inodes[k])->typeBlock==0){// nom trouvé mais pas fini on continu
				tmpD=noInodeToBlockD(sb, tmpD->inodes[k]);
				i=i+j+1;
				j=0;
				//free(tmpString);
			}
			else{
				return 0; //cas ou on tombe sur un fichier confondu avec un repertoire
			}
		}	
}
}

char *cheminActuel(superBlock *sb, int argInode){
	
	if(noInodeToInode(sb, argInode)->typeBlock!=0){
		printf("erreur\n");
		return "!!";
	}
	blockD *tmpD = noInodeToBlockD(sb, argInode);
	int profondeur=0;
	while(tmpD->inodes[0]!=1){
		profondeur ++;
		tmpD=noInodeToBlockD(sb,tmpD->inodes[1]);
	}
	if(profondeur ==0){
		return "/";
	}
	else{
		char *tab[profondeur];
		tmpD = noInodeToBlockD(sb, argInode);
		tmpD=noInodeToBlockD(sb, tmpD->inodes[1]);
		int i=profondeur-1,j,enCours=argInode;
		int taille=0;
		for(i;i>=0;i--){
			j=2;
			while(tmpD->inodes[j]!=enCours)
				j++;
			tab[i]=tmpD->sousDirect[j];
			taille += strlen(tmpD->sousDirect[j]);
			enCours=tmpD->inodes[0];
			tmpD=noInodeToBlockD(sb,tmpD->inodes[1]);
		}
		char *res = malloc(sizeof(char)*(taille+profondeur-1));
		res[0]='/';
		i=0;j=0;
		int encours=1;
		for(i;i<profondeur;i++){
			for(j=0;j<strlen(tab[i]);j++){
				res[encours]=tab[i][j];
				encours++;
			}
			if(encours!=taille+profondeur){
				res[encours] ='/';
				encours++;
			}
		}
		return res;
	}
	
}
