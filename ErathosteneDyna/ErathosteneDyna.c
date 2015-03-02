/*
 ============================================================================
 Name        : ErathosteneDyna.c
 Author      : Marlier M.
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

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

void InitialiserTListePrem(struct TListePrem *l);
void Erathostene(struct TListePrem *l);
void AfficherPremiers(struct TListePrem *l);
void DetruireTListePrem(struct TListePrem *l);

int main(int argc, char* argv[]) {
	struct TListePrem listePrem;
	do {
		InitialiserTListePrem(&listePrem);
		listePrem.nbrMax = ReadIntLimited("\nVotre naturel maximum ? ", 0, MAX);
		Erathostene(&listePrem);
		AfficherPremiers(&listePrem);
		DetruireTListePrem(&listePrem);
	} while (!Stop());
	return EXIT_SUCCESS;
}

void InitialiserTListePrem(struct TListePrem *l)
{
	l->nbrMax = 0;
	l->pPrem = NULL;
	l->nbrPrem = 0;
}

void Erathostene(struct TListePrem *l)
{
	bool* bools;
	int i, nb, k;
	double racine;
	clock_t t = clock();

/*tableau de bool deja initialisé a true partout si true == 0 !*/
	bools = calloc(l->nbrMax + 1, sizeof(bool));
	
	for (i = 2; i <= l->nbrMax; ++i)
		bools[i] = true;

	if(l->nbrMax > 2){

		l->nbrPrem = l->nbrMax - 1;

		racine = sqrt(l->nbrMax);

		for (nb = 2; nb <= racine; nb++) {
			k = l->nbrMax / nb;
			for (i = nb; i <= k; i++){
				if(bools[i * nb] == true){
					bools[i * nb] = false;
					l->nbrPrem--;
				}
			}
		}
	}

	t = clock() - t;
	printf("Duree calculs : %.2f\n", (float)t / 1000000);

	l->pPrem = calloc(l->nbrPrem + 1, sizeof(int));
	nb = 0;

	for (i = 0; i <= l->nbrMax; ++i)
		if (bools[i] == true)
			l->pPrem[nb++] = i;

	free(bools);
}


void AfficherPremiers(struct TListePrem *l)
{
	int i;
	printf("Il y a %d nombre premiers inferieurs a %d\n", l->nbrPrem, l->nbrMax);

	if (l->nbrPrem > 20)
	{
		for (i = 0; i < 10; ++i)
			printf("Nombre premier n %10d : %11d \n", i,l->pPrem[i]);
		printf("\n...\n\n");
		for (i = l->nbrPrem-10; i < l->nbrPrem; ++i)
			printf("Nombre premier n %10d : %11d \n", i,l->pPrem[i]);
		
	}
	else{
		for (i = 0; i < l->nbrPrem; ++i)
			printf("Nombre premier n %10d : %11d \n", i,l->pPrem[i]);
	}
}

void DetruireTListePrem(struct TListePrem *l)
{	
	l->nbrPrem=0;
	l->nbrMax=0;
	free(l->pPrem);
}
 