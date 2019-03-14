#pragma once
#include "County.h"
#include "TownManager.h"
#include "FruitCountyComparator.h"
#include "FarmCountyComparator.h"
#include "ForestCountyComparator.h"

using namespace std;
using namespace structures;

static const wstring NEWLINE = L"\n";
static const int BEST_COUNTY = 0;
static const int WORST_COUNTY = 1;
static const int RANK = 2;

/*
Vinica, okres Velky Krtis, nie je vo vymerach
*/

class CountyManager
{
private:
	TownManager * tm_;
	SequenceTable<wstring, County*>* counties_;
	//SequenceTable<string, County*>* counties_;

	// Uloha 3a - pole smernikov na pole smernikov na najlepsiu a najorsiu County

	/// Pre kazdy rok existuje pole o velkosti 2, v ktorom na indexe 0 je smernik na najlepsiu County,
	/// Na indexe 1 na najhorsia County
	County*** fruitCounties_;

	/// Pole v prvom riadku drzi doposial najlepsiu najdenu hodnotu pre i-ty rok
	/// V druhom riadku su najhorie hodnoty
	long** fruitCountyValues_;

	/// Kazda County si sem nascitava udaje o ovocnej pode. Pri zmene County sa porovnaju hodnoty s best/worst z frutiCountyValues,
	/// pripadne sa zmeni best/worst County, a toto pole sa vynuluje.
	long* fruitFileValues_;

	//Uloha 3b
	County*** farmCounties_;
	double** farmCountyValues_;
	double* farmFileValues_;
	double* farmFruitFileValues_;

	//Uloha 3c
	County*** forestCounties_;
	double** forestCountyValues_;
	double* forestFileValues_;
	double* totalForestFileValues_;

public:
	CountyManager();
	CountyManager(TownManager * tm);
	~CountyManager();

	void loadCounties(const char* filename);

	/// Uloha 4
	void sortCounties(unsigned int aYear, unsigned int bYear, unsigned int ascending, unsigned int criterium);

	void addFruitFileValues(Town* town);
	void addFarmFileValues(Town* town);
	void addForestFileValues(Town* town);

	void compareFruitValues(County* county);
	void compareFarmValues(County* county);
	void compareForestValues(County* county);

	void renewFilesValues();

	void findBestWorstCounty(unsigned int year, unsigned int criterium);

};

