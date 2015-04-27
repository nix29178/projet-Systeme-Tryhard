#ifndef INODES_H
#define INODES_H
typedef  struct fichier fichier;
typedef  struct dossier dossier;
struct dossier{
	//int numDossier;
	dossier *parent; 
	dossier *suivant; 
	dossier *sousDossiers;
	fichier *fichiers;
	char *nom;
} DOSSIER_T;

dossier *initSGF();
void afficherContenuD(dossier *actuel);
void creerSousDossier(dossier *actuel, char *nom);
void afficherCheminAbsolu(dossier *actuel);
dossier getSousDossier(dossier *actuel, char *nom);
void creerFichierVide(dossier *actuel, char *nom);

struct fichier{
	char *nom;
	char *contenu;
	dossier *parent; 
	fichier *suivant;
} FICHIER_T;


#endif
