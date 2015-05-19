/*
 * tree.h
 *
 *  Created on: 19-févr.-2009
 *      Author: mattens
 */
/* ------------------------------------------------------------------------- */
#ifndef TREE_H_
#define TREE_H_
/* ------------------------------------------------------------------------- */
#include <stddef.h>
#include "tfortree.h"
#include "allocator.h"
/* ------------------------------------------------------------------------- */
typedef TKeyTree (*TKeyOf)(const TValueTree*);
typedef int (*TComp)(TKeyTree, TKeyTree);
typedef void (*FCallbackOnValue)(TValueTree*);
/* ------------------------------------------------------------------------- */
struct TTree;
struct __TNodeTree;
typedef struct __TNodeTree* TIteratorTree;
/* ------------------------------------------------------------------------- */
/* TODO ...                                                                  */
struct TTree* CreateTree(TKeyOf __KeyOf, TComp __KeyCompare);
TKeyTree GetKeyInTree(struct TTree* pTree, TIteratorTree it);
TValueTree* GetPDataInTree(TIteratorTree it);
TIteratorTree BeginOfTree(struct TTree* pTree);
TIteratorTree EndOfTree(struct TTree* pTree);
int IsEmptyTree(struct TTree* pTree);
int SizeOfTree(struct TTree* pTree);
TIteratorTree NextInTree(TIteratorTree it);
TIteratorTree PreviousInTree(TIteratorTree it);
void InsertInTree(struct TTree* pTree, const TValueTree* data);
TIteratorTree RegInsertInTree(struct TTree* pTree, const TValueTree* data);
TIteratorTree EraseInTree(struct TTree* pTree, TIteratorTree it);
void EraseKeysInTree(struct TTree* pTree, TKeyTree k);
TIteratorTree UpperBoundInTree(struct TTree* pTree, TKeyTree k);
TIteratorTree LowerBoundInTree(struct TTree* pTree, TKeyTree k);
void WalkTree(struct TTree* pTree, FCallbackOnValue cb);
void EraseSequenceInTree(struct TTree* pTree, TIteratorTree first, TIteratorTree last);

/* Red Black trees Functions ----------------------------------------------- */
void RotateLeft(struct TTree* pTree, TIteratorTree x);
void RotateRight(struct TTree* pTree, TIteratorTree x);
void RedBlackFixUp(struct TTree* pTree, TIteratorTree x);
void RedBlackInsert( struct TTree* pTree, const TValueTree* data );


/* ------------------------------------------------------------------------- */
void __ShowPrefixTree(struct TTree* pTree, FCallbackOnValue fShowValue,
                      int isCallOnLeave);
void __ShowPostfixTree(struct TTree* pTree, FCallbackOnValue fShowValue,
                       int isCallOnLeave);
void __ShowInfixTree(struct TTree* pTree, FCallbackOnValue fShowValue,
                     int isCallOnLeave);
void __ShowLevelTree(struct TTree* pTree, FCallbackOnValue fShowValue,
                     int width);
/* ------------------------------------------------------------------------- */
#endif /* TREE_H_ */
