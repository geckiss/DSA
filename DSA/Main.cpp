#pragma once
#include "UI.h"
#include "../CaC/structures/heap_monitor.h"

int main() {
	try {
		initHeapMonitor();

		_setmode(_fileno(stdin), _O_WTEXT);
		std::locale sk("Slovak");
		std::locale::global(sk);

		TownManager* tm = new TownManager();
		CountyManager* cm = new CountyManager(tm);
		UI* ui = new UI(tm, cm);
		ui->mainScreen();

		delete ui;
		delete cm;
		delete tm;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}