/*
 ============================================================================
 Name        : ErathosteneStatic.c
 Author      : Marlier M.
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../InOut/src/inout.h"

typedef short int bool;
#define false 0
#define true 1
#define MAX 100000
#define PPREM_SIZE 78498

struct TListePrem {
	int nbrMax;
	int pPrem[PPREM_SIZE];
	int nbrPrem;
};

void InitialiserTListePrem(struct TListePrem *l);
void Erathostene(struct TListePrem *l);
void AfficherPremiers(struct TListePrem *l);
void DetruireTListePrem(struct TListePrem *l);

int main(int argc, char *argv[])
{

	struct TListePrem listePrem;
	do {
		InitialiserTListePrem(&listePrem);
		listePrem.nbrMax =
		    ReadIntLimited("\nVotre naturel maximum ? ", 0, MAX);
		Erathostene(&listePrem);
		AfficherPremiers(&listePrem);
		DetruireTListePrem(&listePrem);
	} while (!Stop());
	return EXIT_SUCCESS;
}

void InitialiserTListePrem(struct TListePrem *l)
{
	l->nbrMax = MAX;
	l->pPrem[0] = 0;
	l->nbrPrem = 0;
}

void Erathostene(struct TListePrem *l)
{
	bool bools[MAX + 1];
	int i, nb, k;
	double racine;

	for (i = 0; i < MAX; ++i)
		bools[i] = true;

	bools[0] = false;
	bools[1] = false;

	racine = sqrt(l->nbrMax);

	for (nb = 2; nb < racine; nb++) {
		k = l->nbrMax / nb;
		for (i = nb; i <= k; i++)
			bools[i * nb] = false;
	}

	for (i = 0; i < l->nbrMax; ++i)
		if (bools[i] == true)
			l->pPrem[l->nbrPrem++] = i;
}

void AfficherPremiers(struct TListePrem *l)
{
	int i;
	for (i = 0; i < l->nbrPrem; ++i)
		printf("%d;", l->pPrem[i]);
	printf("\n");
}

void DetruireTListePrem(struct TListePrem *l)
{
	int i;
	for (i = 0; i < PPREM_SIZE; ++i)
		l->pPrem[i] = 0;
}
