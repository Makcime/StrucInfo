//-----------------------------------------------------------------------------
// File list.h
//-----------------------------------------------------------------------------
#ifndef LIST_H_
#define LIST_H_
//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------
// Pour list, il faut dans TData : copy constructor, operator =, destructor
// Pour bubbleSort, il faut dans TData : <
// Pour find, il faut dans TData : ==
//-----------------------------------------------------------------------------
using std::string;
//-----------------------------------------------------------------------------
namespace StructInfoList {
//-----------------------------------------------------------------------------
class list {
public:
    typedef string value_type;
protected:
	//-------------------------------------------------------------------------
	struct TNode {
	// TODO ...	
    TNode * pPrevious;
	TNode * pNext;
	value_type value;
	};
	//-------------------------------------------------------------------------
public:
	//-------------------------------------------------------------------------
	class const_iterator;
	class iterator {
	public:
	  // TODO ...
      iterator();
      iterator(const_iterator& _i);
      bool operator==(const iterator& i2) const;
      bool operator!=(const iterator& i2) const;
      value_type operator* () const;
      iterator& operator++ ();    // prefix ++ 
      iterator  operator++ (int); // postfix ++ 
	protected:
		// TODO ...
        TNode* pNode;
	};

	class const_iterator {
	public:
		// TODO ...
        const_iterator();
        const_iterator(iterator& _i);
        bool operator==(const const_iterator& i2) const;
        bool operator!=(const const_iterator& i2) const;
        value_type operator* () const;
        const_iterator& operator++ ();    // prefix ++ 
        const_iterator  operator++ (int); // postfix ++ 
	protected:
		// TODO ...
        TNode* pNode;
	};

	// TODO ... (typedefs)
    
	//-------------------------------------------------------------------------
	// TODO ...
    const_iterator& begin() const;
    const_iterator& end() const;
    iterator& begin();
    iterator& end();
    void insert(iterator i, value_type v);
    void insert(iterator i1, iterator i2, iterator i3);
    int size();
    iterator erase(iterator i1);
    iterator erase(iterator i1, iterator i2);
protected:
	//-------------------------------------------------------------------------
	// TODO ...
	//-------------------------------------------------------------------------
};

//-----------------------------------------------------------------------------
} // namespace StructInfoList
//-----------------------------------------------------------------------------
#endif /*LIST_H_*/
