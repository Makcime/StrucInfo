/*
 * set.h
 *
 *  Created on:
 *  Author: Mattens
 */
/* ------------------------------------------------------------------------- */
#ifndef SET_H_
#define SET_H_
/* ------------------------------------------------------------------------- */
#include <stddef.h>
#include "tforset.h"
#include "../Tree/src/allocator.h"
#include "../Tree/src/tree.h"
/* ------------------------------------------------------------------------- */
struct TSet;
typedef TIteratorTree TIteratorSet;

/* ------------------------------------------------------------------------- */
typedef int (*TCompSet)(TKeySet, TKeySet);
/* ------------------------------------------------------------------------- */
struct TSet* CreateSet(TComp __KeyCompare);
int IsEmptySet(struct TSet* pSet);
int SizeOfSet(struct TSet* pSet);
TIteratorSet BeginOfSet(struct TSet* pSet);	
TIteratorSet EndOfSet(struct TSet* pSet);
TIteratorSet NextInSet(TIteratorSet iter);
TValueSet* GetPDataInSet(TIteratorSet iter);
int AddInSet(struct TSet* pSet,const TValueSet* val);
int RemoveFromSet(struct TSet* pSet, const TValueSet* val);
int IsElementOfSet(struct TSet* pSet, const TValueSet* val);
void DestroySet(struct TSet* pSet);
/* ------------------------------------------------------------------------- */
#endif /* SET_H_ */
