/*
 * inout.c
 *
 *  Created on: 2 févr. 2010
 *      Author: Mattens JM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>

#include "inout.h"

long ReadLongLimited(const char* message, long min, long max) {
	long l;
	char buffer[22];
	char *pLastChar;
	char *p;
	do {
		printf("%s", message);
		p = fgets(buffer, 22, stdin);
		l = strtol(buffer, &pLastChar, 10);
	} while (p == 0 || *pLastChar != '\n' || l < min || l > max);
	return (l);
}

long ReadLong(const char* message) {
	return ReadLongLimited(message, INT_MIN, INT_MAX);
}

int ReadIntLimited(const char* message, int min, int max) {
	return (int) ReadLongLimited(message, min, max);
}

int ReadInt(const char* message) {
	return (int) ReadLongLimited(message, INT_MIN, INT_MAX);
}

double ReadDoubleLimited(const char* message, double min, double max) {
	double d;
	char buffer[23];
	char *pLastChar;
	char *p;
	do {
		printf("%s", message);
		p = fgets(buffer, 22, stdin);
		d = strtod(buffer, &pLastChar);
	} while (p == 0 || *pLastChar != '\n' || d < min || d > max);
	return (d);
}

double ReadDouble(const char* message) {
	return ReadDoubleLimited(message, -DBL_MAX, DBL_MAX);
}

int Stop(void) {
	char stop;
	do {
		printf("Voulez-vous arrêter (<O>ui/<N>on) ? ");
		stop = getchar();
		getchar();
		stop = (char) toupper(stop);
	} while ((stop != 'O') && (stop != 'N'));
	return (stop == 'O');
}
