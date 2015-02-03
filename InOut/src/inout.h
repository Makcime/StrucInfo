/*
 * inout.h
 *
 *  Created on: 2 févr. 2010
 *      Author: jm
 */

#ifndef INOUT_H_
#define INOUT_H_

long ReadLongLimited(const char*, long, long);
long ReadLong(const char*);
int ReadIntLimited(const char*, int, int);
int ReadInt(const char*);
double ReadDoubleLimited(const char*, double, double);
double ReadDouble(const char*);
int Stop(void);

#endif /* INOUT_H_ */
