#include "CountyManager.h"



CountyManager::CountyManager()
{
	counties_ = new UnsortedSequenceTable<wstring, County*>();
}

CountyManager::CountyManager(TownManager * tm)
{
	if (tm != nullptr) {
		tm_ = tm;
		counties_ = new UnsortedSequenceTable<wstring, County*>();

		///////////////////
		fruitCounties_ = new County**[YEARS];
		for (int i = 0; i < YEARS; i++) {
			fruitCounties_[i] = new County*[RANK];
			fruitCounties_[i][BEST_COUNTY] = nullptr;
			fruitCounties_[i][WORST_COUNTY] = nullptr;
		}
		fruitCountyValues_ = new long*[YEARS];
		for (int i = 0; i < YEARS; i++) {
			fruitCountyValues_[i] = new long[RANK];
			fruitCountyValues_[i][BEST_COUNTY] = INT_MIN;
			fruitCountyValues_[i][WORST_COUNTY] = INT_MAX;
		}
		fruitFileValues_ = new long[YEARS] {};

		///////////////////
		farmCounties_ = new County**[YEARS];
		for (int i = 0; i < YEARS; i++) {
			farmCounties_[i] = new County*[RANK];
			farmCounties_[i][BEST_COUNTY] = nullptr;
			farmCounties_[i][WORST_COUNTY] = nullptr;
		}
		farmCountyValues_ = new double*[YEARS];
		for (int i = 0; i < YEARS; i++) {
			farmCountyValues_[i] = new double[RANK];
			farmCountyValues_[i][BEST_COUNTY] = INT_MIN;
			farmCountyValues_[i][WORST_COUNTY] = INT_MAX;
		}
		farmFileValues_ = new double[YEARS] {};
		farmFruitFileValues_ = new double[YEARS] {};

		///////////////////
		forestCounties_ = new County**[YEARS];
		for (int i = 0; i < YEARS; i++) {
			forestCounties_[i] = new County*[RANK];
			forestCounties_[i][BEST_COUNTY] = nullptr;
			forestCounties_[i][WORST_COUNTY] = nullptr;
		}
		forestCountyValues_ = new double*[YEARS];
		for (int i = 0; i < YEARS; i++) {
			forestCountyValues_[i] = new double[RANK];
			forestCountyValues_[i][BEST_COUNTY] = INT_MIN;
			forestCountyValues_[i][WORST_COUNTY] = INT_MAX;
		}
		forestFileValues_ = new double[YEARS] {};
		totalForestFileValues_ = new double[YEARS] {};
	}
}


CountyManager::~CountyManager()
{
	tm_ = nullptr;
	for (auto county : *counties_) {
		delete (county->accessData());
	}
	counties_->clear();
	delete counties_;
	counties_ = nullptr;

	///////////////////
	for (int i = 0; i < YEARS; i++) {
		delete[] fruitCounties_[i];
	}
	delete[] fruitCounties_;
	fruitCounties_ = nullptr;
	for (int i = 0; i < YEARS; i++) {
		delete[] fruitCountyValues_[i];
	}
	delete[] fruitCountyValues_;
	fruitCountyValues_ = nullptr;
	delete[] fruitFileValues_;
	fruitFileValues_ = nullptr;

	///////////////////
	for (int i = 0; i < YEARS; i++) {
		delete[] farmCounties_[i];
	}
	delete[] farmCounties_;
	farmCounties_ = nullptr;
	for (int i = 0; i < YEARS; i++) {
		delete[] farmCountyValues_[i];
	}
	delete[] farmCountyValues_;
	farmCountyValues_ = nullptr;
	delete[] farmFileValues_;
	farmFileValues_ = nullptr;
	delete[] farmFruitFileValues_;
	farmFruitFileValues_ = nullptr;
	///////////////////
	for (int i = 0; i < YEARS; i++) {
		delete[] forestCounties_[i];
	}
	delete[] forestCounties_;
	forestCounties_ = nullptr;
	for (int i = 0; i < YEARS; i++) {
		delete[] forestCountyValues_[i];
	}
	delete[] forestCountyValues_;
	forestCountyValues_ = nullptr;
	delete[] forestFileValues_;
	forestFileValues_ = nullptr;
	delete[] totalForestFileValues_;
	totalForestFileValues_ = nullptr;
}

void CountyManager::loadCounties(const char * filename)
{
	if (filename != nullptr) {
		wifstream f(filename);
		if (f.is_open()) {
			wstring countyName = L"";
			wstring loadedCountyName;
			wstring townName;
			wstring nextTownName;
			County* c;
			int townPos;
			// Prva obec v subore po bodkociarku
			getline(f, townName, L';');
			townName = townName.substr(2);
			// Smernik na Town najdem v towns_ v townManagerovi
			Town* t;
			while (getline(f, loadedCountyName, L';')) {
				townPos = loadedCountyName.find_first_of(NEWLINE);
				// Na konci suboru bude == -1
				if (townPos != -1) {
					nextTownName = loadedCountyName.substr(townPos);
					if (nextTownName == L"\n") {
						break;
					}
					nextTownName = nextTownName.substr(3);
					loadedCountyName = loadedCountyName.substr(0, townPos);
				}

				// Iny okres
				if (countyName != loadedCountyName) {
					if (countyName != L"") {
						// Porovnam hodnoty najlepsieho/horsieho okresu pre Ulohu 3
						compareFruitValues(c);
						compareFarmValues(c);
						compareForestValues(c);

						renewFilesValues();
					}

					c = new County(loadedCountyName);
					// Pridam novy okres
					counties_->insertWithoutCheck(loadedCountyName, c);
					countyName = loadedCountyName;
				}
				// Ziskam smernik na uz existujuce mesto a ten pridam do zoznamu miest v okrese
				if (tm_->getTowns()->tryFind(townName, t)) {

				}
				else {
					townName = (townName.append(L", okres ")).append(loadedCountyName);
					if (tm_->getTowns()->tryFind(townName, t)) {

					}
					else {
						throw std::exception("Town not found in towns' database; cannot add to county");
					}
				}

				addFruitFileValues(t);
				addFarmFileValues(t);
				addForestFileValues(t);

				c->addTown(t);
				c->addTotalValues(t);
				c->addFruitDivValues(t);
				c->addFarmDivValues(t);
				c->addForestDivValues(t);

				wcout << "Obec " << townName << " pridana do okresu " << countyName << endl;
				townName = nextTownName;
			}
			f.close();
		}
		cout << "Nacitavanie okresov a ich obci zo suboru " << filename << " dokoncene." << endl << endl;
	}
}

void CountyManager::sortCounties(unsigned int aYear, unsigned int bYear, unsigned int ascending, unsigned int criterium)
{
	if (!counties_->isEmpty()) {
		UnsortedSequenceTable<wstring, County*>* ust = new UnsortedSequenceTable<wstring, County*>();
		Sort<wstring, County*>* heap = new HeapSort<wstring, County*>();
		Comparator<County*>* comp;

		// Nahadzem ich do neutriedenej
		for (auto county : *counties_) {
			ust->insertWithoutCheck(county->accessData()->getName(), county->accessData());
		}

		switch (criterium) {
		case 1:
			comp = new FruitCountyComparator<County*>(aYear, bYear, ascending);
			wcout << "Triedim..." << endl;
			heap->sort(*ust, comp);
			break;

		case 2:
			comp = new ForestCountyComparator<County*>(aYear, bYear, ascending);
			wcout << "Triedim..." << endl;
			heap->sort(*ust, comp);
			break;

		case 3:
			comp = new ForestCountyComparator<County*>(aYear, bYear, ascending);
			wcout << "Triedim..." << endl;
			heap->sort(*ust, comp);
			break;
		}

		for (auto item : *ust) {
			wcout << item->accessData()->getName() << ": " << item->accessData()->getSub() * 100 << " %" << endl;
		}
		cout << endl;

		delete comp;
		delete heap;
		ust->clear();
		delete ust;
	}
}

void CountyManager::addFruitFileValues(Town* t)
{
	TownLand* tl;
	for (int i = 0; i < YEARS; i++) {
		tl = t->getLand(i + MIN_YEAR);
		if (tl != nullptr) {
			fruitFileValues_[i] += tl->getPpOvoc();
		}
	}
}

void CountyManager::addFarmFileValues(Town* t)
{
	TownLand* tl;
	for (int i = 0; i < YEARS; i++) {
		tl = t->getLand(i + MIN_YEAR);
		if (tl != nullptr) {
			farmFileValues_[i] += (double)tl->getPpOrna();
			farmFruitFileValues_[i] += (double)tl->getPpOvoc();
		}
	}
}

void CountyManager::addForestFileValues(Town* t)
{
	TownLand* tl;
	for (int i = 0; i < YEARS; i++) {
		tl = t->getLand(i + MIN_YEAR);
		if (tl != nullptr) {
			forestFileValues_[i] += (double)tl->getNppLes();
			totalForestFileValues_[i] += (double)tl->getCelkovaVymera();
		}
	}
}

void CountyManager::compareFruitValues(County * county)
{
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < YEARS; j++) {
			// Nasiel som lepsi okres
			if (fruitCountyValues_[j][i] < fruitFileValues_[j]) {
				fruitCountyValues_[j][i] = fruitFileValues_[j];
				// j = rok, 0 = best, 1 = worst
				fruitCounties_[j][BEST_COUNTY] = county;
			}

			// Nasiel som horsi okres
			if (fruitCountyValues_[j][i + 1] > fruitFileValues_[j]) {
				fruitCountyValues_[j][i + 1] = fruitFileValues_[j];
				// j = rok, 0 = best, 1 = worst
				fruitCounties_[j][WORST_COUNTY] = county;
			}
		}
	}
}

void CountyManager::compareFarmValues(County * county)
{
	double menovatel;
	double div;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < YEARS; j++) {
			menovatel = farmFruitFileValues_[j];
			if (menovatel == 0) {
				// TODO keby nejde check toto
				div = 1;
			}
			else {
				div = farmFileValues_[j] / menovatel;
			}
			// Nasiel som lepsi okres
			if (farmCountyValues_[j][i] < div) {
				farmCountyValues_[j][i] = div;
				// j = rok, 0 = best, 1 = worst
				farmCounties_[j][BEST_COUNTY] = county;
			}

			// Nasiel som horsi okres
			if (farmCountyValues_[j][i + 1] > div) {
				farmCountyValues_[j][i + 1] = div;
				// j = rok, 0 = best, 1 = worst
				farmCounties_[j][WORST_COUNTY] = county;
			}
		}
	}
}

void CountyManager::compareForestValues(County * county)
{
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < YEARS; j++) {
			// Nasiel som lepsi okres
			if (forestCountyValues_[j][i] < forestFileValues_[j] / totalForestFileValues_[j]) {
				forestCountyValues_[j][i] = forestFileValues_[j] / totalForestFileValues_[j];
				// j = rok, 0 = best, 1 = worst
				forestCounties_[j][BEST_COUNTY] = county;
			}

			// Nasiel som horsi okres
			if (forestCountyValues_[j][i + 1] > forestFileValues_[j] / totalForestFileValues_[j]) {
				forestCountyValues_[j][i + 1] = forestFileValues_[j] / totalForestFileValues_[j];
				// j = rok, 0 = best, 1 = worst
				forestCounties_[j][WORST_COUNTY] = county;
			}
		}
	}
}

void CountyManager::renewFilesValues()
{
	for (int i = 0; i < YEARS; i++) {
		fruitFileValues_[i] = 0;
		farmFileValues_[i] = 0;
		farmFruitFileValues_[i] = 0;
		forestFileValues_[i] = 0;
		totalForestFileValues_[i] = 0;
	}
}

void CountyManager::findBestWorstCounty(unsigned int year, unsigned int criterium)
{
	County* best;
	County* worst;
	switch (criterium) {
	case 1:
		best = fruitCounties_[year - MIN_YEAR][BEST_COUNTY];
		worst = fruitCounties_[year - MIN_YEAR][WORST_COUNTY];
		wcout << L"Okres s najväèšou výmerou ovocných sadov: " << endl;
		wcout << best->getName() << ": " << fixed << fruitCountyValues_[year - MIN_YEAR][BEST_COUNTY] << " m2" << endl;
		wcout << L"Okres s najmenšou výmerou ovocných sadov: " << endl;
		wcout << worst->getName() << ": " << fixed << fruitCountyValues_[year - MIN_YEAR][WORST_COUNTY] << " m2" << endl;
		break;
	case 2:
		best = farmCounties_[year - MIN_YEAR][BEST_COUNTY];
		worst = farmCounties_[year - MIN_YEAR][WORST_COUNTY];
		wcout << L"Okres s najväèším podielom ornej pôdy voèi celkovej výmere: " << endl;
		wcout << best->getName() << ": " << fixed << farmCountyValues_[year - MIN_YEAR][BEST_COUNTY] * 100 << " %" << endl;
		wcout << L"Okres s najmenším podielom ornej pôdy voèi celkovej výmere: " << endl;
		wcout << worst->getName() << ": " << fixed << farmCountyValues_[year - MIN_YEAR][WORST_COUNTY] * 100 << " %" << endl;
		break;
	case 3:
		best = forestCounties_[year - MIN_YEAR][BEST_COUNTY];
		worst = forestCounties_[year - MIN_YEAR][WORST_COUNTY];
		wcout << L"Okres s najväèším podielom lesov voèi celkovej výmere: " << endl;
		wcout << best->getName() << ": " << fixed << forestCountyValues_[year - MIN_YEAR][BEST_COUNTY] * 100 << " %" << endl;
		wcout << L"Okres s najmenším podielom lesov voèi celkovej výmere: " << endl;
		wcout << worst->getName() << ": " << fixed << forestCountyValues_[year - MIN_YEAR][WORST_COUNTY] * 100 << " %" << endl;
		break;
	}
}
