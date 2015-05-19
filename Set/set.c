
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
TIteratorSet PreviousInSet(TIteratorSet iter){
	return PreviousInTree(iter);	
}
/* ------------------------------------------------------------------------- */
TValueSet* GetPDataInSet(TIteratorSet iter){
	return GetPDataInTree(iter);	
}
/* ------------------------------------------------------------------------- */
bool AddInSet(struct TSet* pSet, const TValueSet* val){
	if(IsElementOfSet(pSet, val) == false){
		// printf("alors je l'ajoute\n\n");
		InsertInTree(pSet->pTree, val);
		return true;	
	}
	// printf("je ne fais rien \n\n", GetChar(val));
	return false;
}
/* ------------------------------------------------------------------------- */
bool RemoveFromSet(struct TSet* pSet, const TValueSet* val){
	if(IsElementOfSet(pSet, val) == true){
		// printf("alors je l'enleve\n\n", GetChar(val));
		EraseInTree(pSet->pTree, LowerBoundInTree(pSet->pTree, val));
		return true;	
	}
	// printf("je ne fais rien \n\n", GetChar(val));
	return false;
}
/* ------------------------------------------------------------------------- */
bool IsElementOfSet(struct TSet* pSet , const TValueSet* val){

	TIteratorTree LBIter = LowerBoundInTree(pSet->pTree, GetChar(val));

	// printf("it %c - val %c\n", GetChar(GetPDataInTree(LBIter)), GetChar(val));

	if(LBIter == EndOfTree(pSet->pTree)){
		// printf("\n%c n'est pas dans la liste, ", GetChar(val));
		return false;
	}

	if (pSet->_KeyCompare(GetChar(val), GetChar(GetPDataInTree(LBIter)))){
		// printf("\n%c n'est pas dans la liste, ", GetChar(val));
		return false;
	}
	else if(pSet->_KeyCompare(GetChar(GetPDataInTree(LBIter)), GetChar(val))){
		// printf("\n%c n'est pas dans la liste, ", GetChar(val));
		return false;
	} // La data dans le lowerBound est egale à la data dans val
	else{
		// printf("\n%c est dans la liste, ", GetChar(val));
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
