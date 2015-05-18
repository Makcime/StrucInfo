/*
 * allocator.h
 *
 *  Created on: 04-mars-2009
 *      Author: mattens
 */
/* ------------------------------------------------------------------------- */
#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
/* ------------------------------------------------------------------------- */
struct TAllocator;
/* ------------------------------------------------------------------------- */
struct TAllocator* CreateAllocator(size_t eleSize);
void DestroyAllocator(struct TAllocator* pAllocator);
int GetNumberAllocated(const struct TAllocator* pAllocator);
void* Allocate(struct TAllocator* pAllocator);
void Deallocate(struct TAllocator* pAllocator, void* ptr);
/* ------------------------------------------------------------------------- */
#endif /* ALLOCATOR_H_ */
