/*
 ============================================================================
 Name        : TreeDemo.c
 Author      : Mattens JM
 Version     : 1.1
 Copyright   : Your copyright notice
 Description : Test of tree, Ansi-style
 ============================================================================
 */
/* ------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
static void * const MAX_KEY = (void*) 0xFF;
static const int MAX_SIZE = 100;
/* ------------------------------------------------------------------------- */
/* Definitions of functions to get key and to compare keys                   */
const void* GetPtr(const struct TPairPtrSize* pData) {
	return pData->ptr;
}

bool LessPtr(const void* ptr1, const void* ptr2) {
	return (ptr1 < ptr2);
}
/* ------------------------------------------------------------------------- */
void ShowPairPtrSize(TValueTree* pValue) {
	if (!pValue) {
		printf("   *   ");
	} else {
		printf("(%02x,%02d)", (int) pValue->ptr, pValue->size);
	}
}

void ShowKey(TValueTree* pValue) {
	if (!pValue) {
		printf("* ");
	} else {
		printf("%02x ", (int) pValue->ptr);
	}
}

void ModifySizes(TValueTree* pValue) {
	++pValue->size;
}
/* ------------------------------------------------------------------------- */
void ShowShort(struct TTree* pTree, TIteratorTree it) {
	printf("(%02x,%02d) ", (int) GetKeyInTree(pTree, it),
			GetPDataInTree(it)->size);
}

void ShowTree(struct TTree* pTree) {
	TIteratorTree iter = BeginOfTree(pTree), end = EndOfTree(pTree);
	printf("ShowTree -> ");
	printf("IsEmptyTree(pTree) : %d", IsEmptyTree(pTree));
	printf(", SizeOfTree(pTree) : %d\n", SizeOfTree(pTree));
	while (iter != end) {
		ShowShort(pTree, iter);
		iter = NextInTree(iter);
	}
	puts("");
}

void ShowInverseTree(struct TTree* pTree) {
	TIteratorTree iter = EndOfTree(pTree), begin = BeginOfTree(pTree);
	printf("ShowInverseTree -> ");
	printf("IsEmptyTree(pTree) : %d", IsEmptyTree(pTree));
	printf(", SizeOfTree(pTree) : %d\n", SizeOfTree(pTree));
	while (iter != begin) {
		iter = PreviousInTree(iter);
		ShowShort(pTree, iter);
	}
	puts("");
}

void InsertInRandomOrder(struct TTree* pTree, int n) {
	int i;
	struct TPairPtrSize data;
	for (i = 0; i < n; ++i) {
		data.ptr = (void*) (rand() % ((int) MAX_KEY + 1));
		data.size = rand() % MAX_SIZE;
		InsertInTree(pTree, &data);
	}
}

void InsertInOrder(struct TTree* pTree, int n) {
	struct TPairPtrSize data;
	double random;
	int key = 0;
	int possibilities = (int) MAX_KEY + 1;
	double probaNotTakeKey;
	while (n > 0) {
		probaNotTakeKey = pow((double) (possibilities - 1)
				/ (double) possibilities, n);
		random = (double) rand() / (double) RAND_MAX;
		if (random < probaNotTakeKey) {
			++key;
			--possibilities;
		} else {
			data.ptr = (void*) key;
			data.size = rand() % MAX_SIZE;
			InsertInTree(pTree, &data);
			--n;
		}
	}
}

void InsertInReverseOrder(struct TTree* pTree, int n) {
	struct TPairPtrSize data;
	double random;
	int key = (int) MAX_KEY;
	int possibilities = (int) MAX_KEY + 1;
	double probaNotTakeKey;
	while (n > 0) {
		probaNotTakeKey = pow((double) (possibilities - 1)
				/ (double) possibilities, n);
		random = (double) rand() / (double) RAND_MAX;
		if (random < probaNotTakeKey) {
			--key;
			--possibilities;
		} else {
			data.ptr = (void*) key;
			data.size = rand() % MAX_SIZE;
			InsertInTree(pTree, &data);
			--n;
		}
	}
}

void EraseNodesFromBegin(struct TTree* pTree) {
	TIteratorTree it;
	for (it = BeginOfTree(pTree); it != EndOfTree(pTree); it = EraseInTree(
			pTree, it))
		;
}

void EraseNodesFromEnd(struct TTree* pTree) {
	TIteratorTree it;
	for (it = EndOfTree(pTree); it != BeginOfTree(pTree); it = PreviousInTree(
			it), it = EraseInTree(pTree, it))
		;
}

void EraseFromKeys(struct TTree* pTree, void* from, void* to) {
	void* k;
	size_t before, after;
	for (k = from; k <= to; k = (char*) k + 1) {
		before = SizeOfTree(pTree);
		EraseKeysInTree(pTree, k);
		after = SizeOfTree(pTree);
		printf("Erased for key %p : %3d \t", k, before - after);
	}
}

int CountNbrOfKeys(struct TTree* pTree, void* key) {
	TIteratorTree it, to;
	int count;
	to = UpperBoundInTree(pTree, key);
	for (count = 0, it = LowerBoundInTree(pTree, key); it != to; ++count, it
			= NextInTree(it))
		;
	return count;
}

void ShowKeys(struct TTree* pTree, void* from, void* to) {
	void* k;
	int nk;
	for (k = from; k < to; k = (char*) k + 1) {
		nk = CountNbrOfKeys(pTree, k);
		if (nk)
			printf("Number of key %p :%3d \t", k, nk);
	}
	printf("\n");
}

int main(void) {
	struct TTree* pTree = CreateTree(GetPtr, LessPtr);
	puts("struct TTree* pTree = CreateTree(GetPtr, LessPtr) ...");
	ShowTree(pTree);
	InsertInRandomOrder(pTree, 20);
	puts("InsertInRandomOrder(pTree, 20) ...");
	ShowTree(pTree);
	ShowInverseTree(pTree);
	ShowKeys(pTree, 0, MAX_KEY);
	__ShowPrefixTree(pTree, ShowKey, true);
	__ShowInfixTree(pTree, ShowKey, true);
	__ShowPostfixTree(pTree, ShowKey, true);
	__ShowLevelTree(pTree, ShowPairPtrSize, 7);
	WalkTree(pTree, ModifySizes);
	puts("WalkTree(pTree,ModifySizes) ...");
	ShowTree(pTree);
	EraseNodesFromBegin(pTree);
	puts("EraseNodesFromBegin(pTree) ...");
	ShowTree(pTree);
	InsertInOrder(pTree, 80);
	puts("InsertInOrder(pTree, 80) ...");
	ShowTree(pTree);
	__ShowPostfixTree(pTree, ShowKey, true);
	InsertInReverseOrder(pTree, 80);
	puts("InsertInReverseOrder(pTree, 80) ...");
	ShowTree(pTree);
	__ShowPrefixTree(pTree, ShowKey, true);
	EraseNodesFromEnd(pTree);
	puts("EraseNodesFromEnd(pTree) ...");
	ShowTree(pTree);
	InsertInRandomOrder(pTree, 80);
	puts("InsertInRandomOrder(pTree, 80) ...");
	ShowTree(pTree);
	EraseSequenceInTree(pTree, NextInTree(BeginOfTree(pTree)), PreviousInTree(
			EndOfTree(pTree)));
	puts(
			"EraseSequenceInTree(pTree,NextInTree(BeginOfTree(pTree)),PreviousInTree(EndOfTree(pTree))) ...");
	ShowTree(pTree);
	EraseSequenceInTree(pTree, BeginOfTree(pTree), EndOfTree(pTree));
	puts("EraseSequenceInTree(pTree, BeginOfTree(pTree), EndOfTree(pTree)) ...");
	ShowTree(pTree);
	InsertInRandomOrder(pTree, 800);
	puts("InsertInRandomOrder(pTree, 800) ...");
	ShowTree(pTree);
	EraseFromKeys(pTree, 0, MAX_KEY);
	puts("EraseFromKeys(pTree,0,MAX_KEY) ...");
	ShowTree(pTree);
	puts("\n!!!BYE!!!");
	DestroyTree(pTree);
	return EXIT_SUCCESS;
}
