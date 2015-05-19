
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
    TComp _KeyCompare; /* because pTree->_KeyCempare not accessible */
};
/* ------------------------------------------------------------------------- */
/* Definition of function to get key                  */
/* TODO ... */
/* ------------------------------------------------------------------------- */
/* Definitions of functions declared in set.h */
/* ------------------------------------------------------------------------- */
struct TSet* CreateSet(TComp __KeyCompare){
	return;	
}
/* ------------------------------------------------------------------------- */
int IsEmptySet(struct TSet* pSet){
	return;	
}
/* ------------------------------------------------------------------------- */
int SizeOfSet(struct TSet* pSet){
	return;	
}
/* ------------------------------------------------------------------------- */
TIteratorSet BeginOfSet(struct TSet* pSet){
	return;	
}
/* ------------------------------------------------------------------------- */
TIteratorSet EndOfSet(struct TSet* pSet){
	return;	
}
/* ------------------------------------------------------------------------- */
TIteratorSet NextInSet(TIteratorSet iter){
	return;	
}
/* ------------------------------------------------------------------------- */
TValueSet* GetPDataInSet(TIteratorSet iter){
	return;	
}
/* ------------------------------------------------------------------------- */
int AddInSet(struct TSet* pSet, TValueSet* val){
	return;	
}
/* ------------------------------------------------------------------------- */
int RemoveFromSet(struct TSet* pSet, TValueSet* val){
	return;	
}
/* ------------------------------------------------------------------------- */
int IsElementOfSet(struct TSet* pSet , TValueSet* val){
	return;	
}
/* ------------------------------------------------------------------------- */
void DestroySet(struct TSet* pSet){
	return;	
}
/* ------------------------------------------------------------------------- */
