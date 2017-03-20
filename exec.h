#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include "supp.h"
#include "bool.h"
#define Taille_max 100

/* Variable global de la commande */
char cmd[Taille_max];


void commmande_interne(char *com[Taille_max]);

void commande_externe(char *com[Taille_max]);

void ExecPipe(char *com[Taille_max]);

void ExecPV(char *com[Taille_max]);


/* Incomplet */

void ExecRedir(char *com[Taille_max]);

void ExecET(char *com[Taille_max]);
