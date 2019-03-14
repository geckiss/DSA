#pragma once

typedef unsigned int m2;

class TownLand
{
private:
	m2 celkovaVymera_;
	// pp = Polnohospodarska poda
	m2 ppOrna_;
	m2 ppOvoc_;
	// npp = Nepolnohospodarska poda
	m2 nppLes_;
	m2 nppVoda_;
	m2 nppZastav_;

	// Uloha 2b
	double buildingChange_;
	//unsigned int buildingChangeYear_;

public:
	TownLand();
	TownLand(m2 celkova, m2 ppOrna, m2 ppOvoc, m2 nppLes, m2 nppVoda, m2 nppZastav);
	~TownLand();

	m2 getCelkovaVymera() { return celkovaVymera_; }
	m2 getPpOrna() { return ppOrna_; }
	m2 getPpOvoc() { return ppOvoc_; }
	m2 getNppLes() { return nppLes_; }
	m2 getNppVoda() { return nppVoda_; }
	m2 getNppZastav() { return nppZastav_; }

	double getBuildingChange() { return buildingChange_; }
	//unsigned int getBuildingChangeYear() { return buildingChangeYear_; }

	void setCelkovaVymera(m2 celk) { celkovaVymera_ = celk; }
	void setPpOrna(m2 orna) { ppOrna_ = orna; }
	void setPpOvoc(m2 ovoc) { ppOvoc_ = ovoc; }
	void setNppLes(m2 les) { nppLes_ = les; }
	void setNppVoda(m2 voda) { nppVoda_ = voda; }
	void setNppZastav(m2 zastav) { nppZastav_ = zastav; }

	void setBuildChange(double bChange) { buildingChange_ = bChange; }
	//void setBuildingChangeYear(unsigned int bYear) { buildingChangeYear_ = bYear; }
};

