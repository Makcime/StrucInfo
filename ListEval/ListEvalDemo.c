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
#include "list.h"
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
void swap(...)
{
   ...
}
/* ------------------------------------------------------------------------- */
void ShowList(...)
{
    ...
}

void BubbleSort(...)
{
 ...
}

/*
0 , 0 0
1 0 0 , 1 0 0 1
2 1 0 0 1 , 2 1 0 0 1 2
3 2 1 0 0 1 2 , 3 2 1 0 0 1 2 3
...
9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 , 9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9 
 
*/
void InsertInts(...)
{
    ...
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
