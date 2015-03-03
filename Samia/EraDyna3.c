#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../InOut/src/inout.h"

/* typedef short int bool; */
typedef unsigned char bool;
#define false 0
#define true 1

#define MAX 2147483647 /* (2^31-1) */

struct TListePrem {
	int nbrMax;
	int* pPrem;
	int nbrPrem;
};

void InitialiserTListePrem(struct TListePrem* pListe);
void Erathostene(struct TListePrem* pListe);
void AfficherPremiers(struct TListePrem* pListe);
void DetruireTListePrem(struct TListePrem* pListe);

int main(int argc, char* argv[]) {
	clock_t start_t, end_t;
	struct TListePrem listePrem;
	do {
		InitialiserTListePrem(&listePrem);
		listePrem.nbrMax = ReadIntLimited("\nVotre naturel maximum ? ", 0, MAX);
		start_t = clock();
		Erathostene(&listePrem);
		end_t = clock();
		AfficherPremiers(&listePrem);
		printf("-> Total time taken by CPU: %4.2f sec\n", (float)(end_t - start_t) / CLOCKS_PER_SEC  );
		DetruireTListePrem(&listePrem);
	} while (!Stop());
	return EXIT_SUCCESS;
}

void InitialiserTListePrem(struct TListePrem* pListe)
{
	printf("(Initialiser called)\n");
	pListe->nbrPrem = 0;
	pListe->pPrem = NULL;
	pListe->nbrMax = 0;
}

void Erathostene(struct TListePrem* pListe)
{
	bool *aTabl_bool;
	unsigned int i, j, k, m, n, factMax, indiceK, nbrImpair, rac;
	printf("(Erathostene called)\n");
	/* On veut se débarasser en avance des nombres pairs dans la série jusque nbrMax
	 * Soit nbrMax est pair, alors le nombre d'impairs correspond à la moitié de nbrMax
	 * ex:	10 entré -> 5 impairs: 1,3,5,7,9
	 * 		12 entré -> 6 impairs: 1,3,5,7,9,11
	 * 		14 entré -> 7 impairs: 1,3,5,7,9,11,13
	 * Soit nbrMax est impair, alors le nombre d'impairs correspond à la (moitié de nbrMax)+1
	 * (le 0,5 de trop n'est pas pris en compte)
	 * ex:	11 entré -> 6 impairs: 2,3,5,7,11
	 * */
	if (pListe->nbrMax%2==0){
		nbrImpair = (pListe->nbrMax/2);
	}
	else{
		nbrImpair = (pListe->nbrMax/2)+1;
	}
	aTabl_bool = calloc(nbrImpair, sizeof(bool)); /* rem: calloc initialise à 0 */
	/* Ici aTabl_bool représente un tableau de bool désignant que les nombres impairs jusque nbrMax
	 * 	Indice:		0 | 1 | 2 | 3 | 4 |	 5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17
	 * 	Prem:		1 | 3 | 5 | 7 | 9 |	11 | 13 | 15 | 17 | 19 | 21 | 23 | 25 | 27 | 29 | 31 | 33 | 35
	 * aTabl_bool est à false en raison du calloc. On va garder false pour les Prem et true désignera les non Prem
	 * */
	aTabl_bool[0] = true; /*1 est non Prem*/
	/*
	for (l = 1; l<pListe->nbrPrem; l++){
		aTabl_bool[l] = false;
	}*/
	
	/* On remarque un lien entre Indice et Prem dans aTabl_bool:
	 * 		Pour passer de l'Indice au Prem : Prem = (Indice*2)+1
	 * 		Pour passer du Prem à l'Indice : Indice = (Prem-1)/2
	 * On va rendre les mutiples impairs des Prem impairs à true
	 * Condition d'arret: les multiples (produit i*j ici) ne doivent pas dépasser nbrMax
	 * */
	rac = sqrt(pListe->nbrMax);
	pListe->nbrPrem = nbrImpair;
	for (i=3; i<= rac; i=i+2) {
		if(aTabl_bool[(i-1)/2] == false) { /*si l'impair i est premier*/
			factMax = pListe->nbrMax/i; /*le facteur max pour multiplier i sans dépasser nbrMax */
			for (j = i; j<= factMax; j=j+2) {
				k = i*j; /*Un non Prem k à rendre true*/
				indiceK = (k-1)/2; /*l'indice qui désigne justement k*/
				if(aTabl_bool[indiceK] != true){ 
					aTabl_bool[indiceK]= true; 
					pListe->nbrPrem = pListe->nbrPrem - 1;
				}
			}
		}
	}
	
	/************ Remplissage du tableau pPrem ************/
	pListe->pPrem = calloc(pListe->nbrPrem, sizeof(int));
	pListe->pPrem[0] = 2;
	m = 1;
	for(n = 1; n<nbrImpair; n++ ){
		if( aTabl_bool[n] == false){
			pListe->pPrem[m]= (n*2)+1;
			m++;
		}
	}
	free(aTabl_bool);
}
	
void AfficherPremiers(struct TListePrem* pListe)
{
	unsigned int i, j;
	printf("(AfficherPremiers called)\n");
	/*
	for (i=0; i<pListe->nbrPrem; i++){
		printf("num %d\t%d\n",i+1, pListe->pPrem[i]);
		printf("%d\n", pListe->pPrem[i]);
	}*/
	if(pListe->nbrPrem>20){
		for (i=0; i<10; i++){
			printf("n %-12d : %12d\n",i+1, pListe->pPrem[i]);
			/*printf("%d\n", pListe->pPrem[i]);*/
		}
		puts("...");
		for (j=10; j>0; j--){
			printf("n %-12d : %12d\n",pListe->nbrPrem-j+1, pListe->pPrem[pListe->nbrPrem-j]);
			/*printf("%d\n", pListe->pPrem[i]);*/
		}
	}else{
			for (i=0; i<pListe->nbrPrem; i++){
				printf("n %-12d : %12d\n",i+1, pListe->pPrem[i]);
				/*printf("%d\n", pListe->pPrem[i]);*/
			}
	}
	printf("-> Nombre de nbrPrem : %d\n", pListe->nbrPrem);
}

void DetruireTListePrem(struct TListePrem* pListe)
{
	printf("(Detruire called)\n");
	free(pListe->pPrem);
}
