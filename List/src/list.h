/*
 * list.h
 *
 * 
 * Author: mattens
 */

#ifndef LIST_H_
#define LIST_H_
/* ------------------------------------------------------------------------- */
#include <stddef.h>
#include "tforlist.h"
/* ------------------------------------------------------------------------- */
typedef void (*FCallbackOnValue)(TValueList*);
/* ------------------------------------------------------------------------- */
struct TList;
struct __TNodeList;
typedef struct __TNodeList* TIteratorList;
/* ------------------------------------------------------------------------- */

TIteratorList BeginOfList(struct TList* pList);
TIteratorList EndOfList(struct TList* pList);

int IsEmptyList(struct TList* pList);
int SizeOfList(struct TList* pList);

TIteratorList NextInList(TIteratorList iter);
TIteratorList PreviousInList(TIteratorList iter);

TValueList* GetPDataInList(TIteratorList iter);

void InsertInList(struct TList* pList, TIteratorList iter, TValueList * value);

struct TList* CreateList();
DestroyList(struct TList* pList);

TIteratorList EraseInList(struct TList* pList, TIteratorList iter);

void WalkSequenceList(FCallbackOnValue cb, TIteratorList startIt ,TIteratorList stopIt);
EraseSequenceInList(struct TList* pList, TIteratorList startIt, TIteratorList stopIt);



/* ------------------------------------------------------------------------- */
#endif /* LIST_H_ */
