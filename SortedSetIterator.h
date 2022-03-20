#pragma once
#include "SortedSet.h"
#include <algorithm>

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	SortedSet& s;
	SortedSetIterator(SortedSet &m);

    int position;
	int* values;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    ~SortedSetIterator();
};

