#pragma once
#include "CountyComparator.h"

template<typename T>
class ForestCountyComparator : public CountyComparator<T> {

public:
	ForestCountyComparator();
	ForestCountyComparator(unsigned int aYear, unsigned int bYear, bool ascending);

	~ForestCountyComparator();

	bool compare(T item1, T item2) override;
};

template<typename T>
inline ForestCountyComparator<T>::ForestCountyComparator()
{
}

template<typename T>
inline ForestCountyComparator<T>::ForestCountyComparator(unsigned int aYear, unsigned int bYear, bool ascending)
{
	aYear_ = aYear;
	bYear_ = bYear;
	ascending_ = ascending;
}

template<typename T>
inline ForestCountyComparator<T>::~ForestCountyComparator() {
}

template<typename T>
inline bool ForestCountyComparator<T>::compare(T item1, T item2)
{
	double divAYear1 = item1->getForestDivValue(aYear_) / item1->getTotalValue(aYear_);
	double divBYear1 = item1->getForestDivValue(bYear_) / item1->getTotalValue(bYear_);
	double divAYear2 = item2->getForestDivValue(aYear_) / item2->getTotalValue(aYear_);
	double divBYear2 = item2->getForestDivValue(bYear_) / item2->getTotalValue(bYear_);
	double subtract1 = divBYear1 - divAYear1;
	double subtract2 = divBYear2 - divAYear2;

	item1->setDiv(aYear_, divAYear1);
	item1->setDiv(bYear_, divBYear1);
	item1->setSub(subtract1);
	item2->setDiv(aYear_, divAYear2);
	item2->setDiv(bYear_, divBYear2);
	item2->setSub(subtract2);

	if (ascending_) {
		if (subtract1 > subtract2) {
			return true;
		}
		return false;
	}
	else {
		if (subtract1 < subtract2) {
			return true;
		}
		return false;
	}
}