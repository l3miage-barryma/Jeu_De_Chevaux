#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "projet0.h"

void creat_fork(int n){
	
	for(int i = 0; i < n; i++){
	
		 if (fork() == 0) {
           		 printf("[fils] pid %d [pere] pid %d\n",getpid(), getppid());
            		 exit(0);
       		 }
	}
	

}

int main(int argc, char * argv[]){
	
	//creation de quatre precessus fils²	
	int nbFils;
	if(argc != 2){
		  fprintf(stderr, "argument insufisant\n");
       		 exit(-1);
	}
	
	nbFils = atoi(argv[1]);
	if(nbFils < 0){
		fprintf(stderr,"ERREUR! ressasir à nouveau un entier positif\n");
		exit(-1);
	}
	creat_fork(nbFils);
	while(wait(NULL) !=-1);	
	

	return 0;
}
