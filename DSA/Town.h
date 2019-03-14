#pragma once
#include "TownLand.h"
#include <string>	// string, stod, stoi, getline, substr, find
#include <iostream>

/*
Sklabin· = Sklabinaa
Luk·Ëovce = Lukaacovce
Breûany = Brezany
Laûany = Lazzany
»ernina = Ccernina
*/
using namespace std;
static const unsigned short YEARS = 22;
static const unsigned int MIN_YEAR = 1996;
static const unsigned int MAX_YEAR = 2017;
static const unsigned int YEAR_LENGTH = 4;

class Town
{
private:
	//string name_;
	wstring name_;
	TownLand** years_;

	// Uloha 2c
	double farmlandChange_;
	unsigned int aYear_;
	unsigned int bYear_;
public:
	//Town(string name);
	Town(wstring name);
	~Town();

	wstring getName() { return name_; }
	//string getName() { return name_; }
	TownLand* getLand(int year);
	TownLand** getYears() { return years_; }

	double getFarmlandChange() { return farmlandChange_; }
	unsigned int getAYear() { return aYear_; }
	unsigned int getBYear() { return bYear_; }

	void setFarmlandChange(double fChange) { farmlandChange_ = fChange; }
	void setAYear(unsigned int aYear) { aYear_ = aYear; }
	void setBYear(unsigned int bYear) { bYear_ = bYear; }

	// year modulo 1996 = index
	void addLand(int year, TownLand* tl);

	void printTownInfo(unsigned int lowYear, unsigned int highYear);
};

