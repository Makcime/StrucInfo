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
