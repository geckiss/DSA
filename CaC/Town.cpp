#include "Town.h"



Town::Town(wstring name) :
	farmlandChange_(0), aYear_(0), bYear_(0)
{
	if (name.length() != 0) {
		name_ = name;
		years_ = new TownLand*[YEARS];
		for (int i = 0; i < YEARS; i++) {
			years_[i] = new TownLand();
		}
	}
	else {
		wcout << L"Nemozno vytvorit obec; ziadny nazov" << endl;
	}
}


Town::~Town()
{
	name_ = L"";
	//name_ = "";
	for (int i = 0; i < YEARS; i++) {
		delete years_[i];
	}
	delete years_;
	years_ = nullptr;
	farmlandChange_ = 0;
	aYear_ = 0;
	bYear_ = 0;
}

TownLand * Town::getLand(int year)
{
	return years_[year - MIN_YEAR];
}

void Town::addLand(int year, TownLand* tl)
{
	if (year >= MIN_YEAR && year <= MAX_YEAR) {
		years_[MIN_YEAR - year] = tl;
	}
	else {
		cout << "Nemozno pridat informacie o pozemkoch; nespravny rok: " << year << endl;
	}

}

void Town::printTownInfo(unsigned int lowYear, unsigned int highYear)
{
	TownLand* land;
	unsigned int total;
	double div;
	wcout << endl << "------------------------------------------------------------------------------------------" << endl << "Obec " << name_ << ":" << endl;
	for (int i = 0; i < (highYear - lowYear + 1); i++) {
		land = getLand(lowYear + i);
		total = land->getCelkovaVymera();
		cout << lowYear + i << ":" << endl;
		cout << "*	Celkova vymera obce: " << total << endl;
		cout << "*	Vymera ornej pody: " << land->getPpOrna() << " m2" << endl;
		cout << "*	Vymera ovocnych sadov: " << land->getPpOvoc() << " m2" << endl;
		cout << "*	Podiel vymery vodnych ploch voci celkovej vymere obce: ";
		div = ((double)land->getNppVoda() / total) * 100;
		cout << div << " %" << endl;
		cout << "*	Podiel vymery lesnych pozemkov voci celkovej vymere obce: ";
		div = ((double)land->getNppLes() / total) * 100;
		cout << div << " %" << endl;
		cout << "*	Podiel vymery zastavanych ploch a nadvori voci celkovej vymere obce: ";
		div = ((double)land->getNppZastav() / total) * 100;
		cout << div << " %" << endl << endl;
	}
	cout << endl << "------------------------------------------------------------------------------------------" << endl;
}