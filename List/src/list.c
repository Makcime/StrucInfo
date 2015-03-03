/*
 * list.c
 *
 * 
 * Author: mattens
 */
/* ------------------------------------------------------------------------- */
#define __DEBUG 0
/* ------------------------------------------------------------------------- */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
struct TList {
	struct __TNodeList* _pEndNode;
	size_t _nodeCount;
};
/* ------------------------------------------------------------------------- */
typedef struct __TNodeList _TNode;
typedef struct __TNodeList* _TPNode;
struct __TNodeList {
	struct __TNodeList * pPrevious;
	struct __TNodeList * pNext;
	TValueList value;
};
/* ------------------------------------------------------------------------- */
/* Declaration of prototypes of utilities funtions                           */
static _TPNode _CreateHeaderNode();
static _TPNode _CreateNode(const TValueList* pv, const _TPNode _pPrevious,
		const _TPNode _pNext);
/* ------------------------------------------------------------------------- */
/* Definition of funtions declared in list.h                                 */
TIteratorList BeginOfList(struct TList* pList){
	return;
}

/*--------------------------------------------------------------------*/
TIteratorList EndOfList(struct TList* pList){
	return;
}

/*--------------------------------------------------------------------*/
int IsEmptyList(struct TList* pList){
	return;
}

/*--------------------------------------------------------------------*/
int SizeOfList(struct TList* pList){
	return;
}

/*--------------------------------------------------------------------*/
struct TList* GetPDataInList(TIteratorList iter){
	return;
}

/*--------------------------------------------------------------------*/
void InsertInList(struct TList* pList, TIteratorList iter, TValueList * value){
	return;
}

/*--------------------------------------------------------------------*/
/* ------------------------------------------------------------------------- */
/* Definition of utilities funtions                                          */
/* ...                                                                       */
/* ...                                                                       */
/* ...                                                                       */
/* ------------------------------------------------------------------------- */

