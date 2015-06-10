#ifndef USER_H
#define USER_H

typedef struct user user;

struct user{
	int noUser;
	char *nom
	char *mdp;
	user *next;
} USER_T;


user *initUser(superBlock *sb, int argnoUser, char *argNom, char *argmdp);
int connexion(superBlock *sb, char *argNom, char *mdp);

#endif
