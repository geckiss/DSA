#include "County.h"



County::County()
{
}

County::County(wstring name)
{
	if (name.length() != 0) {
		name_ = name;
		townsInCounty_ = new UnsortedSequenceTable<wstring, Town*>();

		///////
		totalValues_ = new double[YEARS] {};
		divs_ = new double[YEARS] {};
		sub_ = 0;
		fruitDivValues_ = new double[YEARS] {};
		farmDivValues_ = new double[YEARS] {};
		forestDivValues_ = new double[YEARS] {};
	}
}


County::~County()
{
	delete[] totalValues_;
	delete[] divs_;
	delete[] fruitDivValues_;
	delete[] farmDivValues_;
	delete[] forestDivValues_;

	townsInCounty_->clear();
	delete townsInCounty_;
	townsInCounty_ = nullptr;
	name_ = L"";
	sub_ = 0;
}

void County::addTown(Town * t)
{
	if (t != nullptr) {
		townsInCounty_->insertWithoutCheck(t->getName(), t);
	}
}

void County::addTotalValues(Town * t)
{
	for (int i = 0; i < YEARS; i++) {
		totalValues_[i] += t->getLand(i + MIN_YEAR)->getCelkovaVymera();
	}
}

void County::setDiv(unsigned int year, double value)
{
	divs_[year - MIN_YEAR] = value;
}

void County::addFruitDivValues(Town * t)
{
	for (int i = 0; i < YEARS; i++) {
		fruitDivValues_[i] += t->getLand(i + MIN_YEAR)->getPpOvoc();
	}
}

void County::addFarmDivValues(Town * t)
{
	for (int i = 0; i < YEARS; i++) {
		farmDivValues_[i] += t->getLand(i + MIN_YEAR)->getPpOrna();
	}
}

void County::addForestDivValues(Town * t)
{
	for (int i = 0; i < YEARS; i++) {
		forestDivValues_[i] += t->getLand(i + MIN_YEAR)->getNppLes();
	}
}

double County::getTotalValue(unsigned int year)
{
	return totalValues_[year - MIN_YEAR];
}

double County::getDiv(unsigned int year)
{
	return divs_[year - MIN_YEAR];
}

double County::getFruitDivValue(unsigned int year)
{
	return fruitDivValues_[year - MIN_YEAR];
}

double County::getFarmDivValue(unsigned int year)
{
	return farmDivValues_[year - MIN_YEAR];
}

double County::getForestDivValue(unsigned int year)
{
	return forestDivValues_[year - MIN_YEAR];
}
