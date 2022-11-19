#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/wait.h>
#include "joue.h"

#define NBPLAYERS 4


int main(int argc, char const *argv[])
{
    pid_t bufferPid;
   // int pipes[PIPES_LENGHT];
    int players[4];
    int idplayer = -1;
    int token = 0;
    int valfork;
    // score pour le fils 0
    int score0 = 0;
    // score pour le fils 1
    int score1 = 0;
    // score pour le fils 2
    int score2 = 0;
    // score pour le fils 3
    int score3 = 2;
    int tuyaux[4][2];
    // creation des pipes
    for (int i = 0; i < 4; i++)
    {
        pipe(tuyaux[i]);
        printf("je suis le tuyau numero %d \n", i);
    }

    // creation des nb processus
    for (int i = 0; i < NBPLAYERS; i++)
    {
        valfork = fork();
        if (valfork == 0)
        { 
   
            idplayer = i;
            switch (idplayer)
            {

            case 0:
                // pour le fils 0
                close(tuyaux[0][0]);
                close(tuyaux[1][0]);
                close(tuyaux[1][1]);
                close(tuyaux[2][0]);
                close(tuyaux[2][1]);
                close(tuyaux[3][1]);
                score0 = joue(idplayer);
                printf("je suis le fils0 \n");
                read(tuyaux[3][0], &score3, sizeof(int));
                close(tuyaux[3][0]);
             write(tuyaux[0][1], &score0, sizeof(int));
             close(tuyaux[0][1]);
                printf("mon score %d\n", score0);
                printf("fils0 a lu la  valeur :%d\n",score3);
                // close(tuyaux[0][1]);
                exit(0);

            case 1:
                // pour le fils 1
                close(tuyaux[1][0]);
                close(tuyaux[2][0]);
                close(tuyaux[2][1]);
                close(tuyaux[3][1]);
                close(tuyaux[3][0]);
                close(tuyaux[0][1]);
                //close(tuyaux[0][0]);
                score1 = joue(idplayer);
                printf("mon  score %d\n", score1);
                printf("je suis le fils1 \n");
                read(tuyaux[0][0], &score0, sizeof(int));
                printf("fils1 a lu la valeur %d\n", score0);
                close(tuyaux[0][0]);
                write(tuyaux[1][1], &score1, sizeof(int));
                close(tuyaux[1][1]);
                exit(0);
            case 2:
                // pour le fils 2
                close(tuyaux[2][0]);
                close(tuyaux[3][0]);
                close(tuyaux[3][1]);
                close(tuyaux[0][0]);
                close(tuyaux[0][1]);
                close(tuyaux[1][1]);
                score2 = joue(idplayer);
                printf("mon score %d\n", score2);
                printf("je suis le fils 2\n");
                read(tuyaux[1][0], &score1, sizeof(int));
                printf("fils 2 a lu la valeur %d\n", score1);
                close(tuyaux[1][0]);
                write(tuyaux[2][1], &score2, sizeof(int));
                close(tuyaux[2][1]);
                exit(0);
            case 3:
                // pour le fils 3
                close(tuyaux[3][1]);
                close(tuyaux[0][0]);
                close(tuyaux[0][1]);
                close(tuyaux[1][0]);
                close(tuyaux[1][1]);
                close(tuyaux[2][1]);
                score3 = joue(idplayer);
                printf("mon score %d\n", score3);
                printf("je suis le fils3\n");
                read(tuyaux[2][0], &score2, sizeof(int));
                printf("fils3 a lu la valeur %d\n", score2);
                close(tuyaux[2][0]);
				write(tuyaux[3][0], &score3, sizeof(int));
                close(tuyaux[3][0]);
                exit(0);
            default:
                while (wait(NULL) != -1);
                write(tuyaux[4][1], &score3, sizeof(int));
                close(tuyaux[4][1]);
                // fermetures des pipes 
                close(tuyaux[0][1]);
                close(tuyaux[0][0]);
                close(tuyaux[1][1]);
                close(tuyaux[1][0]);
                close(tuyaux[2][0]);
                close(tuyaux[2][1]);
                close(tuyaux[3][0]);
				close(tuyaux[4][0]);
                fprintf(stderr, "je suis le principal et je meurs ");
            }
            
        }
    }
  

    // Début du jeu
    // srand(time(NULL));

    // Principale
    // int aJoueur = 0;
    // Donne la main au joueur aJoueur

    // TODO écrire dans le pipe un 1
    // TODO attendre dans le pipe le retour du joueur
    // SWITCH
    // Si joueur retourne chevaux affiche les joueurs sort sont chevaux....
    // Si joueur retourne un nombre (c'est sont score)
    // Score > 60 jouaeur Vainceur

    // Sinon passe au joueur suivant ((aJoueur = aJoueur + 1)% 4)

    // Chaque fils

    // Attent sur son port d'écoute le go (1) du principale
    // Lance son dés
    // Si 6 est pas de chevau sortie -> sort le chevau -> écrit sur son pipe 'Chevaux'
    // Sinon avance de dé cases -> écrit sur son pipe son score
    // Boucle sans fin
}

//------------- definition des fonctions ------------------------
