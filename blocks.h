#ifndef BLOCKS_H
#define BLOCKS_H

//const int tailleC=8;
//const int tailleD=255;


typedef struct superBlock superBlock;
typedef struct inode inode;
typedef struct blockF blockF;
typedef struct blockD blockD;
typedef struct user user;

struct superBlock{
	//structures blocks
	inode *inodes;
	blockF *blocksF;
	blockD *blocksD;
	//variables pour le fd
	int nbBlockI;
	int maxBlockI;
	int nbBlockF;
	int maxBlockF;
	int nbBlockD;
	int maxBlockD;
	//structure utilisateur
	user *users;
	int userEnCours;
	
} SUPERBLOCK_T;

superBlock *initSGF();

struct inode{
	int noInode;
	int typeBlock; //0 directory, 1 File, 2 inode inutilise
	int block;
	
	//infos utilisateur
	int proprio;
	int droitU;
	int droitA;
	
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
int creaDir(superBlock *sb, int noInodeParent, char *nomDir);
void supprDir(superBlock *sb, int argInode);
void toStringBlockD(superBlock *sb, int argInode);
blockD *noInodeToBlockD(superBlock *sb, int argInode);

struct user{
	int noUser;
	char *nom;
	char *mdp;
	user *next;
} USER_T;


user *initUser(int argnoUser, char *argNom, char *argmdp);
user *noUserToUser(superBlock *sb, int argNumero);
user *nomUserToUser(superBlock *sb, char *argNom);
int connexion(superBlock *sb, char *argNom, char *mdp);
int verifDroit(superBlock *sb, int argInode, int userCo, int action);
int chproprio(superBlock *sb, int argInode,int uConnecte, char *argNom);
void tableUser(superBlock *sb, int userCo);
int newUser(superBlock *sb, char *argNom, char *mdp);
int delUser(superBlock *sb, int userCo, char *argNom);


#endif
