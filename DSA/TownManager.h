#pragma once
#include "Town.h"
#include "../CaC/structures/table/sorted_sequence_table.h"
#include "../CaC/structures/table/unsorted_sequence_table.h"
#include "../CaC/structures/table/sorting/heap_sort.h"
#include <fstream>	// ifstream
#include <iostream>	// cin, cout
#include <sstream>	// sstream na parse stringu s medzerami do intu
#include <fcntl.h>
#include <io.h>
#include <locale>

using namespace structures;

static const unsigned int SKEYS_SIZE = 6;
static const wstring NUMBERS = L"0123456789 ";
static const char COUNTY_DELIM = ',';

class TownManager
{
private:
	SequenceTable<wstring, Town*>* towns_;
	wstring* sKeys_;
	//SequenceTable<string, Town*>* towns_;
	//string* sKeys_;

public:
	TownManager();
	~TownManager();

	SequenceTable<wstring, Town*>* getTowns() { return towns_; }
	//SequenceTable<string, Town*>* getTowns() { return towns_; }

	void loadTownInfo(const char* filename);

	// Uloha 1
	void searchForTown(wstring name, unsigned int lowYear, unsigned int highYear);

	void orderTowns(unsigned int aYear, unsigned int bYear, bool ascending, unsigned int criterium);
};

