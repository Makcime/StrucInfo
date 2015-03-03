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
#define false 1
#define true 0

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
/*	for (i = 1; i <= l->nbrMax/2; ++i)
		bools[i] = true;*/
	l->nbrPrem = (l->nbrMax/2)+(l->nbrMax%2);
	bools = calloc(l->nbrPrem, sizeof(bool));

	if(l->nbrMax >= 2){
		bools[0] = false;

		racine = sqrt(l->nbrMax);

		for (nb = 3; nb <= racine; nb+=2) {
			if(bools[nb/2] == true){
				k = l->nbrMax / nb;
				for (i = nb; i <= k; i+=2)
					if(bools[(i * nb)/2] == true){
						bools[(i * nb)/2] = false;
						l->nbrPrem--;
					}
			}	
		}
	}

	l->pPrem = calloc(l->nbrPrem + 1, sizeof(int));
	nb = 0;

	l->pPrem[nb++] = 2;
	for (i = 1; i <= l->nbrMax/2; ++i)
		if (bools[i] == true)
			l->pPrem[nb++] = (i*2)+1;

	free(bools);

	t = clock() - t;
	printf("Duree calculs : %.2f\n", (float)t / 1000000);
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
 