#pragma once
#include "Comparator.h"
#include "Town.h"

template<typename T>
class FarmlandComparator : public Comparator<T> {
private:
	unsigned int aYear_;
	signed int bYear_;
	bool ascending_;
public:
	FarmlandComparator();
	FarmlandComparator(unsigned int aYear, signed int bYear, bool ascending);
	~FarmlandComparator();

	bool compare(T item1, T item2) override;
};

template<typename T>
inline FarmlandComparator<T>::FarmlandComparator()
{
}

template<typename T>
inline FarmlandComparator<T>::FarmlandComparator(unsigned int aYear, signed int bYear, bool ascending) :
	aYear_(aYear), bYear_(bYear), ascending_(ascending)
{
}

template<typename T>
inline FarmlandComparator<T>::~FarmlandComparator()
{
}

template<typename T>
inline bool FarmlandComparator<T>::compare(T item1, T item2) 
{
	double divAYear1;
	double divBYear1;
	double divAYear2;
	double divBYear2;
	double subtract1;
	double subtract2;
	double menovatel;
	// celkova vymera == 0
	if (item1->getAYear() == aYear_ && item1->getBYear() == bYear_) {
		// Ak uz trafim roky, farmlandChange nie je nikdy nulova
		subtract1 = item1->getFarmlandChange();
		subtract2 = item2->getFarmlandChange();
	}
	else {
		menovatel = (double)item1->getLand(aYear_)->getCelkovaVymera();
		if (menovatel != 0) {
			divAYear1 = ((double)item1->getLand(aYear_)->getPpOrna() / menovatel);
		}
		else {
			divAYear1 = 0;
		}

		menovatel = (double)item1->getLand(bYear_)->getCelkovaVymera();
		if (menovatel != 0) {
			divBYear1 = ((double)item1->getLand(bYear_)->getPpOrna() / menovatel);
		}
		else {
			divBYear1 = 0;
		}

		menovatel = (double)item2->getLand(aYear_)->getCelkovaVymera();
		if (menovatel != 0) {
			divAYear2 = ((double)item2->getLand(aYear_)->getPpOrna() / menovatel);
		}
		else {
			divAYear2 = 0;
		}

		menovatel = (double)item2->getLand(bYear_)->getCelkovaVymera();
		if (menovatel != 0) {
			divBYear2 = ((double)item2->getLand(bYear_)->getPpOrna() / menovatel);
		}
		else {
			divBYear2 = 0;
		}

		subtract1 = divBYear1 - divAYear1;
		subtract2 = divBYear2 - divAYear2;

		item1->setFarmlandChange(subtract1);
		item1->setAYear(aYear_);
		item1->setBYear(bYear_);
		item2->setFarmlandChange(subtract2);
		item2->setAYear(aYear_);
		item2->setBYear(bYear_);
	}
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