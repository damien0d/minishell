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


bool est_interne(char *com[Taille_max]);

bool Pipe(char *com[Taille_max]);

bool PointV(char *com[Taille_max]);



/* Non utilisées */

bool est_et(char *com[Taille_max]);

bool est_ou(char *com[Taille_max]);

bool redir(char *com[Taille_max]);

