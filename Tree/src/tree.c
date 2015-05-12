/*
 * tree.c
 *
 *  Created on:
 *  Author: 
 */
/* ------------------------------------------------------------------------- */
#define __DEBUG 0
/* ------------------------------------------------------------------------- */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"
#include "allocator.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
struct TTree {
	struct __TNodeTree* _header;
	size_t _nodeCount;
	TKeyOf _KeyOf;
	TComp _KeyCompare;
	struct TAllocator* _pAllocator;
};
/* ------------------------------------------------------------------------- */
typedef struct __TNodeTree _TNode;
typedef struct __TNodeTree* _TPNode;
enum __TColorType {
	_ctRed, _ctBlack
};
typedef enum __TColorType _TColorType;
struct __TNodeTree {
	_TColorType color;
	struct __TNodeTree * pParent;
	struct __TNodeTree * pLeft;
	struct __TNodeTree * pRight;
	TValueTree value;
};
/* ------------------------------------------------------------------------- */
/* Declaration of prototypes of utilities funtions                           */
/* ...                                                                       */
/* ...                                                                       */
/* ...                                                                       */

static _TPNode _CreateNode(const TValueTree* pv, const _TPNode _pParent,
		const _TPNode _pLeft, const _TPNode _pRight, _TColorType _color,
		struct TAllocator* pAllocator);
static _TPNode _CreateHeaderNode(struct TAllocator* pAllocator);
static void _RecurInfix(_TPNode iter);
/* ------------------------------------------------------------------------- */
static void __RecurPrefix(_TPNode iter);
static void __RecurPostfix(_TPNode iter);
static int __GetRecurDeep(_TPNode iter);
static _TPNode __GetNodeByLevelAndNumber(_TPNode iter, int level, int number);
static _TPNode _Root(struct TTree* pTre);

/* ------------------------------------------------------------------------- */
static bool _isCallOnLeave = false;
static FCallbackOnValue _fCallbackInfix = 0;
static FCallbackOnValue __fCallbackPrefix = 0;
static FCallbackOnValue __fCallbackPostfix = 0;
/* ------------------------------------------------------------------------- */
/* Definition of funtions declared in tree.h                                 */

/* ------------------------------------------------------------------------- */
struct TTree* CreateTree(TKeyOf __KeyOf, TComp __KeyCompare){
	return;
}

/* ------------------------------------------------------------------------- */
TKeyTree GetKeyInTree(struct TTree* pTree, TIteratorTree it){
	return;
}

/* ------------------------------------------------------------------------- */
TValueTree* GetPDataInTree(TIteratorTree it){
	return;
/* ------------------------------------------------------------------------- */
}

/* ------------------------------------------------------------------------- */
TIteratorTree BeginOfTree(struct TTree* pTree){
	return;
}

/* ------------------------------------------------------------------------- */
TIteratorTree EndOfTree(struct TTree* pTree){
	return;
}

/* ------------------------------------------------------------------------- */
bool IsEmptyTree(struct TTree* pTree){
	return;
}

/* ------------------------------------------------------------------------- */
int SizeOfTree(struct TTree* pTree){
	return;
}

/* ------------------------------------------------------------------------- */
TIteratorTree NextInTree(TIteratorTree it){
	return;
}

/* ------------------------------------------------------------------------- */
TIteratorTree PreviousInTree(TIteratorTree it){
	return;
}

/* ------------------------------------------------------------------------- */
void InsertInTree(struct TTree* pTree, struct TPairPtrSize* data){
	return;
}

/* ------------------------------------------------------------------------- */
TIteratorTree EraseInTree(struct TTree* pTree, TIteratorTree it){
	return;
}

/* ------------------------------------------------------------------------- */
void EraseKeysInTree(struct TTree* pTree, TKeyTree k){
	return;
}

void EraseSequenceInTree(struct TTree* pTree, TIteratorTree first, TIteratorTree last){
	return;
}


/* ------------------------------------------------------------------------- */
TIteratorTree UpperBoundInTree(struct TTree* pTree, TKeyTree k){
	return;
}

/* ------------------------------------------------------------------------- */
TIteratorTree LowerBoundInTree(struct TTree* pTree, TKeyTree k){
	return;
}

/* ------------------------------------------------------------------------- */
void WalkTree(struct TTree* pTree, FCallbackOnValue fCallBack) {
	_fCallbackInfix = fCallBack;
	_isCallOnLeave = false;
	_RecurInfix(_Root(pTree));
}

void DestroyTree(struct TTree* pTree) {
	if (pTree && pTree->_header) {
		EraseSequenceInTree(pTree, BeginOfTree(pTree), EndOfTree(pTree));
		Deallocate(pTree->_pAllocator, pTree->_header);
		pTree->_header = NULL;
	}
	if (pTree) {
#if __DEBUG>0
		if (GetNumberAllocated(pTree->_pAllocator) != 0)
			printf("Some memory not deallocated");
#endif
		DestroyAllocator(pTree->_pAllocator);
		free(pTree);
	}
}
/* ------------------------------------------------------------------------- */
void __ShowPrefixTree(struct TTree* pTree, FCallbackOnValue fShowValue,
		int isCallOnLeave) {
	_isCallOnLeave = isCallOnLeave;
	__fCallbackPrefix = fShowValue;
	printf("__ShowPrefixTree -> ");
	__RecurPrefix(_Root(pTree));
	printf("\n");
}

void __ShowInfixTree(struct TTree* pTree, FCallbackOnValue fShowValue,
		int isCallOnLeave) {
	_isCallOnLeave = isCallOnLeave;
	_fCallbackInfix = fShowValue;
	printf("__ShowInfixTree -> ");
	_RecurInfix(_Root(pTree));
	printf("\n");
}

void __ShowPostfixTree(struct TTree* pTree, FCallbackOnValue fShowValue,
		int isCallOnLeave) {
	_isCallOnLeave = isCallOnLeave;
	__fCallbackPostfix = fShowValue;
	printf("__ShowPostfixTree -> ");
	__RecurPostfix(_Root(pTree));
	printf("\n");
}

void __ShowLevelTree(struct TTree* pTree, FCallbackOnValue fShowValue,
		int width) {
	int deep = __GetRecurDeep(pTree->_header->pParent);
	int nodesInLevel, level, number;
	int halfSpaceLength;
	int cc, chs;
	_TPNode pn;

	static char t1[] = "";
	static char t2[] = " ";
	const char * trailer;
	int halfWidth;
	char* halfSpace=NULL;
	if (width % 2 == 0) {
		halfWidth = (width + 2) / 2;
		trailer = t2;
	} else {
		halfWidth = (width + 1) / 2;
		trailer = t1;
	}
	halfSpace = calloc(halfWidth + 1, sizeof(char));
	if (!halfSpace)
		exit(1);
	for (cc = 0; cc < halfWidth; ++cc)
		halfSpace[cc] = ' ';
	halfSpace[cc] = '\0';

	puts("__ShowByLevels ->");

	for (level = 0, nodesInLevel = 1, halfSpaceLength = (1 << (deep - 1)) - 1; level
			< deep; ++level, nodesInLevel <<= 1, halfSpaceLength >>= 1) {
		for (number = 0; number < nodesInLevel; ++number) {
			pn = __GetNodeByLevelAndNumber(_Root(pTree), level, number);
			for (chs = 0; chs < halfSpaceLength; ++chs)
				printf(halfSpace);
			if (pn) {
				fShowValue(&pn->value);
				pn->color == _ctBlack ? printf("B") : printf("R");
			} else {
				fShowValue(NULL);
				printf(" ");
			}
			printf(trailer);
			for (chs = 0; chs < halfSpaceLength; ++chs)
				printf(halfSpace);
		}
		printf("\n");
	}
	free(halfSpace);
}
/* ------------------------------------------------------------------------- */
/* Definition of utilities funtions                                          */
/* ------------------------------------------------------------------------- */

static void _RecurInfix(_TPNode iter){
	return;
}

static void __RecurPrefix(_TPNode iter){
	return;
}

/* ------------------------------------------------------------------------- */

static void __RecurPostfix(_TPNode iter){
	return;
}

/* ------------------------------------------------------------------------- */

static int __GetRecurDeep(_TPNode iter){
	return;
}

/* ------------------------------------------------------------------------- */

static _TPNode __GetNodeByLevelAndNumber(_TPNode iter, int level, int number){
	return;
}

/* ------------------------------------------------------------------------- */

static _TPNode _Root(struct TTree* pTre){
	return;
}

/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */
