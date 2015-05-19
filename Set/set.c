
/* ------------------------------------------------------------------------- */
#define __DEBUG 0
/* ------------------------------------------------------------------------- */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"
#include "../Tree/src/tree.h"
#include "../Tree/src/allocator.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
struct TSet {
    struct TTree* pTree;
    TCompSet _KeyCompare; /* because pTree->_KeyCempare not accessible */
};
/* ------------------------------------------------------------------------- */
/* Definition of function to get key                  */
const void* GetChar(const TValueSet* pData) {
	return *pData;
}

/* ------------------------------------------------------------------------- */
/* Definitions of functions declared in set.h */
/* ------------------------------------------------------------------------- */
struct TSet* CreateSet(TCompSet __KeyCompare){
    struct TSet* set = (struct TSet*) malloc(sizeof(struct TSet));
	set->pTree= CreateTree(GetChar, __KeyCompare);
	set->_KeyCompare = __KeyCompare;
	return set;	
}
/* ------------------------------------------------------------------------- */
int IsEmptySet(struct TSet* pSet){
	return IsEmptyTree(pSet->pTree);	
}
/* ------------------------------------------------------------------------- */
int SizeOfSet(struct TSet* pSet){
	return SizeOfTree(pSet->pTree);	
}
/* ------------------------------------------------------------------------- */
TIteratorSet BeginOfSet(struct TSet* pSet){
	return BeginOfTree(pSet->pTree);	
}
/* ------------------------------------------------------------------------- */
TIteratorSet EndOfSet(struct TSet* pSet){
	return EndOfTree(pSet->pTree);	
}
/* ------------------------------------------------------------------------- */
TIteratorSet NextInSet(TIteratorSet iter){
	return NextInTree(iter);	
}

/* ------------------------------------------------------------------------- */
TValueSet* GetPDataInSet(TIteratorSet iter){
	return GetPDataInTree(iter);	
}
/* ------------------------------------------------------------------------- */
bool AddInSet(struct TSet* pSet, const TValueSet* val){
	if(!IsElementOfSet(pSet, val)){
		InsertInTree(pSet->pTree, val);
		return true;	
	}
	return false;
}
/* ------------------------------------------------------------------------- */
bool RemoveFromSet(struct TSet* pSet, const TValueSet* val){
	if(IsElementOfSet(pSet, val)){
		EraseInTree(pSet->pTree, LowerBoundInTree(pSet->pTree, GetChar(val)));
		return true;	
	}
	return false;
}
/* ------------------------------------------------------------------------- */
bool IsElementOfSet(struct TSet* pSet , const TValueSet* val){

	TIteratorTree LBIter = LowerBoundInTree(pSet->pTree, GetChar(val));
	
	if (pSet->_KeyCompare(GetChar(val), GetChar(GetPDataInTree(LBIter)))){
		return false;
	}
	else if(pSet->_KeyCompare(GetChar(GetPDataInTree(LBIter)), GetChar(val))){
		return false;
	} // La data dans le lowerBound est egale à la data dans val
	else{
		return true;
	}	

}
/* ------------------------------------------------------------------------- */
void DestroySet(struct TSet* pSet){
	DestroyTree(pSet->pTree);
	free(pSet);
	return;	
}
/* ------------------------------------------------------------------------- */
