/*
 ============================================================================
 Name        : ListDemo.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
/* ------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "list.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
static const int MAX_LEN = 10;
static const int MAX_SIZE = 100;
/* ------------------------------------------------------------------------- */
void ShowString(TValueList* pValue) {
	if (!*pValue) {
		printf("* ");
	} else {
		printf("%s ", *pValue);
	}
}

void DestroyString(TValueList* pValue) {
	if (!*pValue)
		free(*pValue);
	*pValue = NULL;
}
/* ------------------------------------------------------------------------- */
void ShowList(struct TList* pList) {
	TIteratorList iter = BeginOfList(pList), end = EndOfList(pList);
	printf("ShowList -> ");
	printf("IsEmptyList(pList) : %d", IsEmptyList(pList));
	printf(", SizeOfList(pList) : %d\n", SizeOfList(pList));
	while (iter != end) {
		ShowString(GetPDataInList(iter));
		iter = NextInList(iter);
	}
	puts("");
}

void ShowInverseList(struct TList* pList) {
	TIteratorList iter = EndOfList(pList), begin = BeginOfList(pList);
	printf("ShowInverseList -> ");
	printf("IsEmptyList(pList) : %d", IsEmptyList(pList));
	printf(", SizeOfList(pList) : %d\n", SizeOfList(pList));
	while (iter != begin) {
		iter = PreviousInList(iter);
		ShowString(GetPDataInList(iter));
	}
	puts("");
}

void InsertRandomStringsAtBegin(struct TList* pList, int n) {
	char* s;
	int len, i, j, l;
	static char t[11];
	for (i = 0; i < n; ++i) {
		sprintf(t, "%d", i);
		l = strlen(t);
		len = rand() % MAX_LEN + l + 1;
		s = malloc(len + 1);
		strcpy(s, t);
		for (j = l; j < len; ++j) {
			s[j] = rand() % 26 + 'A';
		}
		s[len] = '\0';
		InsertInList(pList, BeginOfList(pList), &s);
	}
}

void InsertRandomStringsAtEnd(struct TList* pList, int n) {
	char* s;
	int len, i, j, l;
	static char t[11];
	for (i = 0; i < n; ++i) {
		sprintf(t, "%d", i);
		l = strlen(t);
		len = rand() % MAX_LEN + l + 1;
		s = malloc(len + 1);
		strcpy(s, t);
		for (j = l; j < len; ++j) {
			s[j] = rand() % 26 + 'A';
		}
		s[len] = '\0';
		InsertInList(pList, EndOfList(pList), &s);
	}
}

void EraseNodesFromBegin(struct TList* pList) {
/*	TIteratorList it;
	for (it = BeginOfList(pList); it != EndOfList(pList); free(*GetPDataInList(
			it)), it = EraseInList(pList, it))*/
		;
}

void EraseNodesFromEnd(struct TList* pList) {
/*	TIteratorList it;
	for (it = EndOfList(pList); it != BeginOfList(pList); it = PreviousInList(
			it), free(*GetPDataInList(it)), it = EraseInList(pList, it))
		;*/
}

int main(void) {
	///*
	struct TList* pList = CreateList();
	puts("struct TList* pList = CreateList() ...");
	ShowList(pList);
	InsertRandomStringsAtBegin(pList, 20);
	puts("InsertRandomStringsAtBegin(pList, 20) ...");
	ShowList(pList);
	ShowInverseList(pList);
	EraseNodesFromBegin(pList);
	puts("EraseNodesFromBegin(pList) ...");
	ShowList(pList);
	InsertRandomStringsAtEnd(pList, 80);
	puts("InsertRandomStringsAtEnd(pList, 80) ...");
	ShowList(pList);
	EraseNodesFromEnd(pList);
	puts("EraseNodesFromEnd(pList) ...");
	ShowList(pList);
	InsertRandomStringsAtBegin(pList, 80);
	puts("InsertRandomStringsAtBegin(pList, 80) ...");
	ShowList(pList);
	WalkSequenceList(DestroyString, NextInList(BeginOfList(pList)),
			PreviousInList(EndOfList(pList)));
	puts(
			"WalkSequenceList(DestroyString,NextInList(BeginOfList(pList)), PreviousInList(EndOfList(pList))) ...");
	ShowList(pList);
	EraseSequenceInList(pList, NextInList(BeginOfList(pList)), PreviousInList(
			EndOfList(pList)));
	puts(
			"EraseSequenceInList(pList,NextInList(BeginOfList(pList)),PreviousInList(EndOfList(pList))) ...");
	ShowList(pList);
	WalkSequenceList(DestroyString, BeginOfList(pList),EndOfList(pList));
	puts(
			"WalkSequenceList(DestroyString, BeginOfList(pList),EndOfList(pList)) ...");
	ShowList(pList);
	DestroyList(pList);
	//*/
	puts("\n!!!BYE!!!");
	return EXIT_SUCCESS;
}
