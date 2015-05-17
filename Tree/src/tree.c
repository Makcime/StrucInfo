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
static _TPNode _Root(struct TTree* pTree);

/* ------------------------------------------------------------------------- */
static bool _isCallOnLeave = false;
static FCallbackOnValue _fCallbackInfix = 0;
static FCallbackOnValue __fCallbackPrefix = 0;
static FCallbackOnValue __fCallbackPostfix = 0;
/* ------------------------------------------------------------------------- */
/* Definition of funtions declared in tree.h                                 */

/* ------------------------------------------------------------------------- */
struct TTree* CreateTree(TKeyOf __KeyOf, TComp __KeyCompare){
	
	struct TTree* tree = malloc(sizeof(struct TTree));

	tree->_KeyOf = __KeyOf;
	tree->_KeyCompare = __KeyCompare;

	tree->_pAllocator = CreateAllocator(sizeof(_TNode));

	tree->_nodeCount = 0;

	tree->_header = _CreateHeaderNode(tree->_pAllocator);

	return tree;
}

/* ------------------------------------------------------------------------- */
TKeyTree GetKeyInTree(struct TTree* pTree, TIteratorTree it){
	return pTree->_KeyOf(&it->value);
}

/* ------------------------------------------------------------------------- */
TValueTree* GetPDataInTree(TIteratorTree it){
	return &it->value; 
}

/* ------------------------------------------------------------------------- */
TIteratorTree BeginOfTree(struct TTree* pTree){
	return pTree->_header->pLeft; 
}

/* ------------------------------------------------------------------------- */
TIteratorTree EndOfTree(struct TTree* pTree){
	// return pTree->_header->pRight->pRight; 
	// return pTree->_header->pRight; 
	return pTree->_header; 
}

/* ------------------------------------------------------------------------- */
bool IsEmptyTree(struct TTree* pTree){
	if(pTree->_nodeCount <= 0)
		return true;
	else
		return false;
}

/* ------------------------------------------------------------------------- */
int SizeOfTree(struct TTree* pTree){
	return pTree->_nodeCount;
}

/* ------------------------------------------------------------------------- */
TIteratorTree NextInTree(TIteratorTree it){
	TIteratorTree pNext = it;

	if(it->pRight){
		pNext = it->pRight;
		while(pNext->pLeft && pNext->pParent->pParent != pNext)
			pNext = pNext->pLeft;
	}else{
		while(pNext->pParent->pParent != pNext )
			if(pNext->pParent->pLeft == pNext)
				return pNext->pParent;
			else
				pNext = pNext->pParent;
	}
	return pNext;
}

/* ------------------------------------------------------------------------- */
TIteratorTree PreviousInTree(TIteratorTree it){
	TIteratorTree pPrev = it;

	if(GetPDataInTree(it)->ptr == NULL){
		pPrev = it->pRight;
	}
	else if(it->pLeft){
		pPrev = it->pLeft;
		while(pPrev->pRight)
			pPrev = pPrev->pRight;
	}
	else{
		while(pPrev->pParent->pParent != pPrev){
			if(pPrev->pParent->pRight == pPrev)
				return pPrev->pParent;
			else
				pPrev = pPrev->pParent;
		}
	}
	return pPrev;
}

/* ------------------------------------------------------------------------- */
void InsertInTree(struct TTree* pTree, const TValueTree* data){

	_TPNode node = _CreateNode(data, NULL, NULL, NULL, _ctBlack, pTree->_pAllocator);
	// printf("(%02x,%02d) ", GetPDataInTree(node)->ptr, GetPDataInTree(node)->size);
	printf("(%02d,%02d) \n", pTree->_KeyOf(&node->value), GetPDataInTree(node)->size);
	TIteratorTree next, parent;

	int side = 0;

	if(_Root(pTree)){
		next = _Root(pTree);
		// printf("Root =  %02x\n", GetPDataInTree(next)->ptr);
		parent = next;
		while(next && next != pTree->_header){
			parent = next;
			if(pTree->_KeyCompare(pTree->_KeyOf(&node->value), pTree->_KeyOf(&next->value))){
				next = parent->pLeft;
				side = 1;

			}else{
				next = parent->pRight;
				side = 2;
				// if (next == pTree->_header)
					// next = NULL;
			}
		}
		node->pParent = parent;
		if (side==1){
			parent->pLeft = node;
			// printf("fils de gauche de pute de %02x\n", GetPDataInTree(parent)->ptr);
		}
		else{
			parent->pRight = node;
			// printf("fils de pd de droite %02x\n", GetPDataInTree(parent)->ptr);
		}

		if(pTree->_KeyCompare(pTree->_KeyOf(&node->value), 
					pTree->_KeyOf(&pTree->_header->pLeft->value))){
			// printf("%02x plus petit %02x \n", pTree->_KeyOf(&node->value), pTree->_KeyOf(&pTree->_header->pLeft->value));
			pTree->_header->pLeft = node;
		}else if(pTree->_KeyCompare(pTree->_KeyOf(&pTree->_header->pRight->value),
					pTree->_KeyOf(&node->value))){
			// printf("%02x plus grand %02x \n", pTree->_KeyOf(&node->value), pTree->_KeyOf(&pTree->_header->pRight->value));
			pTree->_header->pRight = node;
			node->pRight = pTree->_header;
		}

	}else{
		pTree->_header->pParent = node;
		pTree->_header->pLeft = node;
		pTree->_header->pRight = node;
		node->pParent = pTree->_header;
		// node->pRight = pTree->_header;


	}
	pTree->_nodeCount++;
}

/* ------------------------------------------------------------------------- */
TIteratorTree EraseInTree(struct TTree* pTree, TIteratorTree it){

    TIteratorTree next = NextInTree(it);
	TIteratorTree prev = pTree->_header;
    
	if(iter!=pTree->_header->pLeft)
    	prev = PreviousInTree(it);

    // 1. si it n'a pas d'enfant
    if( (it->pLeft == NULL && it->pRight == NULL) || it->pRight->pRight == it){
        if(it->pParent->pLeft == it){ 
            it->pParent->pLeft = NULL;
            if (pTree->_header->pLeft == it)
                pTree->_header->pLeft = next;
        }
        else if (it->pParent->pRight == it){
            it->pParent->pRight = NULL; 
            if (pTree->_header->pRight == it)
                pTree->_header->pRight = prev;
        }
        else{   // il ne reste que le Root dans l arbre
            it->pParent->pParent = NULL;
            it->pParent->pLeft = it->pParent;
            it->pParent->pRight = it->pParent;
        }                
    }
    // 2. si it n'a pas un fils droit
    else if(!it->pRight){
        // on relie le fils gauche de it au pere de it               
        if(it->pParent->pLeft == it){ 
            it->pParent->pLeft = it->pLeft; 
        }
        else if(it->pParent->pRight == it){ 
            it->pParent->pRight = it->pLeft;
        }else{  // it est le Root
            it->pParent->pParent = it->pLeft;
        }
        it->pLeft->pParent = it->pParent;        
    }
    // 3. si it a un fils droit
    else{
        // on remplace it par son "suivant" 
        if(!it->pRight->pLeft){
        	next->pLeft = it->pLeft;

        	if (it->pLeft)
        		it->pLeft->pParent = next;

        	next->pParent = it->pParent;

	        if(it->pParent->pLeft == it){ 
	            it->pParent->pLeft = next;            
	        }
	        else if(it->pParent->pRight == it){ 
	            it->pParent->pRight = next;
	        }    
	        else{ // it est le Root
	            it->pParent->pParent = next;            
	        }
        }else{
            next->pParent->pLeft = next->pRight;
            next->pRight = it->pRight;
            next->pLeft = it->pLeft;
            next->pParent = it->pParent;  

	        if(it->pParent->pLeft == it){ 
	            it->pParent->pLeft = next;            
	        }
	        else if(it->pParent->pRight == it){ 
	            it->pParent->pRight = next;
	        }    
	        else{ // it est le Root
	            it->pParent->pParent = next;            
	        }      
        }


        // next->pParent = it->pParent;
        // 3.1. si fils droit de it n'a pas de fils gauche
        // if(next->pLeft != NULL){
        //     next->pLeft = it->pLeft;
        //     it->pLeft->pParent = it->pRight;
        // }
        // 3.2. si fils droit de it a un fils gauche
        // else{
        //     next->pParent->pLeft = next->pRight;
        //     next->pRight = it->pRight;
        //     next->pLeft = it->pLeft;
        //     next->pParent = it->pParent;
        // }
    }

    if (pTree->_header->pLeft == it)
        pTree->_header->pLeft = next;
    if (pTree->_header->pRight == it)
        pTree->_header->pRight = prev;
        
    // Deallocate(pTree->_pAllocator,it);
    pTree->_nodeCount--;
    printf("begin = (%x , %d)\n", GetPDataInTree(BeginOfTree(pTree))->ptr, GetPDataInTree(BeginOfTree(pTree))->size);
    // printf("next = (%x , %d)\n", GetPDataInTree(next)->ptr, GetPDataInTree(next)->size);
    // printf("parent de next = (%x , %d)\n", GetPDataInTree(next->pParent)->ptr, GetPDataInTree(next->pParent)->size);
    return next;
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
	TIteratorTree iter = BeginOfTree(pTree);
	TIteratorTree end =	EndOfTree(pTree);
	while((!pTree->_KeyCompare(k, pTree->_KeyOf(&iter->value))) && iter != end)
		iter = NextInTree(iter);
	return iter;
}

/* ------------------------------------------------------------------------- */
TIteratorTree LowerBoundInTree(struct TTree* pTree, TKeyTree k){
	TIteratorTree iter = BeginOfTree(pTree);
	TIteratorTree end =	EndOfTree(pTree);
	while(pTree->_KeyCompare(pTree->_KeyOf(&iter->value), k) && iter != end)
		iter = NextInTree(iter);
	return iter;
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
	printf("deep = %d \n", deep);
	getchar();
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

static _TPNode _CreateHeaderNode(struct TAllocator* pAllocator){
	_TPNode header = Allocate(pAllocator);

	header->pParent = NULL;
	header->pLeft = header;
	header->pRight = header;

	return header;
}

static _TPNode _CreateNode(const TValueTree* pv, const _TPNode _pParent,
		const _TPNode _pLeft, const _TPNode _pRight, _TColorType _color,
		struct TAllocator* pAllocator){
	
	_TPNode node = Allocate(pAllocator);

	node->pParent = _pParent;
	node->pLeft = _pLeft;
	node->pRight = _pRight;
	node->color = _color;
	node->value = *pv;

	return node;

}

/* ------------------------------------------------------------------------- */

static void _RecurInfix(_TPNode iter){

	if(iter)
		_RecurInfix(iter->pLeft);
	
	if(iter )
		_fCallbackInfix(&iter->value);
	else
		if (_isCallOnLeave)
			_fCallbackInfix(NULL);

	if(iter)
		if(iter->pRight && iter->pRight->pRight != iter)
			_RecurInfix(iter->pRight);
		else
			if (_isCallOnLeave)
				_RecurInfix(NULL);

	return;

	// if (iter->pLeft!=NULL)	_RecurInfix(iter->pLeft);
	// else{
	// 	if (_isCallOnLeave)
	// 	_fCallbackInfix(NULL);
	// }
	// 	_fCallbackInfix(&iter->value);
	// if (iter->pRight!=NULL)	_RecurInfix(iter->pRight);
	// else{
	// 	if(_isCallOnLeave)
	// 		_fCallbackInfix(NULL);
	// 	}
}

/* ------------------------------------------------------------------------- */
static void __RecurPrefix(_TPNode iter){

	if(iter)
		__fCallbackPrefix(&iter->value);
	else
		__fCallbackPrefix(NULL);

	if(iter)
		__RecurPrefix(iter->pLeft);

	if(iter)	
		if(iter->pRight && iter->pRight->pRight != iter)
			__RecurPrefix(iter->pRight);
		else
			__RecurPrefix(NULL);

	return;
}

/* ------------------------------------------------------------------------- */

static void __RecurPostfix(_TPNode iter){
	if(iter)
		__RecurPostfix(iter->pLeft);

	if(iter)	
		if(iter->pRight && iter->pRight->pRight != iter)
			__RecurPostfix(iter->pRight);
		else
			__RecurPostfix(NULL);

	if(iter) 
		__fCallbackPostfix(&iter->value);
	else
		__fCallbackPostfix(NULL);
	return;
}

/* ------------------------------------------------------------------------- */

static int __GetRecurDeep(_TPNode iter){
	if(iter){
		if(iter->pRight && iter->pRight->pRight != iter){
			return 1 + (__GetRecurDeep(iter->pLeft) >= __GetRecurDeep(iter->pRight) ?
			__GetRecurDeep(iter->pLeft):__GetRecurDeep(iter->pRight));
		}else
			return 1 + (__GetRecurDeep(iter->pLeft) >= __GetRecurDeep(NULL) ?
			__GetRecurDeep(iter->pLeft):__GetRecurDeep(NULL));
	}
	else
		return 0;
}

/* ------------------------------------------------------------------------- */

static _TPNode __GetNodeByLevelAndNumber(_TPNode iter, int level, int number){
 if(!iter)
		return NULL;
	 if(level == 0)
		return iter;

	if (number / (1<<(level -1))==0)
		return __GetNodeByLevelAndNumber(iter->pLeft,level-1, number % (1<<(level -1)));
	else{
		if(iter->pRight && iter->pRight->pRight != iter)
			return __GetNodeByLevelAndNumber(iter->pRight,level-1, number % (1<<(level -1)));
		else
			return __GetNodeByLevelAndNumber(NULL,level-1, number % (1<<(level -1)));
	}
}

/* ------------------------------------------------------------------------- */

static _TPNode _Root(struct TTree* pTree){
	return pTree->_header->pParent;
}

/* ------------------------------------------------------------------------- */
