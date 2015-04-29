#include <stdio.h>
#include <stdlib.h>
#include "blocks.h"

superBlock *initSGF(){
	//initialisation du super block
	superBlock *tmp = malloc(sizeof(superBlock));
	
	//initialisation de la table d'inodes avec la racine
	tmp->inodes = initInode(1,0,1);
	
	//initialisation de la racine
	tmp->blocksD = initDirec(1,1,1);
	
	//initilisation des blocks Fichier
	tmp->blocksF = initBlockFvide(1,1);
	return tmp;   
}

inode *initInode(int argInode, int argType, int argBlock){
	
	inode *tmp = malloc(sizeof(inode));
	tmp->noInode=argInode;
	tmp->typeBlock=argType;
	tmp->block=argBlock;
	tmp->next=NULL;
	return tmp;
}

blockD *initDirec(int inodeDirect, int inodePapa, int argBlock){
	
	blockD *tmp=malloc(sizeof(blockD));
	tmp->noBlockD=argBlock;
	tmp->sousDirect[0]=".";
	tmp->sousDirect[1]="..";
	tmp->inodes[0] = inodeDirect;
	tmp->inodes[1] = inodePapa;
	int i;
	for(i=2;i<255;i++){
		tmp->inodes[i]=0;
	}
	tmp->next=NULL;
	return tmp;
}

blockF *initBlockFvide(int inodeF, int argBlock){
	
	blockF *tmp =malloc(sizeof(blockF));
	tmp->noInode=inodeF;
	tmp->noBlockF=argBlock;
	int i;
	for(i=0; i<8; i++){
		tmp->contenu[i]=NULL;
	}
	tmp->nextBlock=NULL;
	tmp->nextF=NULL;
	return tmp;
}

inode *inodeLibre(inode *inodes){//cherche un inode de libre si n'existe pas en créé un
	
    inode *tmp=inodes;
    while(tmp->typeBlock!=2 && tmp->next!=NULL){
		tmp = tmp->next;
	}
	if(tmp->next!=NULL){
		return tmp;
	}
	else{
		tmp->next=initInode(tmp->noInode+1, 2, 0);
		return tmp->next;
	}
}

blockD *blockDLibre(blockD *blocksD){ // cherche un block directory libre si n'existe pas en créé un 
    blockD *tmp=blocksD;
    while(tmp->inodes[0]!=0 && tmp->next!=NULL){
		tmp = tmp->next;
	}
	if(tmp->next!=NULL){
		return tmp;
	}
	else{
		tmp->next=initDirec(0,0,tmp->noBlockD+1);
		return tmp->next;
	}	
}

void toStringBlockD(blockD *block){

	printf("inode du block : %d\n",block->noInode);
	int i=0;
	while(block->inodes[i]!=0){
		printf("%s    -    %d\n",block->sousDirect[i],block->inodes[i]);
		i++;
	}
}

void creaDir(superBlock *sb, blockD *parent, char *nomDir){
	
	int noInode, noBlock;
	inode *placeInode = inodeLibre(sb->inodes);
	noInode = placeInode->noInode;
	
	blockD *placeBlock = blockDLibre(sb->blocksD);
	noBlock = placeBlock->noBlockD;
	
	placeInode->block=noBlock;
	placeBlock->noInode=noInode;
	placeBlock->inodes[0]=noInode;
	placeBlock->inodes[1]=parent->noInode;
	
	int i=2;
	while(parent->inodes[i]!=0){
		i++;
	}
	parent->inodes[i]=noInode;
	parent->sousDirect[i]=nomDir;
	
}
