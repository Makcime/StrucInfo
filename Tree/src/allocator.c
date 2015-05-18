/*
 * allocator.c
 *
 *  Created on: 04-mars-2009
 *      Author: mattens
 */
/* ------------------------------------------------------------------------- */
#include <stdlib.h>
#include "allocator.h"
/* ------------------------------------------------------------------------- */
typedef int bool;
#define false 0
#define true 1
/* ------------------------------------------------------------------------- */
struct TAllocator {
	size_t _sizeEle;
	size_t _allocCount;
};
/* ------------------------------------------------------------------------- */
struct TAllocator* CreateAllocator(size_t sizeEle) {
	struct TAllocator* pAllocator = malloc(sizeof(struct TAllocator));
	if (!pAllocator) exit(1);
	pAllocator->_sizeEle = sizeEle;
	pAllocator->_allocCount = 0;
	return pAllocator;
}

void DestroyAllocator(struct TAllocator* pAllocator) {
	free(pAllocator);
}

int GetNumberAllocated(const struct TAllocator* pAllocator) {
	return pAllocator->_allocCount;
}

void* Allocate(struct TAllocator* pAllocator) {
	void* ptr = malloc(pAllocator->_sizeEle);
	if (!ptr) exit(1);
	++pAllocator->_allocCount;
	return ptr;
}

void Deallocate(struct TAllocator* pAllocator,void* ptr) {
	free(ptr);
	--pAllocator->_allocCount;
}
/* ------------------------------------------------------------------------- */

