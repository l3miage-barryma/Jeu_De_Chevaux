#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "joue.h"
// Début du jeu
int joue(int curPlaying)
{
    int val = 0;
    srand(time(NULL) * getpid());
    int diceRoll = (rand() % 6) + 1;
    system("clear");
    printf("\n  ----- lancement du jeu ----- \n");
    sleep(1);
    printf("Joueur %d a obtenu : %d\n", curPlaying, diceRoll);
    switch (diceRoll)
    {
    case 1:
        val += 1;
        break;
    case 2:
        val += 2;
        break;
    case 3:
        val += 3;
        break;
    case 4:
        val += 4;
        break;
    case 5:
        val += 5;
        break;
    case 6:
        val += 6;
        break;
    default:
        val -= 1;
    }
    return val;
}

