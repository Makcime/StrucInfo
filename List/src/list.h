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

struct TList* GetPDataInList(TIteratorList iter);

void InsertInList(struct TList* pList, TIteratorList iter, TValueList * value);

/* ------------------------------------------------------------------------- */
#endif /* LIST_H_ */
