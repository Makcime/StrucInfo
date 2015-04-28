/*
 ============================================================================
 Name        : ListEvalDemo.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */
/* ------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../List/src/list.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
void ShowInt(TValueList* pValue)
{
    printf("%10d", *pValue);
}
/* ------------------------------------------------------------------------- */
void swap(struct TList* pList, TIteratorList it, TIteratorList next)
{
    InsertInList(pList, it, GetPDataInList(next));
    EraseInList(pList, next);
   return;
}
/* ------------------------------------------------------------------------- */
void ShowList(struct TList* pList)
{
    int i = 0;
    TIteratorList iter = BeginOfList(pList), end = EndOfList(pList);
    printf("ShowList -> ");
    printf("IsEmptyList(pList) : %d", IsEmptyList(pList));
    printf(", SizeOfList(pList) : %d\n", SizeOfList(pList));
    while (iter != end) {
        if(!(i++ % 8)){
            puts("");
        }
        ShowInt(GetPDataInList(iter));
        iter = NextInList(iter);
    }
    puts("");
}

void BubbleSort(struct TList* pList)
{
    int i;
    TIteratorList it , next, newswap, lastSwap = EndOfList(pList);
    // repeter tant que l'on swap
    while(lastSwap)
    {
        it = BeginOfList(pList);
        next = NextInList(it);
        newswap = NULL;
        // parcourir la liste jusqu'au dernier swap
        while(next != lastSwap){
            if(*GetPDataInList(next) < *GetPDataInList(it)){
                swap(pList, it, next);
                newswap = it;
            }else{
                it = NextInList(it);
            }
            next = NextInList(it);
        }
        lastSwap = newswap;
    }
    return;
}

/*
0 , 0 0
1 0 0 , 1 0 0 1
2 1 0 0 1 , 2 1 0 0 1 2
3 2 1 0 0 1 2 , 3 2 1 0 0 1 2 3
...
9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 , 9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9 
 
*/
void InsertInts(struct TList* pList, int nb)
{
    int i;
    for (i = 0; i < nb; ++i)
    {
        InsertInList(pList, BeginOfList(pList), &i);
        InsertInList(pList, EndOfList(pList), &i);
    }
}

int main(void)
{
    int i = 7;
    struct TList* pList = CreateList();
    puts("struct TList* pList = CreateList() ...");
    ShowList(pList);
    InsertInts(pList, 10);
    ShowList(pList);
    BubbleSort(pList);
    ShowList(pList);
    InsertInList(pList, EndOfList(pList), &i);
    ShowList(pList);
    BubbleSort(pList);
    ShowList(pList);
    puts("\n!!!BYE!!!");
    DestroyList(pList);
    return EXIT_SUCCESS;
}
