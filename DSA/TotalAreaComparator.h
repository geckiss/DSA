#pragma once
#include "Comparator.h"
#include "Town.h"

template<typename T>
class TotalAreaComparator : public Comparator<T> {
private:
	unsigned int aYear_;
	bool ascending_;
public:
	TotalAreaComparator();
	TotalAreaComparator(unsigned int aYear, bool ascending);

	~TotalAreaComparator();
	 
	bool compare(T item1, T item2) override;
};

template<typename T>
inline TotalAreaComparator<T>::TotalAreaComparator()
{
}

template<typename T>
inline TotalAreaComparator<T>::TotalAreaComparator(unsigned int aYear, bool ascending) : aYear_(aYear), ascending_(ascending)
{
}

template<typename T>
inline TotalAreaComparator<T>::~TotalAreaComparator() {
}

template<typename T>
inline bool TotalAreaComparator<T>::compare(T item1, T item2) 
{
	if (ascending_) {
		if (item1->getLand(aYear_)->getCelkovaVymera() > item2->getLand(aYear_)->getCelkovaVymera()) {
			return true;
		}
		return false;
	}
	else {
		if (item1->getLand(aYear_)->getCelkovaVymera() < item2->getLand(aYear_)->getCelkovaVymera()) {
			return true;
		}
		return false;
	}
}
