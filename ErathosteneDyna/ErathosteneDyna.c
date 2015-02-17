/*
 ============================================================================
 Name        : ErathosteneDyna.c
 Author      : 
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "inout.h"

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

/*  TODO ... */

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

/*  TODO ... */

