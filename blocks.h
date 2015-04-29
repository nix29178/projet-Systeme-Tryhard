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

struct blockF{
	int noInode;
	int noBlockF;
	char contenu[8];
	blockF *nextF;
	blockF *nextBlock;
} BLOCKF_T;

blockF *initBlockFvide(int inodeF, int argBlock);

struct blockD{
	int noInode;
	int noBlockD;
	char *sousDirect[255];
	int inodes[255];
	blockD *next;	
} BLOCKD_T;

blockD *initDirec(int inodeDirect, int inodePapa, int argBlock);
blockD *blockDLibre(blockD *blocksD);
void creaDir(superBlock *sb, blockD *parent, char *nomDir);
void toStringBlockD(blockD *block);

#endif
