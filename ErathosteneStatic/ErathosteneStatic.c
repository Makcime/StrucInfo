/*
 ============================================================================
 Name        :
 Author      :
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "inout.h"

typedef short int bool;
#define false 0
#define true 1

#define MAX 100000

struct TListePrem {
	int nbrMax;
	int pPrem[78498];
	int nbrPrem;
};

/* TODO ... */

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

/* TODO ... */
