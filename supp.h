#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

#define Taille_max 100

/* Variable global de la commande */
char cmd[Taille_max];



void supp_pipe(char *com[Taille_max], char *com_sansP[Taille_max][Taille_max]);

void supp_espace(char commande[Taille_max], char *com[Taille_max]);
