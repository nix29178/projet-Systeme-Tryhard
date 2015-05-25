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
	tmp->blocksF = initBlockFvide(0);
	tmp->blocksF->noBlockF=1;
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
	tmp->noInode=inodeDirect;
	tmp->inodes[0] = inodeDirect;
	tmp->inodes[1] = inodePapa;
	int i;
	for(i=2;i<20;i++){
		tmp->inodes[i]=0;
	}
	tmp->next=NULL;
	return tmp;
}

blockF *initBlockFvide(int inodeF){ //initialiste un blockF sans noBlock attribué et used a 0
	
	blockF *tmp =malloc(sizeof(blockF));
	tmp->noInode=inodeF;
	tmp->noBlockF=0;
	tmp->used=0;
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
	if(tmp->typeBlock==2){
		//printf("inode recycle no %d\n",tmp->noInode);
		return tmp;
	}
	else{
		tmp->next=initInode(tmp->noInode+1, 2, 0);
		//printf("nouveau inode no %d\n",tmp->next->noInode);
		return tmp->next;
	}
	
}

blockF *blockFLibre(blockF *blocksF){
    blockF *tmp = blocksF;
    while(tmp->used!=0 || tmp->nextBlock!=NULL){
		tmp=tmp->nextBlock;
	}
	if(tmp->used==0){
		return tmp;
	}
	else{
		tmp->nextBlock=initBlockFvide(0);
		tmp->nextBlock->noBlockF=tmp->noBlockF+1;
		return tmp->nextBlock;
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
	for(i=0;i<20;i++){
		if(block->inodes[i]!=0){
		printf("%s    -    %d\n",block->sousDirect[i],block->inodes[i]);
		}
	}
}
void toStringInode(superBlock *sb){
	inode *tmpI=sb->inodes;
	printf("----------TABLE INODES -----------\n");
	while(tmpI!=NULL){
		printf("inode %d, type %d, block %d\n",tmpI->noInode, tmpI->typeBlock, tmpI->block);
		tmpI=tmpI->next;
	}
	
}

void creaDir(superBlock *sb, int noInodeParent, char *nomDir){
	
	blockD *parent = noInodeToBlockD(sb, noInodeParent);
	
	int noInode, noBlock;
	inode *placeInode = inodeLibre(sb->inodes);
	noInode = placeInode->noInode;
	placeInode->typeBlock=0;
	
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

void supprDir(superBlock *sb, int argInode){
    blockD *tmpD = noInodeToBlockD(sb, argInode);
    blockD *parent =noInodeToBlockD(sb, tmpD->inodes[1]);
    inode *tmpI = noInodeToInode(sb, argInode);
    tmpI->typeBlock=2; //on met l'inode a etat inutilise
    
    int i;
    for(i=0;i<20;i++){
		tmpD->inodes[i]=0;
		tmpD->sousDirect[i]=NULL;	
	}
	i=0;
	while(parent->inodes[i]!=argInode){
		i++;
	}
	parent->inodes[i]=0;
	parent->sousDirect[i]=NULL;
}

int creerFicher(superBlock *sb, int inodeDossier, char *nomfile){//creer un fichier -vide- dans un dossier, retourne inode
    	//on lui cherche un inode disponible
    	inode *tmpI = inodeLibre(sb->inodes);
    	tmpI->typeBlock=1;
    	blockD *tmpD = noInodeToBlockD(sb, inodeDossier);
    	
    	blockF *tmpF = blockFLibre(sb->blocksF);//on cherche un blockF de libre ou on le créer
    	tmpF->used=1;//on le marque comme utilise
    	tmpF->noInode=tmpI->noInode;
    	int i=2;
    	while(tmpD->inodes[i]!=0){
			i++;
		}
		tmpD->inodes[i]=tmpI->noInode;
		tmpD->sousDirect[i]=nomfile;
		tmpI->block =tmpF->noBlockF;
		return tmpI->noInode;  		
}

void supprFichier(superBlock *sb, int argInode, int dossier){
		inode *tmpI = noInodeToInode(sb, argInode);
		tmpI->typeBlock=2; //on libere l'inode
		blockF *tmpF = noInodeToBlockF(sb, argInode);
		while(tmpF->nextF!=NULL){
			printf("ca va merder\n");
			tmpF->used=0; //on passe tous les blockF du fichier a l'état inutilisé
			tmpF=tmpF->nextF;
		}
		//on le retire de la table du dossier
		blockD *tmpD = noInodeToBlockD(sb,dossier);
		int i=2;
		while(tmpD->inodes[i]!=argInode){
			i++;
		}
		tmpD->inodes[i]=0;
		tmpD->sousDirect[i]=NULL;
}

inode *noInodeToInode(superBlock *sb, int argInode){
    inode *tmp = sb->inodes;
    while(tmp->noInode!=argInode && tmp!=NULL){
		tmp=tmp->next;  //on cherche le numéro de block dans la table d'inodes
	}
	if(tmp == NULL){
		// si l'inode n'a été trouvé : erreur	
		printf("erreur critique : inode %d non trouve\n",argInode);
		exit(2);
	} 
	else{
		return tmp;
	}
}

blockD *noInodeToBlockD(superBlock *sb, int argInode){
    inode *tmpI = noInodeToInode(sb,argInode);
    if(tmpI->typeBlock!=0){
		printf("erreur critique : l'inode %d ne pointe pas sur les repertoires\n",argInode);
		exit(2);
	}
	int block = tmpI->block; 
	blockD *tmpD = sb->blocksD;
	while(tmpD->noBlockD!=block && tmpD!=NULL){
		tmpD=tmpD->next; //on cherche le blockD
	}
	if(tmpD==NULL){
		printf("erreur critique : le blockD no %d n'existe pas\n",block);
		exit(2);
	}
	else{
		return tmpD;
	}		
}

blockF *noInodeToBlockF(superBlock *sb, int argInode){
    
    inode *tmp = noInodeToInode(sb, argInode);
	int block = tmp->block; 
	blockF *tmpF = sb->blocksF;
	while(tmpF->noBlockF!=block && tmpF !=NULL){
		tmpF=tmpF->nextBlock; //on cherche le blockF et on le retourne
	}
	if(tmpF == NULL){printf("erreur critique : block no %d non trouve\n",block); exit(2);}
	return tmpF;		
}