#include "TownManager.h"



TownManager::TownManager()
{
	towns_ = new SortedSequenceTable<wstring, Town*>();
	//towns_ = new SortedSequenceTable<string, Town*>();
	sKeys_ = new wstring[6];
	//sKeys_ = new string[6];
	
	sKeys_[0] = L"Celková výmera územia obce - mesta (v m2)";
	sKeys_[1] = L"Po¾nohospodárska pôda  - orná pôda (v m2)";
	sKeys_[2] = L"Po¾nohospodárska pôda  -  ovocný sad (v m2)";
	sKeys_[3] = L"Nepo¾nohospodárska pôda - lesný pozemok (v m2)";
	sKeys_[4] = L"Nepo¾nohospodárska pôda - vodná plocha (v m2)";
	sKeys_[5] = L"Nepo¾nohospodárska pôda - zastavaná plocha a nádvorie (v m2)";
	/*
	sKeys_[0] = "Celkova vymera uzemia obce - mesta (v m2)";
	sKeys_[1] = "Polnohospodarska poda  - orna poda (v m2)";
	sKeys_[2] = "Polnohospodarska poda  -  ovocny sad (v m2)";
	sKeys_[3] = "Nepolnohospodarska poda - lesny pozemok (v m2)";
	sKeys_[4] = "Nepolnohospodarska poda - vodna plocha (v m2)";
	sKeys_[5] = "Nepolnohospodarska poda - zastavana plocha a nadvorie (v m2)";
	*/
}


TownManager::~TownManager()
{
	
	for (int i = 0; i < SKEYS_SIZE; i++) {
		sKeys_[i] = L"";
	}
	/*
	for (int i = 0; i < SKEYS_SIZE; i++) {
		sKeys_[i] = "";
	}
	*/
	delete[] sKeys_;
	sKeys_ = nullptr;

	for (auto item : *towns_) {
		delete item->accessData();
	}
	towns_->clear();
	delete towns_;
	towns_ = nullptr;
}

void TownManager::loadTownInfo(const char* filename) 
{		
	if (filename != nullptr) {
		std::wifstream f(filename);
		if (f.is_open()) {
			std::wstring desc;
			std::wstring name;
			int iDesc;
			bool isItTown;
			int townPos;
			unsigned int rok;
			std::wstring cislo;
			std::wstring subcislo;
			std::wstring cast;
			Town* t;
			TownLand* tl;

			// O(n) - n je pocet obci
			while (getline(f, desc, L';')) {
				townPos = 0;
				if (desc.length() != 0) {
					if (name != L"") {
						t = new Town(name);
						towns_->insert(name, t);
						wcout << name << endl;
					}
					isItTown = true;
					for (int i = 0; i < SKEYS_SIZE; i++) {
						if (desc.find(sKeys_[i]) != -1) {
							iDesc = i;
							isItTown = false;
							break;
						}
					}

					if (!isItTown) {
						rok = MIN_YEAR;
						// O(m)
						while (rok != MAX_YEAR + 1) {
							// O(1)
							getline(f, cislo, L';');
							// Ak som na konci info. pre dane mesto, je tam \n
							// Tak musim checknut ci getline nevratil cislo \n
							townPos = cislo.find_first_not_of(NUMBERS);
							// Ak hej, \n prec
							if (townPos != -1) {
								name = cislo.substr(townPos + 1);
								cislo = cislo.substr(0, townPos);
							}
							wstringstream stream(cislo);
							subcislo = L"";
							while (stream >> cast) {
								subcislo += cast;
							}

							switch (iDesc) {
							case 0:
								t->getLand(rok)->setCelkovaVymera(stoul(subcislo));
								break;
							case 1:
								t->getLand(rok)->setPpOrna(stoul(subcislo));
								break;
							case 2:
								t->getLand(rok)->setPpOvoc(stoul(subcislo));
								break;
							case 3:
								t->getLand(rok)->setNppLes(stoul(subcislo));
								break;
							case 4:
								t->getLand(rok)->setNppVoda(stoul(subcislo));
								break;
							case 5:
								t->getLand(rok)->setNppZastav(stoul(subcislo));
								break;
							}
							rok++;
						}
					}
					else {
						//desc = desc.substr(3);
						t = new Town(desc);
						towns_->insert(desc, t);
						wcout << desc << endl;
					}
				}

			}
		}
		if (f.is_open()) f.close();
		cout << "Nacitavanie vymeri obci dokoncene" << endl;
	}
	
}

void TownManager::searchForTown(wstring name, unsigned int lowYear, unsigned int highYear)
{
	Town* searched = towns_->operator[](name);
	if (searched != nullptr) {
		searched->printTownInfo(lowYear, highYear);
	}
	else {
		cout << "Zadana obec nebola najdena v databaze!" << endl;
	}
}

void TownManager::orderTowns(unsigned int aYear, unsigned int bYear, bool ascending, unsigned int criterium)
{
	if (!towns_->isEmpty()) {

		Town* t;
		UnsortedSequenceTable<wstring, Town*>* ust1 = new UnsortedSequenceTable<wstring, Town*>();
		Sort<wstring, Town*>* heap1 = new HeapSort<wstring, Town*>();
		Comparator<Town*>* comp;

		// Nahadzem ich do neutriedenej
		for (auto item : *towns_) {
			t = item->accessData();
			ust1->insertWithoutCheck(t->getName(), t);
		}

		switch (criterium) {
		case 1:
			comp = new TotalAreaComparator<Town*>(aYear, ascending);
			wcout << "Triedim..." << endl;
			heap1->sort(*ust1, comp);

			for (auto item : *ust1) {
				wcout << item->accessData()->getName() << ": " << fixed << item->accessData()->getLand(aYear)->getCelkovaVymera() << " m2" << endl << endl;
			}

			break;

		case 2:
			comp = new BuildingAreaComparator<Town*>(aYear, ascending);
			wcout << "Triedim..." << endl;
			heap1->sort(*ust1, comp);

			for (auto item : *ust1) {
				wcout << item->accessData()->getName() << ": " << fixed << item->accessData()->getLand(aYear)->getBuildingChange() * 100 << " %" << endl << endl;
			}

			break;
		case 3:
			comp = new FarmlandComparator<Town*>(aYear, bYear, ascending);
			wcout << "Triedim..." << endl;
			heap1->sort(*ust1, comp);

			for (auto item : *ust1) {
				wcout << item->accessData()->getName() << ": " << fixed << item->accessData()->getFarmlandChange() * 100 << " %" << endl << endl;
			}

			break;
		}
		delete comp;
		delete heap1;
		ust1->clear();
		delete ust1;
	}
	else {
		cout << "Nemožno triedi - žiadna obec!" << endl;
	}
}
