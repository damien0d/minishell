#include "supp.h"


/*============================================================================================*/
/*================================= Suppression des pipes ====================================*/
/*============================================================================================*/
void supp_pipe(char *com[Taille_max], char *com_sansP[Taille_max][Taille_max]){
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;

	while(com[i] != NULL){
		if(strcmp(com[i],"|") == 0){
			com_sansP[j][k] = NULL;
			k = 0;
			j++;
			i++;
		}else{
			com_sansP[j][k] = com[i];
			k++;
			i++;
		}
	}
	j++;
	com_sansP[j][0] = NULL;
}


/*============================================================================================*/
/*================================ Suppression des espaces ===================================*/
/*============================================================================================*/
void supp_espace(char commande[Taille_max], char *com[Taille_max]){
	char *token;
	char *separateur = {" "};
	int n = 0;

	token = strtok(commande,separateur);

	while(token != NULL){
		com[n] = token;
		token = strtok(NULL, separateur);
		n++;
	}
	com[n]=NULL;
	
}
