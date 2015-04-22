#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 1
int oLectureSeule(char *file){
    int fd;
    if((fd = open(file,O_RDONLY))==-1){
        printf("il existe pas :'(");
        exit(2);
    }
    else{
        return fd;
    }
}

int creNouveauFichier(char *file){
    int fd;
    if((fd = open(file,O_WRONLY|O_CREAT))==-1){
        printf("erreur sur la creation du fichier :'(");
        exit(2);
    }
    else{
        return fd;
    }
}


void copierContenu(int fd, int fd2){
    int n;
    char *buff;
    buff = malloc(sizeof(char)*SIZE);
    while ((n = read(fd, buff, SIZE)) > 0){
            write(fd2,buff,SIZE);
    }
    free(buff);
}

int main(int argc, char * argv[])
{
    if(argc != 3){
        printf("Merci de passer deux fichiers en paramètre\n");
        exit(2);
    }
    int fd,fd2;

    fd = oLectureSeule(argv[1]);
    fd2 = creNouveauFichier(argv[2]);
    printf("\nCopie de %s à %s\n",argv[1],argv[2]);
    fd = oLectureSeule(argv[1]);
    copierContenu(fd,fd2);
    printf("copie terminée\n");
    printf("\n");
    close(fd);
    close(fd2);
    return 0;
}
