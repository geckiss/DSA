#pragma once
#include "Comparator.h"
#include "Town.h"

static const unsigned short INIT_GROWTH = 100;

template<typename T>
class BuildingAreaComparator : public Comparator<T> {
private:
	unsigned int aYear_;
	bool ascending_;
public:
	BuildingAreaComparator();
	BuildingAreaComparator(unsigned int aYear, bool ascending);
	~BuildingAreaComparator();

	bool compare(T item1, T item2) override;
};

template<typename T>
inline BuildingAreaComparator<T>::BuildingAreaComparator() 
{
}

template<typename T>
inline BuildingAreaComparator<T>::BuildingAreaComparator(unsigned int aYear, bool ascending) :
	aYear_(aYear), ascending_(ascending)
{
}

template<typename T>
inline BuildingAreaComparator<T>::~BuildingAreaComparator() 
{
}

template<typename T>
inline bool BuildingAreaComparator<T>::compare(T item1, T item2) 
{
	double totalYearBefore1 = 0;
	double zastavYearBefore1 = 0;
	double totalThisYear1;
	double zastavThisYear1;
	double totalYearBefore2 = 0;
	double zastavYearBefore2 = 0;
	double totalThisYear2;
	double zastavThisYear2;
	double growth1 = 0;
	double growth2 = 0;

	if (item1->getLand(aYear_)->getBuildingChange() == 0) {
		if (aYear_ != MIN_YEAR) {
			totalYearBefore1 = (double)item1->getLand(aYear_ - 1)->getCelkovaVymera();
			zastavYearBefore1 = (double)item1->getLand(aYear_ - 1)->getNppZastav();

			totalThisYear1 = (double)item1->getLand(aYear_)->getCelkovaVymera();
			zastavThisYear1 = (double)item1->getLand(aYear_)->getNppZastav();
			if (totalYearBefore1 != 0) {
				growth1 = (zastavThisYear1 / totalThisYear1) - (zastavYearBefore1 / totalYearBefore1);
			}
			else {
				growth1 = (zastavThisYear1 / totalThisYear1);
			}

			totalYearBefore2 = (double)item2->getLand(aYear_ - 1)->getCelkovaVymera();
			zastavYearBefore2 = (double)item2->getLand(aYear_ - 1)->getNppZastav();

			totalThisYear2 = (double)item2->getLand(aYear_)->getCelkovaVymera();
			zastavThisYear2 = (double)item2->getLand(aYear_)->getNppZastav();
			if (totalYearBefore2 != 0) {
				growth2 = (zastavThisYear2 / totalThisYear2) - (zastavYearBefore2 / totalYearBefore2);
			}
			else {
				growth2 = (zastavThisYear2 / totalThisYear2);
			}
		}
		else {
			growth1 = INIT_GROWTH;
			growth2 = INIT_GROWTH;
		}
		item1->getLand(aYear_)->setBuildChange(growth1);
		//t1->getLand(aYear_)->setBuildChangeYear(aYear_);
		item2->getLand(aYear_)->setBuildChange(growth2);
		//t2->getLand(aYear_)->setBuildChangeYear(aYear_);
	}
	else {
		growth1 = item1->getLand(aYear_)->getBuildingChange();
		growth2 = item2->getLand(aYear_)->getBuildingChange();
	}
	if (ascending_) {
		if (growth1 > growth2) {
			return true;
		}
		return false;
	}
	else {
		if (growth1 < growth2) {
			return true;
		}
		return false;
	}
}
