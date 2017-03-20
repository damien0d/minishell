#include "exec.h"

/*============================================================================================*/
/*=================================== Commandes internes =====================================*/
/*============================================================================================*/
void commmande_interne(char *com[Taille_max]){
	int i;

	if(strcmp(com[0],"echo") == 0 ){		/* 'echo' reconnu */
		if(strcmp(com[1],"$HOME") == 0){
			printf("%s",getenv("HOME"));
		}else if (strcmp(com[1],"$PWD") == 0){
			printf("%s",getenv("PWD"));
		}else if (strcmp(com[1],"$PATH") == 0){
			printf("%s",getenv("PATH"));
		}else{
			i = 1;
			while(com[i] != NULL){
				printf("%s ",com[i]);				
				i++;
			}
		}
		printf("\n");	
	}else if(strcmp(com[0],"cd") == 0){		/* 'cd' reconnu */
		if(!com[1]){		
			chdir(getenv("HOME"));		
		}else{				
			chdir(com[1]);
		}
	}else if(strcmp(com[0],"getenv") == 0){		/* 'getenv' reconnu */
		if(com[1] == NULL){
			//printf("Erreur, getenv nécessite une variable\n");	
			fprintf(stderr,"Erreur, getenv nécessite une variable\n");	
		}else{
			printf("%s\n",getenv(com[1]));
		}
	}
}

/*============================================================================================*/
/*=================================== Commandes externes =====================================*/
/*============================================================================================*/
void commande_externe(char *com[Taille_max]){
	int no, status;

	switch (fork()){
		case -1 :
			perror("fork");
			exit(-1);
		case 0 :
			signal(SIGINT,SIG_DFL);
			signal(SIGQUIT,SIG_DFL);
			execvp(com[0],com);
			if(execvp(com[0],com) == -1){
				perror("execvp");	
				exit(-1);
			}
		default :
			no = wait(&status);
	}
}

/*============================================================================================*/
/*=================================== Commandes avec pipe ====================================*/
/*============================================================================================*/
void ExecPipe(char *com[Taille_max]){
	char *com_sansP[Taille_max][Taille_max];		/* Tableau de tableau de pointeur */
	int f[2];
	pipe(f);
	int i = 0;
	int j = 0;

	supp_pipe(com, com_sansP);		/* Suppression pipe et stockage dans tableau de tableau de pointeur (com_sansP) */

		switch (fork()){
			case -1 :
				printf("fork 1\n");
				perror("fork"); 
				exit(-1);

			case 0 :
				close(1);				/* fermeture sortie standard */
				dup(f[1]);				/* on met f[1] en sortie */
				close(f[1]);
				close(f[0]);
				execvp(com_sansP[0][0], com_sansP[0]);
				if (execvp(com_sansP[0][0], com_sansP[0]) == -1){
					perror("execvp");
					exit(-1);
				}
			
			default :
				while (wait(NULL)!=-1);
				switch (fork()){
					case -1 :
						printf("fork 1\n");
						perror("fork"); 
						exit(-1);

					case 0 :
						close(0);		/* fermeture entrée standard */
						dup(f[0]);		/* on met f[0] en entrée */
						close(f[0]);
						close(f[1]);
						execvp(com_sansP[1][0], com_sansP[1]);
						if (execvp(com_sansP[1][0], com_sansP[1]) == -1){
							perror("execvp");
							exit(-1);
						}
					default :
						close(f[0]);
						close(f[1]);
						while (wait(NULL)!=-1);
						//printf("sortie\n");					
				}
		}

}

/*============================================================================================*/
/*============================= Commandes avec point virgules ================================*/
/*============================================================================================*/
void ExecPV(char *com[Taille_max]){
	char *tmp[Taille_max];
	int i = 0;
	int j = 0;
	
	while(com[i] != NULL){
		if (strcmp(com[i],";") == 0){
			tmp[j] = NULL;
			if(est_interne(tmp)){
				commmande_interne(tmp);
			}else{
				commande_externe(tmp);
			}
		j = 0;			
		}else{
			tmp[j] = com[i];
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	if(est_interne(tmp)){
		commmande_interne(tmp);
	}else{
		commande_externe(tmp);
	}

}


/*============================================================================================*/
/*===================================== Gestion des && =======================================*/
/*======================================== INCOMPLET =========================================*/
/*============================================================================================*/
void ExecET(char *com[Taille_max]){
	char *tmp[Taille_max];
	int i = 0;
	int j = 0;
	int v;
	
	while(com[i] != NULL){
		if (strcmp(com[i],"&&") == 0){
			tmp[j] = NULL;
			if(est_interne(tmp)){
//				v = commmande_interne(tmp);
			}else{
//				v = commande_externe(tmp);
			}

		j = 0;			
		}else{
			tmp[j] = com[i];
			j++;
		}
		i++;
	}
	if (v!=-1){
		tmp[j] = NULL;
		if(est_interne(tmp)){
			commmande_interne(tmp);
		}else{
			commande_externe(tmp);
		}
	}

}


void ExecRedir(char *com[Taille_max]){
	
}



