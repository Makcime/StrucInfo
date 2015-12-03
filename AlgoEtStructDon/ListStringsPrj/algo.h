//-----------------------------------------------------------------------------
// File algo.h
//-----------------------------------------------------------------------------
#ifndef ALGO_H_
#define ALGO_H_
//-----------------------------------------------------------------------------
#include "list.h"
//-----------------------------------------------------------------------------
using namespace StructInfoList;
//-----------------------------------------------------------------------------
namespace StructInfoAlgo {
//-----------------------------------------------------------------------------
typedef int (*Compare)(const string&, const string&);
//---------------------------------------------------------------------------
class Predicate {
public:
//	Predicate() {};
	virtual bool operator()(const string& name) const = 0;
};
//-----------------------------------------------------------------------------
// TODO ... (find, find_if, reverse, bubbelSort) 
list::iterator find(list::const_iterator i1, list::const_iterator i2, list::value_type e1);
//list::iterator find(list::iterator& i1, list::const_iterator i2, list::value_type& e1);
void reverse(list::iterator& i1, list::iterator& i2);
void bubbelSort(list::iterator& i1, list::iterator& i2, Compare);
list::iterator find_if(list::iterator& i1, list::const_iterator i2, bool);
//-----------------------------------------------------------------------------
} // namespace StructInfoAlgo
//-----------------------------------------------------------------------------
#endif /*ALGO_H_*/
//-----------------------------------------------------------------------------
