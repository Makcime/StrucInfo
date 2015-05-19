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
struct TTree* CreateTree(TKeyOf __KeyOf, TComp __KeyCompare) {

    struct TTree* tree = (struct TTree*) malloc(sizeof(struct TTree));

    tree->_KeyOf = __KeyOf;
    tree->_KeyCompare = __KeyCompare;
    tree->_nodeCount = 0;

    tree->_pAllocator = CreateAllocator(sizeof(_TNode));
    tree->_header = _CreateHeaderNode(tree->_pAllocator);

    return tree;
}

/* ------------------------------------------------------------------------- */
TKeyTree GetKeyInTree(struct TTree* pTree, TIteratorTree it) {
    return pTree->_KeyOf(&it->value);
}

/* ------------------------------------------------------------------------- */
TValueTree* GetPDataInTree(TIteratorTree it) {
    return &it->value;
}

/* ------------------------------------------------------------------------- */
TIteratorTree BeginOfTree(struct TTree* pTree) {
    return pTree->_header->pLeft;
}

/* ------------------------------------------------------------------------- */
TIteratorTree EndOfTree(struct TTree* pTree) {
    return pTree->_header;
}

/* ------------------------------------------------------------------------- */
bool IsEmptyTree(struct TTree* pTree) {
    if(pTree->_nodeCount <= 0) return true;
    else return false;
}

/* ------------------------------------------------------------------------- */
int SizeOfTree(struct TTree* pTree) {
    return pTree->_nodeCount;
}

/* ------------------------------------------------------------------------- */
TIteratorTree NextInTree(TIteratorTree it) {
    TIteratorTree pNext = it;

    // Si pas de fils droit, on remontre dans l'arbre
    // jusqu'à être le fils gauche de mon parent
    // ou si on est Root
    if (!pNext->pRight) {
        while ((pNext != pNext->pParent->pLeft) && (pNext!=pNext->pParent->pParent)) {
            pNext = pNext->pParent;
        }
        return pNext->pParent;

    } else { 	//prendre le plus à gauche du fils droit
        pNext = pNext->pRight;
        // tant que j'ai un fils de gauche et que l'arbre n'est pas vide
        while (pNext->pLeft && pNext->pLeft != pNext) {
            // while (pNext->pLeft && pNext->pLeft->pParent) {
            pNext = pNext->pLeft;
        }
        return pNext;
    }
}

/* ------------------------------------------------------------------------- */
TIteratorTree PreviousInTree(TIteratorTree it) {
    TIteratorTree pPrev = it;

    // Suis-je le header Node ?

    // suis-je le parent de de mon parent?
    // et ai-je un fils de droite?
    if((it->pParent->pParent == it) && it->pRight != NULL) {
        // mon fils droit a-t-il un fils droit?
        if(!it->pRight->pRight) {
            if((it->pRight == it->pParent)) { // si mon fils droit est mon parent
                pPrev = it->pRight;
                return pPrev;
                // alors je suis le header et le max est le root
            } else if(it->pRight->pParent != it) { // si je ne suis pas le parent de mon fils droit
                pPrev = it->pRight;	// alors je suis le header
                return pPrev;	// alors je suis le header
            } // sinon je suis le root
        }
    }

    // Dans tout les autres cas je suis un noeud dans l'arbre
    // else if(pPrev->pLeft){ // si j'ai un fils gauche
    if(pPrev->pLeft) { // si j'ai un fils gauche
        pPrev = pPrev->pLeft;
        while(pPrev->pRight) // prendre le plus à droite de ce fils gauche
            pPrev = pPrev->pRight;
        // return pPrev;
    }
    else { // sinon relonter dans l'arbre
        while(pPrev->pParent->pRight != pPrev) { // jusquà être le fils droit de mon parent
            pPrev = pPrev->pParent; //on remonte dans l'arbre
        }
        // return pPrev->pParent;
        pPrev = pPrev->pParent;
    }

    return pPrev;
}

/* ------------------------------------------------------------------------- */
void InsertInTree(struct TTree* pTree, const TValueTree* data) {
    // RegInsertInTree(pTree, data);
    RedBlackInsert(pTree, data);

}
/* ------------------------------------------------------------------------- */
TIteratorTree RegInsertInTree(struct TTree* pTree, const TValueTree* data) {

    _TPNode node = _CreateNode(data, NULL, NULL, NULL, _ctRed, pTree->_pAllocator);
    TIteratorTree next, parent;

    int side = 0;

    // si l'arbre n'est pa vide :
    if(_Root(pTree)) {
        next = _Root(pTree);
        while(next && next != pTree->_header) {
            parent = next;
            if(pTree->_KeyCompare(pTree->_KeyOf(&node->value), pTree->_KeyOf(&next->value))) {
                next = parent->pLeft;
                side = 1;
            } else {
                next = parent->pRight;
                side = 2;
            }
        }
        node->pParent = parent;
        if ( side == 1 ) {
            parent->pLeft = node;
        }
        else {
            parent->pRight = node;
        }

        if(pTree->_KeyCompare(pTree->_KeyOf(&node->value),
                              pTree->_KeyOf(&pTree->_header->pLeft->value))) {
            pTree->_header->pLeft = node;
        }
        if(!pTree->_KeyCompare(pTree->_KeyOf(&node->value),
                               pTree->_KeyOf(&pTree->_header->pRight->value))) {
            pTree->_header->pRight = node;
        }

    } else {
        pTree->_header->pParent = node;
        pTree->_header->pLeft = node;
        pTree->_header->pRight = node;
        node->pParent = pTree->_header;
        node->color = 	_ctBlack;
        // node->pRight = pTree->_header;
    }
    pTree->_nodeCount++;

    return node;
}

/* ------------------------------------------------------------------------- */
TIteratorTree EraseInTree(struct TTree* pTree, TIteratorTree it) {

    TIteratorTree next = NextInTree(it);
    TIteratorTree prev = pTree->_header;

    // Si je ne suis pas le plus petit dans l'arbre
    if(it != pTree->_header->pLeft)
        prev = PreviousInTree(it);

    /* *** 1. si je n'ai pas d'enfant *** */
    // if( (it->pLeft == NULL && it->pRight == NULL) || it->pRight->pRight == it){
    if(!it->pLeft && !it->pRight) {

        //cas où il ne reste que le root!
        // if(pTree->_header->pLeft == pTree->_header->pRight){
        if(pTree->_nodeCount == 1) {
            // printf("cas où il ne reste que le root!\n");
            pTree->_header->pParent = NULL;
            pTree->_header->pLeft = pTree->_header;
            pTree->_header->pRight = pTree->_header;
        }

        // Je suis un enfant de gauche
        if(it->pParent->pLeft == it) {
            it->pParent->pLeft = NULL; // effacer l'enfant de gauche de mon parent
            // mettre a jour le debut d'arbre
            if (pTree->_header->pLeft == it)
                pTree->_header->pLeft = next;
        }

        // Je suis un enfant de droite
        else if (it->pParent->pRight == it) {
            it->pParent->pRight = NULL; // effacer l'enfant de droite de mon parent
            // mettre a jour la fin d'arbre
            if (pTree->_header->pRight == it) {
                pTree->_header->pRight = prev;
            }

        }
    }

    /* *** 2. si j'ai uniquement un fils droit *** */
    else if(it->pRight && !it->pLeft) {

        // Si je suis le root
        if(it->pParent->pParent == it) {
            it->pParent->pParent = it->pRight; // le parent du header node devient mon fils droit
            it->pRight->pParent = it->pParent; // le parent de mon fils droit devient le header
        }
        // Sinon si je suis un enfant de gauche
        else if(it->pParent->pLeft == it) {
            it->pParent->pLeft = it->pRight; // le fils gauche de mon parent devient mon fils droit
            it->pRight->pParent = it->pParent; // le parent de mon fils droit devient mon parent
        }
        // Sinon si je suis un enfant de droite
        else if(it->pParent->pRight == it) {
            it->pParent->pRight = it->pRight; // le fils gauche de mon parent devient mon fils droit
            it->pRight->pParent = it->pParent; // le parent de mon fils droit devient mon parent
        }

        // mettre a jour le debut d'arbre
        if (pTree->_header->pLeft == it)
            pTree->_header->pLeft = next;
    }

    /* *** 3. si j'ai uniquement un fils gauche *** */
    else if(it->pLeft && !it->pRight) {

        // Si je suis le root
        if(it->pParent->pParent == it) {
            it->pParent->pParent = it->pLeft; // le parent du header node devient mon fils gauche
            it->pLeft->pParent = it->pParent; // le parent de mon fils gauche devient le header
        }
        // Sinon si je suis un enfant de gauche
        else if(it->pParent->pLeft == it) {
            it->pParent->pLeft = it->pLeft; // le fils gauche de mon parent devient mon fils gauche
            it->pLeft->pParent = it->pParent; // le parent de mon fils gauche devient mon parent
        }
        // Sinon si je suis un enfant de droite
        else if(it->pParent->pRight == it) {
            it->pParent->pRight = it->pLeft; // le fils gauche de mon parent devient mon fils droit
            it->pLeft->pParent = it->pParent; // le parent de mon fils gauche mon parent
        }

        // mettre a jour la fin d'arbre
        if (pTree->_header->pRight == it) {
            pTree->_header->pRight = prev;
        }
    }
    /* *** 4. Sinon je possède deux fils*** */
    else {
        // mon suivant prends ma place
        it->pLeft->pParent = next;
        next->pLeft = it->pLeft;
        it->pRight->pParent = it->pParent;

        if(it == it->pParent->pParent) { // si je suis le root
            it->pParent->pParent = it->pRight;
        } else if(it == it->pParent->pLeft) // sinon si je suis un fils gauche
            it->pParent->pLeft = it->pRight;
        else	// sinon je suis un fils droit
            it->pParent->pRight = it->pRight;
    }

    if (pTree->_header->pLeft == it)
        pTree->_header->pLeft = next;
    if (pTree->_header->pRight == it) {
        prev->pRight = pTree->_header;
    }

    pTree->_nodeCount--;
    Deallocate(pTree->_pAllocator, it);

    return next;
}

/* ------------------------------------------------------------------------- */
void EraseKeysInTree(struct TTree* pTree, TKeyTree k) {

    TIteratorTree it = BeginOfTree(pTree), end = EndOfTree(pTree);

    while (it != end) {

        if(!pTree->_KeyCompare(k, pTree->_KeyOf(&it->value))
                && !pTree->_KeyCompare(pTree->_KeyOf(&it->value), k))
            it = EraseInTree(pTree, it);
        else
            it = NextInTree(it);
    }
    // return SizeOfTree(pTree);
    return;
}

void EraseSequenceInTree(struct TTree* pTree, TIteratorTree first, TIteratorTree last) {
    TIteratorTree it = first;
    while (it != last) {
        it = EraseInTree(pTree, it);
    }
    // return it;
    return;
}


/* ------------------------------------------------------------------------- */
TIteratorTree UpperBoundInTree(struct TTree* pTree, TKeyTree k) {
    TIteratorTree iter = BeginOfTree(pTree);
    TIteratorTree end =	EndOfTree(pTree);
    while((!pTree->_KeyCompare(k, pTree->_KeyOf(&iter->value))) && iter != end)
        iter = NextInTree(iter);
    return iter;
}

/* ------------------------------------------------------------------------- */
TIteratorTree LowerBoundInTree(struct TTree* pTree, TKeyTree k) {
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

static _TPNode _CreateHeaderNode(struct TAllocator* pAllocator) {
    _TPNode header = Allocate(pAllocator);

    header->pParent = NULL;
    header->pLeft = header;
    header->pRight = header;

    return header;
}

static _TPNode _CreateNode(const TValueTree* pv, const _TPNode _pParent,
                           const _TPNode _pLeft, const _TPNode _pRight, _TColorType _color,
                           struct TAllocator* pAllocator) {

    _TPNode node = Allocate(pAllocator);

    node->pParent = _pParent;
    node->pLeft = _pLeft;
    node->pRight = _pRight;
    node->color = _color;
    node->value = *pv;

    return node;

}

/* ------------------------------------------------------------------------- */

static void _RecurInfix(_TPNode iter) {

    if(iter)
        _RecurInfix(iter->pLeft);

    if(iter )
        _fCallbackInfix(&iter->value);
    else if (_isCallOnLeave)
        _fCallbackInfix(NULL);

    if(iter)
        _RecurInfix(iter->pRight);

    return;

}

/* ------------------------------------------------------------------------- */
static void __RecurPrefix(_TPNode iter) {

    if(iter)
        __fCallbackPrefix(&iter->value);
    else if (_isCallOnLeave)
        __fCallbackPrefix(NULL);

    if(iter)
        __RecurPrefix(iter->pLeft);

    if(iter)
        __RecurPrefix(iter->pRight);

    return;
}

/* ------------------------------------------------------------------------- */

static void __RecurPostfix(_TPNode iter) {
    if(iter)
        __RecurPostfix(iter->pLeft);

    if(iter)
        __RecurPostfix(iter->pRight);

    if(iter)
        __fCallbackPostfix(&iter->value);
    else if (_isCallOnLeave)
        __fCallbackPostfix(NULL);
    return;
}

/* ------------------------------------------------------------------------- */

static int __GetRecurDeep(_TPNode iter) {
    if(iter) {
        if(iter->pRight && iter->pRight->pRight != iter) {
            return 1 + (__GetRecurDeep(iter->pLeft) >= __GetRecurDeep(iter->pRight) ?
                        __GetRecurDeep(iter->pLeft):__GetRecurDeep(iter->pRight));
        } else
            return 1 + (__GetRecurDeep(iter->pLeft) >= __GetRecurDeep(NULL) ?
                        __GetRecurDeep(iter->pLeft):__GetRecurDeep(NULL));
    }
    else
        return 0;
}

/* ------------------------------------------------------------------------- */

static _TPNode __GetNodeByLevelAndNumber(_TPNode iter, int level, int number) {
    if(!iter)
        return NULL;
    if(level == 0)
        return iter;

    if (number / (1<<(level -1))==0)
        return __GetNodeByLevelAndNumber(iter->pLeft,level-1, number % (1<<(level -1)));
    else {
        if(iter->pRight && iter->pRight->pRight != iter)
            return __GetNodeByLevelAndNumber(iter->pRight,level-1, number % (1<<(level -1)));
        else
            return __GetNodeByLevelAndNumber(NULL,level-1, number % (1<<(level -1)));
    }
}

/* ------------------------------------------------------------------------- */

static _TPNode _Root(struct TTree* pTree) {
    return pTree->_header->pParent;
}

/* ------------------------------------------------------------------------- */
/* Red Black trees Functions ----------------------------------------------- */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

// Definition of a red-black tree
// A red-black tree is a binary search tree which has the following red-black properties:

//     Every node is either red or black.
//     Every leaf (NULL) is black.
//     If a node is red, then both its children are black.
//     Every simple path from a node to a descendant leaf contains the same number of black nodes.


//     implies that on any path from the root to a leaf, red nodes must not be adjacent.

//     However, any number of black nodes may appear in a sequence.

/* ------------------------------------------------------------------------- */

// make a right-leaning link lean to the left
void RotateLeft(struct TTree* pTree, TIteratorTree x) {
    TIteratorTree y;
    y = x->pRight;
    /* Turn y's left sub-tree into x's pRight sub-tree */
    x->pRight = y->pLeft;
    if ( y->pLeft != NULL )
        y->pLeft->pParent = x;
    /* y's new pParent was x's pParent */
    y->pParent = x->pParent;
    /* Set the pParent to point to y instead of x */
    /* First see whether we're at the root */
    if ( x->pParent->pParent == x ) {
        x->pParent->pParent = y;
    }
    else {
        if ( x == (x->pParent)->pLeft )
            /* x was on the pLeft of its pParent */
            x->pParent->pLeft = y;
        else
            /* x must have been on the pRight */
            x->pParent->pRight = y;
    }
    /* Finally, put x on y's pLeft */
    y->pLeft = x;
    x->pParent = y;
    return;
}

// make a Left-leaning link lean to the right
void RotateRight(struct TTree* pTree, TIteratorTree x) {
    TIteratorTree y;
    y = x->pLeft;
    /* Turn y's right sub-tree into x's pLeft sub-tree */
    x->pLeft = y->pRight;
    if ( y->pRight != NULL )
        y->pRight->pParent = x;
    /* y's new pParent was x's pParent */
    y->pParent = x->pParent;
    /* Set the pParent to point to y instead of x */
    /* First see whether we're at the root */
    if ( x->pParent->pParent == x ) {
        x->pParent->pParent = y;
    }
    else {
        if ( x == (x->pParent)->pRight )
            /* x was on the pRight of its pParent */
            x->pParent->pRight = y;
        else
            /* x must have been on the pLeft */
            x->pParent->pLeft = y;
    }
    /* Finally, put x on y's pRight */
    y->pRight = x;
    x->pParent = y;
    return;
}

void RedBlackFixUp(struct TTree* pTree, TIteratorTree it) {
    return;
}

void RedBlackInsert( struct TTree* pTree, const TValueTree* data ) {
    TIteratorTree x, y;
    int debug = 0;
    /* Insert in the tree in the usual way */
    x = RegInsertInTree(pTree, data);

    /* Now restore the red-black property */
    if(_Root(pTree)) {
        while ( (x != _Root(pTree)) && (x->pParent->color == _ctRed) ) {
            if ( x->pParent == x->pParent->pParent->pLeft ) {
                /* If x's pParent is a left, y is x's right 'uncle' */
                y = x->pParent->pParent->pRight;
                if (y && y->color == _ctRed ) {
                    /* case 1 - change the colors */
                    x->pParent->color = _ctBlack;
                    y->color = _ctBlack;
                    x->pParent->pParent->color = _ctRed;
                    /* Move x up the tree */
                    x = x->pParent->pParent;
                }
                else {
                    /* y is a _ctBlack node */
                    if ( x == x->pParent->pRight ) {
                        /* and x is to the right */
                        /* case 2 - move x up and rotate */
                        x = x->pParent;
                        RotateLeft( pTree, x );
                    }
                    /* case 3 */
                    x->pParent->color = _ctBlack;
                    x->pParent->pParent->color = _ctRed;
                    RotateRight( pTree, x->pParent->pParent );
                }
            }
            else {
                /* repeat the "if" part with right and left
                   exchanged */
                y = x->pParent->pParent->pLeft;
                if (y && y->color == _ctRed ) {
                    /* case 1 - change the colors */
                    x->pParent->color = _ctBlack;
                    y->color = _ctBlack;
                    x->pParent->pParent->color = _ctRed;
                    /* Move x up the tree */
                    x = x->pParent->pParent;
                }
                else {
                    /* y is a _ctBlack node */
                    if ( x == x->pParent->pLeft ) {
                        /* and x is to the right */
                        /* case 2 - move x up and rotate */
                        x = x->pParent;
                        RotateRight( pTree, x );
                    }
                    /* case 3 */
                    x->pParent->color = _ctBlack;
                    x->pParent->pParent->color = _ctRed;
                    RotateLeft( pTree, x->pParent->pParent );
                }

            }
        }
    }

    /* Colour the root _ctBlack */
    _Root(pTree)->color = _ctBlack;
}

