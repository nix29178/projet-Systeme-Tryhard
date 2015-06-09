#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"
#include "touch.c"
#include "cat.c"
#include "ls.c"
#include "chemin.c"
#include "rm.c"
#include <string.h>

char* recupArgs(){
	int i =0;
	int longueur=0;
	char buffer[250];
	char* arguments;
	fgets(buffer, 249, stdin);
	while(buffer[i]!='\0'){
		if(buffer[i]=='\n'){
			buffer[i]='\n';
		break;
		}
	i++;
	}

	longueur=strlen(buffer);
	arguments=malloc(longueur*sizeof(char));
	strcpy(arguments,buffer);
	
	return arguments;
}

char** recupTabArgs(char* Arguments){
	
	int i,j,k,x,total,ok;
	char ** TabArgs;
	ok=0;
	i=0;
	j=0;
	k=0;
	x=0;

	total = strlen(Arguments);
	if(Arguments[0]==' '){ //on verifie que l'argument ne commence pas par un " "
			printf("Erreur 444 la commande commence par un espace");
		return 0;
	}
	else{
		for(i=0;i<total;i++){ //on compte le nombre de d'espace ;
			if(Arguments[i]==' ' || Arguments[i]=='\n')
				j++;
		}
		TabArgs = malloc(sizeof(char*)*(j+1)); //initialisation de l'epace pour le nombre de chaine de char
		i=0;
		j=0;
		k=0;
		while((i)<total){
			while(Arguments[i+j]!=' '&& j+i<total && Arguments[i+j]!='\n'){
				j++;
			}
			TabArgs[k]=malloc(j*sizeof(char)); //initialisation pour charque chaine de char
			for(x=0;x<j;x++){
			TabArgs[k][x]=Arguments[i+x]; // remplissage du tableau avec les arguments
			}
			k++;
			i=i+j+1;
			j=0;
		}
	}	
	return TabArgs	;			
}

char** InitTabfonction(){

	char ** TabFonction;
	int nbfonction=4;
	int i=0;
	TabFonction = malloc(sizeof(char*)*(nbfonction)); //initialisation de l'epace pour le nombre de chaine de char

	for(i=0;i<nbfonction;i++){
		switch(i){
			case 0:
			TabFonction[i]=malloc(strlen("touch")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"touch"); // remplissage du tableau avec les fonctions	
			break;
	
			case 1:
			TabFonction[i]=malloc(strlen("cat")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"cat"); // remplissage du tableau avec les fonctions	
			break;

			case 2:
			TabFonction[i]=malloc(strlen("ls")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"ls"); // remplissage du tableau avec les fonctions	
			break;

			case 3:
			TabFonction[i]=malloc(strlen("rm")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"rm"); // remplissage du tableau avec les fonctions	
			break;	
		}
	}
	return TabFonction;			
}

void action(char** TabArgs,char** TabFonction,superBlock *sb, int argInode){
	int i,NbInstruction=-1,nbfonction=4;

	for(i=0;i<nbfonction;i++){
		if(strcmp(TabArgs[0],TabFonction[i])==0)
			NbInstruction=i;
			}

	switch(NbInstruction){
		case 0://touch
		touch(sb,argInode,TabArgs[1]);
		modifContenu(sb,chemin(sb,argInode,TabArgs[1]),"cosmin<3");
		break;

		case 1://cat

		cat(sb,chemin(sb,argInode,TabArgs[1]));
		
		break;
		
		case 2://ls
	
		ls(sb,argInode);		

		break;

		case 3://rm

		rmdir(sb,chemin(sb,argInode,TabArgs[1]));
		break;	
default:
break;
		}
		

}

int main(void){

	superBlock *sb = initSGF();
	char * arguments;
	char ** TabArgs;
	char ** TabFonction;
	int i,nbfonction=4;
	int dossiercurrent=1;
	
	
	TabFonction=InitTabfonction();
	for(i=0;i<nbfonction;i++)

	while (1){
	arguments = recupArgs();
	TabArgs=recupTabArgs(arguments);
	action(TabArgs,TabFonction,sb,dossiercurrent);
	free(TabArgs);
	}
	
	

//"touch.c"
//"cat.c"
// "ls.c"
//"rm.c"


	return 0;
}
