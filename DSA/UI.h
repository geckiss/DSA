#pragma once
#include "CountyManager.h"
#include "../CaC/structures/heap_monitor.h"

class UI
{
private:
	TownManager* tm_;
	CountyManager* cm_;

	wstring pomVstup;
	int iOrderType = 0;
	int i = 0;
	/// Na ukoncenie programu
	bool finish;
public:
	UI();
	UI(TownManager* tm, CountyManager* cm);
	~UI();

	void hi();
	void mainScreen();
	void searchForTown();
	void orderTowns();
	void searchForCounty();
	void orderCounties();
	void bye();

	bool getFinished() { return finish; }

	void setI(int newI) { i = newI; }
	void setOrderType(int newType) { iOrderType = newType; }
};

