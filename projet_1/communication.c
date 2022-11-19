#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "communication.h"



int communication(int id, int descripteur0[2], int descripteR[2], int descripteW[2]){
    
    //declaration des chaines pour stocker le nbre d'octets a lire et a ecrire
    //char buffR[255], buffW[256]; 
    int number = 3;
    long int n;
    sleep(10);//attend 10s
    //commencer par fermer les descripteur non utilise
    //fermeture de la lecture du descripteur0
    close(descripteur0[0]);
    close(descripteR[1]);
    close(descripteW[0]);
    
    //sprintf(bufferW,"msg de p1 (%d)\n",getpid()); 
    //p1 lit dans le pipe descripteur0
    n = read(descripteR[0], &number, sizeof(int));
        if(n==-1)
             perror("problème de lecture ");
    close(descripteR[0]);
    
    /*fermure  apres ecriture en ecriture du pipe descripteur0*/
    
    
    //on affiche le contenu du fils en cour
    printf("id:%d, number : %d\n", id, number);
    //on incremente l'entier pour etre sur que les fils communiquent
    number +=1;

    //close(descripteur0[1]);
    
    //le fils suivant ecrit dans le descriteurW le contenu de pipe precedent
    //close(descripteur0[1]);
    n = write(descripteW[1], &number, sizeof(int));
    if(n == -1)
        { perror("problème d'écriture processus ");}
    close(descripteW[1]);
    

    //on envoi (ecriture)l'entier  du processus en cours dans le descripteur0
    n = write(descripteur0[1], &id, sizeof(int));
    if(n == -1)
        { perror("problème d'écriture père");}
    close(descripteur0[1]);
    //le fils suivant lit dans le descriteur0 le contenu de p2
    //n = read(descripteur0[0], &number, sizeof(int));
    // quitter
    exit(0);
}

