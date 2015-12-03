//-----------------------------------------------------------------------------
// file list.cpp
//-----------------------------------------------------------------------------
#include "list.h"
//-----------------------------------------------------------------------------
namespace StructInfoList {
//-----------------------------------------------------------------------------
// TODO ... (list::TNode::...)
//-----------------------------------------------------------------------------
// TODO ... (list::iterator::...)
list::iterator::iterator(){
    
    }
list::iterator::iterator(const_iterator& _i){
    //pNode = _i.pNode;
    }
//-----------------------------------------------------------------------------
// TODO ... (list::const_iterator::...)
bool list::const_iterator::operator==(const const_iterator& i2) const {
/*	if (nRows != m2.nRows || nColumns != m2.nColumns)
		return false;
	for (int r = 0; r < nRows; ++r)
		for (int c = 0; c < nColumns; ++c)
			if (fabs(pRows[r].pValues[c] - m2.pRows[r].pValues[c]) > EPSILON)
				return false;*/

	return true;
}
//-----------------------------------------------------------------------------
// TODO ... (list::...)
/*istream& operator >>(istream& is, value_type& v) {
	int nr=-1, nc=-1;  // pour Realloc en cas d'activation de failbit
	is >> nr;
	is.get();
	is >> nc;
	m.Realloc(nr, nc);
	for (int i = 0; i < m.GetNbrRows(); ++i)
		for (int j = 0; j < m.GetNbrColumns(); ++j) {
			is.get();
			is >> m[i][j];
		}
	return is;
}*/
//-----------------------------------------------------------------------------
} // namespace StructInfoList
//-----------------------------------------------------------------------------
