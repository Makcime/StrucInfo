/*
 * tfortree.h
 *
 *  Created on:
 *  Author: Mattens
 */

#ifndef TFORTREE_H_
#define TFORTREE_H_
/* ------------------------------------------------------------------------- */
/* Types TValueTree and TKeyTree must be defined by the programmer for use with TTree*/
struct TPairPtrSize {
	const void* ptr;
	size_t size;
};
typedef const void* TKeyTree;
typedef struct TPairPtrSize TValueTree;
/* ------------------------------------------------------------------------- */
#endif /* TFORTREE_H_ */
