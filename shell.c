#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"
#include "user.c"
#include "touch.c"
#include "cat.c"
#include "ls.c"
#include "chemin.c"
#include "rm.c"
#include <string.h>
#include "mkdir.c"
#include "cd.c"


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
			if(Arguments[i]==' ' || Arguments[i]=='\n' )
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

char** InitTabfonction(int nbfonction){

	char ** TabFonction;
	
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
			TabFonction[i]=malloc(strlen("unlink")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"unlink"); // remplissage du tableau avec les fonctions	
			break;	
			case 4:
			TabFonction[i]=malloc(strlen("mkdir")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"mkdir"); // remplissage du tableau avec les fonctions	
			break;	
			case 5:
			TabFonction[i]=malloc(strlen("cd")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"cd"); // remplissage du tableau avec les fonctions	
			break;
			case 6:
			TabFonction[i]=malloc(strlen("newU")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"newU"); // remplissage du tableau avec les fonctions	
			break;
			case 7:
			TabFonction[i]=malloc(strlen("changeU")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"changeU"); // remplissage du tableau avec les fonctions	
			break;
			case 8:
			TabFonction[i]=malloc(strlen("tableU")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"tableU"); // remplissage du tableau avec les fonctions	
			break;
			case 9:
			TabFonction[i]=malloc(strlen("chmod")*sizeof(char)); //initialisation pour charque chaine de char
			strcpy(TabFonction[i],"chmod"); // remplissage du tableau avec les fonctions	
			break;
		}
	}
	return TabFonction;			
}

int action(char** TabArgs,char** TabFonction,superBlock *sb, int *argInode,int nbfonction, int *userCo){
	int i,NbInstruction=-1;

	for(i=0;i<nbfonction;i++){
		if(strcmp(TabArgs[0],TabFonction[i])==0)
			NbInstruction=i;
			}

	switch(NbInstruction){
		case 0://touch
		touch(sb,*argInode,TabArgs[1],*userCo);
		
		break;

		case 1://cat

		cat(sb,chemin(sb,*argInode,TabArgs[1]));
		
		break;
		
		case 2://ls
	
		ls(sb,*argInode);		

		break;

		case 3://rm

		unlink(sb,chemin(sb,*argInode, TabArgs[1]),*argInode,*userCo);
		break;	
		case 4://mkdir

		mkdir(sb,*argInode,TabArgs[1],*userCo);
		break;	
		case 5://cd
		if(cd(sb,*argInode,TabArgs[1])!=0)
			*argInode=cd(sb,*argInode,TabArgs[1]); 
		break;
		case 6://newU
		if(TabArgs[1]!=NULL && TabArgs[2]!=NULL)
		    newUser(sb,TabArgs[1], TabArgs[2]); 
		break;
		case 7://changeU
		if(TabArgs[1]!=NULL && TabArgs[2]!=NULL){
		    int res =connexion(sb,TabArgs[1], TabArgs[2]); 
		    if(res !=-1){
				*userCo=res;
			}
		}
		break;
		case 8://tableU
		    tableUser(sb,*userCo);
		break;
		case 9://chmod
			if(TabArgs[1]!=NULL && TabArgs[2]!= NULL && TabArgs[3]!= NULL)
				chmod(sb,chemin(sb,*argInode,TabArgs[3]), *userCo,atoi(TabArgs[1]), atoi(TabArgs[2]));
		break;
default:
printf("action non reconnue\n");
break;
	
		}
		
	return 1;
}

int main(void){

	superBlock *sb = initSGF();
	char * arguments;
	char ** TabArgs;
	char ** TabFonction;
	int i,nbfonction=9;
	int dossiercurrent=1;
	int userCo=connectInterface(sb), ok=0;
	
	
	TabFonction=InitTabfonction(nbfonction);
	for(i=0;i<nbfonction;i++)
		printf(" %s\n",TabFonction[i]);

	while (1){
	printf("%s:~%s$",noUserToUser(sb, userCo)->nom,cheminActuel(sb,dossiercurrent));
	arguments = recupArgs();
	TabArgs=recupTabArgs(arguments);
	action(TabArgs,TabFonction,sb,&dossiercurrent,nbfonction,&userCo);
		
	free(TabArgs);
	}
	
	

//"touch.c"
//"cat.c"
// "ls.c"
//"rm.c"


	return 0;
}

int connectInterface(superBlock *sb){
	int num,ok=0;
	system("clear");
	printf("------------------------------------------\n");
	printf("--- SGF Divry-Le Bourhis-Mandoc-Migeot ---\n");
	printf("------------------------------------------\n\n");
	while(ok==0){
		char **res;
		printf("qui etes vous ? ");
		res=recupTabArgs(recupArgs());
		char *nom = res[0];
		printf("mot de passe ? ");
		res=recupTabArgs(recupArgs());
		char *mdp = res[0];
		num =connexion(sb,nom,mdp);
		if(num !=-1)
			ok=1;
	}
	return num;
}
