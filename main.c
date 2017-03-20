#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include "exec.h"
#include "bool.h"
#include "supp.h"
#define Taille_max 100

/* Variable global de la commande */
char cmd[Taille_max];


/* Récupération de la commande, et suppression du '\n' */
int ligne_shell(char cmd[Taille_max]){
	int k = 0;
	int v = 1;
	char my_cwd[1024];

    	getcwd(my_cwd, 1024);

    	printf("%s", my_cwd);			/* Affichage du dossier courant */
	printf("> ");				/* '>' */
	fgets(cmd, Taille_max, stdin);		/* Récupération de ligne de commande */

	if (strcmp(cmd,"\n") != 0){		/* Test ligne vide (utile pour ^C et ^\) */
		while( k < Taille_max ){
			//printf("test %i\n",k);
			if(cmd[k]=='\n'){	/* Remplacement du caractère de fin */
				cmd[k]='\0';			
			}
			k++;
		}
	}else{
		//printf("test sortie\n");
		v = -1;				/* valeur si la ligne était vide */
	}
	return v;
}

/*============================================================================================*/
/*=================================== Fonction principale ====================================*/
/*============================================================================================*/

void mon_shell (char *arge[]){
	char *com[Taille_max];
	int v;
	
	signal(SIGINT,SIG_IGN);					/* Gestion signal ^C */
	signal(SIGQUIT,SIG_IGN);				/* Gestion signal ^\ */
	printf("Bienvenue dans notre shell, tapez 'exit' pour en sortir \n");
	//printf("Taille max : %i \n", Taille_max);
	v = ligne_shell(cmd);					/* Affichage de la ligne mini-shell */
	//printf("%i\n",v);
	
	while (strcmp(cmd,"exit") != 0) {			/* 'exit' pour quitter */
		if (v == 1){
			supp_espace(cmd, com);			/* récupération de la comde */
			if (Pipe(com)){
				//printf("Exec avec un pipe\n");
				ExecPipe(com);			/* Exécution avec un pipe */ 
			}else if (PointV(com)){
				//printf("Exec avec un point virgule\n");
				ExecPV(com);			/* Exécution avec un point virgule */
			}else if (redir(com)){
				//printf("Exec redir\n");
				//ExecRedir(com);
			}else if (est_et(com)){
				//printf("Exec &&\n");
				//ExecET(com);
			}else if (est_interne(com)){
				//printf("Exec interne\n");
				commmande_interne(com);		/* Exécution d'une commande interne */	
			}else{
				//printf("%s\n", com[0]);
				commande_externe(com);		/* Exécution d'une commande externe */
			}
		}
			v = ligne_shell(cmd);			/* Affichage de la ligne mini-shell */
			//printf("%i\n",v);
	}

}

/*============================================================================================*/
/*===================================== Fonction main ========================================*/
/*============================================================================================*/


int main(int argc, char *argv[], char *arge[]){
    mon_shell(arge);
    return 0;
}
