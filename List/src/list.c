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
	_TPNode pPrevious;
	_TPNode pNext;
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
	return pList->_pEndNode->pNext;
}
 
/*--------------------------------------------------------------------*/
TIteratorList EndOfList(struct TList* pList){
	return pList->_pEndNode;
}

/*--------------------------------------------------------------------*/
TIteratorList NextInList(TIteratorList iter){
	return iter->pNext;

}

/*--------------------------------------------------------------------*/
TIteratorList PreviousInList(TIteratorList iter){
	return iter->pPrevious;
}

/*--------------------------------------------------------------------*/
bool IsEmptyList(struct TList* pList){
	return (pList->_nodeCount <= 0);
}

/*--------------------------------------------------------------------*/
int SizeOfList(struct TList* pList){
	return pList->_nodeCount;
}

/*--------------------------------------------------------------------*/
TValueList*  GetPDataInList(TIteratorList iter){
	return &iter->value;
}

/*--------------------------------------------------------------------*/
void InsertInList(struct TList* pList, TIteratorList iter, 
	TValueList * value){

	_TPNode pPrevNode = iter->pPrevious;

	_TPNode pNewNode;

	pNewNode = _CreateNode(value, pPrevNode, iter);
	iter->pPrevious = pNewNode;
	pPrevNode->pNext = pNewNode;
	pList->_nodeCount++;

	return;	
}


/*--------------------------------------------------------------------*/
struct TList* CreateList(){
	struct TList* pList = malloc(sizeof(struct TList));
	pList->_nodeCount = 0;
	pList->_pEndNode = _CreateHeaderNode();
	return pList;
}

/*--------------------------------------------------------------------*/
void DestroyList(struct TList* pList){

	EraseSequenceInList(pList, BeginOfList(pList), EndOfList(pList));
	free(pList->_pEndNode);
	free(pList);
	return;
}

/*--------------------------------------------------------------------*/
TIteratorList EraseInList(struct TList* pList, TIteratorList iter){

	TIteratorList i = iter->pNext ;
	iter->pNext->pPrevious = iter->pPrevious; 
	iter->pPrevious->pNext = iter->pNext;
	free(iter);

	pList->_nodeCount--;

	return i;
}

/*--------------------------------------------------------------------*/
void WalkSequenceList(FCallbackOnValue cb, TIteratorList startIt ,TIteratorList stopIt){
	TIteratorList it;
	for (it = startIt; it != stopIt; cb(&it->value), it = NextInList(it));
	return;
}

/*--------------------------------------------------------------------*/
void EraseSequenceInList(struct TList* pList, TIteratorList startIt, TIteratorList stopIt){

	TIteratorList it;
	for (it = startIt; it != stopIt; free(*GetPDataInList(it)), it = EraseInList(pList, it));
	return;
}


/*--------------------------------------------------------------------*/
/* ------------------------------------------------------------------------- */
/* Definition of utilities funtions                                          */
static _TPNode _CreateHeaderNode(){
	_TPNode _pEndNode = malloc(sizeof(_TNode));
	_pEndNode->pPrevious = _pEndNode;
	_pEndNode->pNext = _pEndNode;
	return _pEndNode;
}
/* ------------------------------------------------------------------------- */
static _TPNode _CreateNode(const TValueList* pv, const _TPNode _pPrevious,
	const _TPNode _pNext){
	_TPNode _pNode = malloc(sizeof(_TNode));
	_pNode->pPrevious = _pPrevious;
	_pNode->pNext = _pNext;
	_pNode->value = *pv;
	return _pNode;
}
/* ------------------------------------------------------------------------- */

