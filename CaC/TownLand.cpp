#include "TownLand.h"



TownLand::TownLand()
{
	celkovaVymera_ = 0;
	ppOrna_ = 0;
	ppOvoc_ = 0;
	nppLes_ = 0;
	nppVoda_ = 0;
	nppZastav_ = 0;
	buildingChange_ = 0;
}


TownLand::TownLand(m2 celkova, m2 ppOrna, m2 ppOvoc, m2 nppLes, m2 nppVoda, m2 nppZastav) :
	buildingChange_(0)//, buildingChangeYear_(0)
{
	if (celkova >= 0 && ppOrna >= 0 &&
		ppOvoc >= 0 && nppLes >= 0 && nppVoda >= 0 && nppZastav >= 0) 
	{
		celkovaVymera_ = celkova;
		ppOrna_ = ppOrna;
		ppOvoc_ = ppOvoc;
		nppLes_ = nppLes;
		nppVoda_ = nppVoda;
		nppZastav_ = nppZastav;
	}
}

TownLand::~TownLand()
{
	celkovaVymera_ = 0;
	ppOrna_ = 0;
	ppOvoc_ = 0;
	nppLes_ = 0;
	nppVoda_ = 0;
	nppZastav_ = 0;
	buildingChange_ = 0;
	//buildingChangeYear_ = 0;
}
