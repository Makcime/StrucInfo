/*
 ============================================================================
 Name        : SetDemo.c
 Author      : Mattens JM
 Version     : 1.1
 Copyright   :
 Description : Test of set, Ansi-style
 ============================================================================
 */
/* ------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "set.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
/* Definition of function compare elements                                   */
bool LessChar(char c1, char c2)
{
    return (c1 < c2);
}
/* ------------------------------------------------------------------------- */
void ShowSet(struct TSet* pSet)
{
    TIteratorSet iter;
    printf("ShowSet -> ");
    printf("empty: %d", IsEmptySet(pSet));
    printf(", size: %d -> ", SizeOfSet(pSet));
    for(iter = BeginOfSet(pSet); iter != EndOfSet(pSet); iter = NextInSet(iter)) {
        printf("%2c", *GetPDataInSet(iter));
    }
    puts("");
}

int main(void)
{
    struct TSet* pSet = CreateSet(LessChar);
    char a = 'A', b = 'B', c = 'C', d = 'D';
    printf("struct TSet* pSet = CreateSet(LessPtr) ...\n");
    ShowSet(pSet);
    printf("AddInSet(pSet,&a)-> %d\n", AddInSet(pSet, &a));
    ShowSet(pSet);
    printf("AddInSet(pSet,&b)-> %d\n", AddInSet(pSet, &b));
    ShowSet(pSet);
    printf("AddInSet(pSet,&a)-> %d\n", AddInSet(pSet, &a));
    ShowSet(pSet);
    printf("AddInSet(pSet,&d)-> %d\n", AddInSet(pSet, &d));
    ShowSet(pSet);
    printf("AddInSet(pSet,&c)-> %d\n", AddInSet(pSet, &c));
    ShowSet(pSet);
    printf("IsElementOfSet(pSet,&c)-> %d\n", IsElementOfSet(pSet, &c));
    printf("RemoveFromSet(pSet,&c)-> %d\n", RemoveFromSet(pSet, &c));
    ShowSet(pSet);
    printf("RemoveFromSet(pSet,&c)-> %d\n", RemoveFromSet(pSet, &c));
    ShowSet(pSet);

    DestroySet(pSet);
    return EXIT_SUCCESS;
}
