#pragma once
#include "Comparator.h"
#include "County.h"

template<typename T>
class CountyComparator : public Comparator<T> {
protected:
	unsigned int aYear_;
	unsigned int bYear_;
	bool ascending_;
public:

	virtual bool compare(T item1, T item2) = 0;
};