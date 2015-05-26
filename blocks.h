#ifndef BLOCKS_H
#define BLOCKS_H

//const int tailleC=8;
//const int tailleD=255;


typedef struct superBlock superBlock;
typedef struct inode inode;
typedef struct blockF blockF;
typedef struct blockD blockD;

struct superBlock{
	inode *inodes;
	blockF *blocksF;
	blockD *blocksD;
} SUPERBLOCK_T;

superBlock *initSGF();

struct inode{
	int noInode;
	int typeBlock; //0 directory, 1 File, 2 inode inutilise
	int block;
	inode *next;
} INODE_T;

inode *initInode(int argInode, int argType, int argBlock);
inode *inodeLibre(inode *inodes);
inode *noInodeToInode(superBlock *sb, int argInode);

void toStringInode(superBlock *sb);

struct blockF{
	int noInode;
	int used; //0 inutilise 1 utilise
	int noBlockF;
	char contenu[8];
	blockF *nextF;
	blockF *nextBlock;
} BLOCKF_T;

blockF *initBlockFvide(int inodeF);
blockF *noInodeToBlockF(superBlock *sb, int argInode);
blockF *blockFLibre(blockF *blocksF);
int creerFicher(superBlock *sb, int inodeDossier, char *nomfile);
void supprFichier(superBlock *sb, int inodeFichier, int dossier);
char * lireFichier(superBlock *sb, int argInode);

void toStringBlocksF(superBlock *sb);

struct blockD{
	int noInode;
	int noBlockD;
	char *sousDirect[20];
	int inodes[20];
	blockD *next;	
} BLOCKD_T;

blockD *initDirec(int inodeDirect, int inodePapa, int argBlock);
blockD *blockDLibre(blockD *blocksD);
void creaDir(superBlock *sb, int noInodeParent, char *nomDir);
void supprDir(superBlock *sb, int argInode);
void toStringBlockD(superBlock *sb, int argInode);
blockD *noInodeToBlockD(superBlock *sb, int argInode);

#endif
