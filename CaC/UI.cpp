#include "UI.h"
#include "../CaC/structures/heap_monitor.h"

UI::UI()
{
}

UI::UI(TownManager* tm, CountyManager* cm)
{
	if (tm != nullptr && cm != nullptr) {
		tm_ = tm;
		cm_ = cm;
		finish = false;
	}
}

UI::~UI()
{
	tm_ = nullptr;
	cm_ = nullptr;
	iOrderType = 0;
	i = 0;
}

void UI::hi()
{
	cout << endl;
	cout << "		**************************************************" << endl;
	cout << "				Vitajte v aplik�cii" << endl;
	cout << "		**************************************************" << endl << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	cout << "		�daje o ploche s� prezentovan� v m2." << endl;
	cout << "		�daje o podieloch(a pr�rastkoch resp.�bytkoch) s� prezentovan� v percent�ch." << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl << endl;
}

void UI::mainScreen()
{
	tm_->loadTownInfo("Vymera_dia_noutf.csv");
	
	cm_->loadCounties("Uzemie_ba_dia_noutf.csv");
	cm_->loadCounties("Uzemie_nr_dia_noutf.csv");
	cm_->loadCounties("Uzemie_tt_dia_noutf.csv");
	cm_->loadCounties("Uzemie_tn_dia_noutf.csv");
	cm_->loadCounties("Uzemie_za_dia_noutf.csv");
	cm_->loadCounties("Uzemie_bb_dia_noutf.csv");
	cm_->loadCounties("Uzemie_po_dia_noutf.csv");
	cm_->loadCounties("Uzemie_ke_dia_noutf.csv");

	hi();
	do {
		setI(0);
		pomVstup = L"";
		cout << endl;
		cout << "	1. Vyh�adanie obce pod�a n�zvu" << endl;
		cout << "	2. Zoradenie obc�" << endl;
		cout << "	3. Vyh�adanie okresu pod�a krit�ria" << endl;
		cout << "	4. Zoradenie okresov" << endl;
		cout << "	5. Koniec" << endl;
		cout << endl;
		do {
			cout << "Zvo�te funkcionalitu(��slo od 1 do 5 vr�tane): ";
			try {
				getline(wcin, pomVstup);
				i = stoi(pomVstup);
			}
			catch (exception e) {
				e.what();
			}
		} while (i < 1 || i > 5);
		switch (i) {
		case 1:
			searchForTown();
			break;
		case 2:
			orderTowns();
			break;
		case 3:
			searchForCounty();
			break;
		case 4:
			orderCounties();
			break;
		case 5:
			finish = true;
			bye();
			break;
		}
	} while (!finish);
}

void UI::searchForTown()
{
	setI(0);
	wstring name = L"";
	pomVstup = L"";
	unsigned int a = 0;
	unsigned int b = 0;
	cout << endl << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	try {
		while (name == L"") {
			cout << endl << "Zadajte n�zov obce: ";
			getline(wcin, name);
		}

		cout << endl << "Zadajte rozp�tie rokov, z ktor�ch chcete vyp�sa� �daje o obci. " << endl;
		cout << "Tvar: <men��Rok, v���Rok> " << endl;
		cout << "Maxim�lne povolen� rozp�tie je <1996, 2017>" << endl;
		while (a < MIN_YEAR || a > MAX_YEAR) {
			cout << endl << "Zadajte men�� rok: ";
			getline(wcin, pomVstup);
			if (pomVstup != L"") {
				try {
					a = stoul(pomVstup);
				}
				catch (exception e) {
					e.what();
				}
			}
		}

		pomVstup = L"";

		while (b < MIN_YEAR || b > MAX_YEAR || a > b) {
			cout << endl << "Zadajte v��� rok(v��i alebo rovn� ako " << a << "): ";
			getline(wcin, pomVstup);
			if (pomVstup != L"") {
				try {
					b = stoul(pomVstup);
				}
				catch (exception e) {
					e.what();
				}
			}
		}
		tm_->searchForTown(name, a, b);
	}
	catch (exception e) {
		e.what();
	}
}

void UI::orderTowns()
{
	setI(0);
	unsigned int year1;
	unsigned int year2 = 2020;
	bool ascending = false;
	int a = -1;
	pomVstup = L"";
	cout << endl << endl << "--------------------------------------------------------------------------------------------" << endl;
	cout << "Zoradenie obc� na z�klade:" << endl;
	cout << "	1. Celkovej v�mery obce v danom roku" << endl;
	cout << "	2. Pr�rastku zastavan�ch pl�ch vo�i celkovej v�mere obce v danom roku" << endl;
	cout << "	3. Zmeny podielu v�mery ornej p�dy vo�i celkovej v�mere obce medzi dvomi rokmi" << endl;
	cout << "	4. Nasp�" << endl;
	cout << endl;

	while (pomVstup == L"" || i < 1 || i > 4) {
		cout << "Zvo�te krit�rium zoradenia(v tvare 1): ";
		getline(wcin, pomVstup);
		try {
			i = stoi(pomVstup);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
	if (i != 4) {
		if (i == 1 || i == 2) {
			while (pomVstup == L"" || pomVstup.length() != YEAR_LENGTH || year1 < MIN_YEAR || year1 > MAX_YEAR) {
				cout << "Zadajte rok: " << endl;
				getline(wcin, pomVstup);
				try {
					year1 = stoi(pomVstup);
				}
				catch (exception e) {
					cout << e.what() << endl;
				}
			}
		}
		else {
			if (i == 3) {
				while (pomVstup == L"" || pomVstup.length() != YEAR_LENGTH || year1 < MIN_YEAR || year1 > MAX_YEAR) {
					cout << "Zadajte prv� rok: " << endl;
					getline(wcin, pomVstup);
					try {
						year1 = stoi(pomVstup);
					}
					catch (exception e) {
						cout << e.what() << endl;
					}
				}

				while (pomVstup == L"" || pomVstup.length() != YEAR_LENGTH || year2 < MIN_YEAR || year2 > MAX_YEAR) {
					cout << "Zadajte druh� rok: " << endl;
					getline(wcin, pomVstup);
					try {
						year2 = stoi(pomVstup);
					}
					catch (exception e) {
						cout << e.what() << endl;
					}
				}
			}
		}

		cout << "Zvo�te sp�sob zoradenia(v tvare 1): " << endl;
		while (pomVstup == L"" || a < 1 || a > 2) {
			cout << "1. Vzostupne: " << endl;
			cout << "2. Zostupne: " << endl;
			getline(wcin, pomVstup);
			try {
				a = stoi(pomVstup);
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}

		if (a == 1) {
			ascending = true;
		}

		if (year1 > year2) {
			int pomYear = year1;
			year1 = year2;
			year2 = pomYear;
		}

		cout << endl;
		tm_->orderTowns(year1, year2, ascending, i);
	}
}

void UI::searchForCounty()
{
	setI(0);
	unsigned int year;
	int a = -1;
	pomVstup = L"";
	cout << endl << endl << "--------------------------------------------------------------------------------------------" << endl;
	cout << "Vyh�adanie okresu, ktor� mal:" << endl;
	cout << "	1. Najv��iu a najmen�iu celkov� v�meru ovocn�ch sadov(v danom roku)" << endl;
	cout << "	2. Najv��� a najmen�� podiel celkovej v�mery ornej p�dy okresu vo�i celkovej v�mere ovocn�ch sadov okresu(v danom roku)" << endl;
	cout << "	3. Najv��� a najmen�� podiel v�mery lesov vo�i celkovej v�mere okresu(v danom roku)" << endl;
	cout << "	4. Nasp�" << endl;
	cout << endl;

	while (pomVstup == L"" || i < 1 || i > 4) {
		cout << "Zvo�te krit�rium zoradenia(v tvare 1): ";
		getline(wcin, pomVstup);
		try {
			i = stoi(pomVstup);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}

	if (i == 1 || i == 2 || i == 3) {
		while (pomVstup == L"" || pomVstup.length() != YEAR_LENGTH || year < MIN_YEAR || year > MAX_YEAR) {
			cout << "Zadajte rok: " << endl;
			getline(wcin, pomVstup);
			try {
				year = stoi(pomVstup);
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}

		cout << endl;
		cm_->findBestWorstCounty(year, i);
		cout << endl;
	}
}

void UI::orderCounties()
{
	setI(0);
	unsigned int aYear = 1990;
	unsigned int bYear = 2020;
	bool ascending = false;
	int a = -1;
	pomVstup = L"";
	cout << endl << endl << "--------------------------------------------------------------------------------------------" << endl;
	cout << "Zoradenie v�etk�ch okresov na z�klade:" << endl;
	cout << "	1. Zmeny podielu v�mery ovocn�ch sadov vo�i celkovej v�mere (medzi dvomi rokmi)" << endl;
	cout << "	2. Zmeny podielu v�mery ornej p�dy vo�i celkovej v�mere (medzi dvomi rokmi)" << endl;
	cout << "	3. Zmeny podielu v�mery lesov vo�i celkovej v�mere (medzi dvomi rokmi)" << endl;
	cout << "	4. Nasp�" << endl;
	cout << endl;

	while (pomVstup == L"" || i < 1 || i > 4) {
		cout << "Zvo�te krit�rium zoradenia(v tvare 1): ";
		getline(wcin, pomVstup);
		try {
			i = stoi(pomVstup);
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}

	if (i == 1 || i == 2 || i == 3) {
		cout << "Zvo�te sp�sob zoradenia(v tvare 1): " << endl;
		while (pomVstup == L"" || a < 1 || a > 2) {
			cout << "1. Vzostupne: " << endl;
			cout << "2. Zostupne: " << endl;
			getline(wcin, pomVstup);
			try {
				a = stoi(pomVstup);
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}

		if (a == 1) {
			ascending = true;
		}

		while (pomVstup == L"" || pomVstup.length() != YEAR_LENGTH || aYear < MIN_YEAR || aYear > MAX_YEAR) {
			cout << "Zadajte prv� rok: " << endl;
			getline(wcin, pomVstup);
			try {
				aYear = stoi(pomVstup);
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}

		while (pomVstup == L"" || pomVstup.length() != YEAR_LENGTH || bYear < MIN_YEAR || bYear > MAX_YEAR) {
			cout << "Zadajte druh� rok: " << endl;
			getline(wcin, pomVstup);
			try {
				bYear = stoi(pomVstup);
			}
			catch (exception e) {
				cout << e.what() << endl;
			}
		}

		if (aYear > bYear) {
			int pomYear = aYear;
			aYear = bYear;
			bYear = pomYear;
		}

		cm_->sortCounties(aYear, bYear, ascending, i);
	}
}

void UI::bye()
{
	cout << endl;
	cout << "		******************************************************" << endl;
	cout << "		*	Dakujeme za vyuzivanie nasich sluzieb.	     *" << endl;
	cout << "		******************************************************" << endl << endl;
}

