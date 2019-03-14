#pragma once
#include "Town.h"
#include "../CaC/structures/table/sorted_sequence_table.h"
#include "../CaC/structures/table/unsorted_sequence_table.h"
#include <fstream>	// ifstream, ofstream
#include <iostream>	// cin, cout
#include <sstream>	// sstream na parse stringu s medzerami do intu
#include <io.h>
#include <fcntl.h>
#include <locale>

using namespace structures;
class County
{
	wstring name_;
	//string name_;
	SequenceTable<wstring, Town*>* townsInCounty_;
	//UnsortedSequenceTable<string, Town*>* townsInCounty_;

	//Uloha 4
	double* totalValues_;
	/// Do divs_ ukladam je jedno ktore udaje kriterii, vzdy po utriedeni sa vypisu a po novom triedeni prepisu a zase vypisu atd...
	double* divs_;
	/// Rozdiel vypocitany v comparatore, pouzity pri finalnom vypise
	double sub_;

	//Uloha 4a
	double* fruitDivValues_;

	//Uloha 4b
	double* farmDivValues_;

	//Uloha 4c
	double* forestDivValues_;
public:
	County();
	County(wstring name);
	~County();

	wstring getName() { return name_; }
	SequenceTable<wstring, Town*>* getTownsInCounty() { return townsInCounty_; }

	void addTown(Town* t);

	/// Uloha 4
	/// Vytiahne z obce udaje o celkovej vymere a pricita ich k celkovej vymere okresu, pre kazdy rok
	void addTotalValues(Town* t);

	void setDiv(unsigned int year, double value);
	void setSub(double sub) { sub_ = sub; }

	/// Uloha 4a
	/// Vytiahne z obce udaje o ovocnych sadoch a pricita ich k vymere ovocnych sadocv okresu, pre kazdy rok
	void addFruitDivValues(Town* t);

	/// Uloha 4b
	/// Vytiahne z obce udaje o ornej pode a pricita ich k vymere ornej pody okresu, pre kazdy rok
	void addFarmDivValues(Town* t);

	/// Uloha 4c
	/// Vytiahne z obce udaje o lesoch a pricita ich k vymere lesov okresu, pre kazdy rok
	void addForestDivValues(Town* t);

	double getTotalValue(unsigned int year);
	double getDiv(unsigned int year);
	double getSub() { return sub_; }
	double getFruitDivValue(unsigned int year);
	double getFarmDivValue(unsigned int year);
	double getForestDivValue(unsigned int year);
};

