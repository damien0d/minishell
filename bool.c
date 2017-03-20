#include "bool.h"

/*=========================== Fonctions qui retournent un bool ================================*/

/*============================================================================================*/
/*======================================= est_interne ========================================*/
/*============================================================================================*/
bool est_interne(char *com[Taille_max]){
	bool check;
	check = false;	

	if(strcmp(com[0],"cd")==0){			/* Compare si c'est une 'cd' */
		check = true;
	}else if (strcmp(com[0],"echo")==0){		/* Compare si c'est une 'echo' */
		check = true;
	}else if (strcmp(com[0],"getenv")==0){		/* Compare si c'est une 'getenv' */
		check = true;
	}
	return check;
}

/*============================================================================================*/
/*======================================== avec pipe =========================================*/
/*============================================================================================*/
bool Pipe(char *com[Taille_max]){
	bool check;
	int i = 0;
	check = false;
	
	while(com[i] != NULL){
		if (strcmp(com[i],"|") == 0){
			check = true;
		}		
		i++;	
	}
	return check;
}

/*============================================================================================*/
/*=================================== avec point virgule =====================================*/
/*============================================================================================*/
bool PointV(char *com[Taille_max]){
	bool check;
	int i = 0;
	check = false;
	
	while(com[i] != NULL){
		if (strcmp(com[i],";") == 0){
			check = true;
		}		
		i++;	
	}
	return check;
}


/*============================================================================================*/
/*===================================== Non utilisées ========================================*/
/*============================================================================================*/
/* Regarde si '&&' est présent  */
bool est_et(char *com[Taille_max]){
	bool check;
	int i = 0;
	check = false ;

	while (com[i] != NULL){
		if (strcmp(com[i],"&&") == 0) {
			check = true;		
		}
		i++;
	}
	return check;
}

/* Regarde si '||' est présent */
bool est_ou(char *com[Taille_max]){
	bool check;
	int i = 0;
	check = false ;

	while (com[i] != NULL){
		if (strcmp(com[i],"||") == 0) {
			check = true;		
		}
		i++;
	}
	return check;
}

/* Regarde si '<' ou '>' est présent */
bool redir(char *com[Taille_max]){
	bool check;
	int i = 0;
	check = false ;

	while (com[i] != NULL){
		if ((strcmp(com[i],"<") == 0) || (strcmp(com[i],">")) == 0) {
			check = true;		
		}
		i++;
	}
	return check;
}



