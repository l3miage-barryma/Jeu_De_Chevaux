#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "communication.h"




int main(int argc, char * argv[]){
    int nbFils;
    int number ;//information à faire circuler
    if(argc != 2){
          fprintf(stderr, "argument insufisant\n");
             exit(-1);
    }
    
    nbFils = atoi(argv[1]);
     if(nbFils < 0){
        fprintf(stderr, "il faut un entier positif\n");
        exit(-1);
    }
    if(nbFils < 2){
        fprintf(stderr, "il faut au moins deux (2) processus\n");
        exit(-1);
    }
    /* creation d'un tableau de pipes  qui est un tableau de tableau pour generer tous les pipes*/
    int * pipes[nbFils];
    for(int i = 0; i < nbFils; i++){
        pipes[i]= (int*) malloc (2 * sizeof(int));
        pipe(pipes[i]);
    }

    //envoi de la valeur number au premier processus p0 dans le descripteur0
    number = 3;
    write(pipes[nbFils-1][1], &number, sizeof(int));
    //on ouvre le pipe descripteur0
    int desc0[2];
    pipe(desc0);
    /* on va generer nos n processus fils pour la communication*/
    //attention veuillez à afficher les pid des fils et du pere pour etre sur qu'il ny est pas de petit fils
    for(int i = 0; i < nbFils; i++){
        sleep(1);//attendre 1 second
        int f=fork();
        if(f== 0){
            if(i == 0){
                communication(i, desc0, pipes[nbFils-1], pipes[i]);
            }
            else{
                communication(i, desc0, pipes[i-1], pipes[i]);
            }

        }  else {
            printf("processus #id: %d\n",i);
            
        }
        
    }

    printf("\n --- init --- \n");
        //on fait une lecture du message envoyé par les fils pour etre sur que les processus communique
        int buffp;
        
        while(read(desc0[0], &buffp, sizeof(int))>0 && (buffp != nbFils -1)){
         printf("information reçu %d\n", buffp);
        }
        printf("l'information reçu :%d\n", buffp);  
        close(desc0[0]);
        //on libere la memoire allouée 
        for(int i = 0; i < nbFils; i++){
            free(pipes[i]);
            //on attend la mort des fils
            wait(NULL);
       }   
    
    return 0;
  }
