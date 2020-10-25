#pragma once
#include <iostream>
#include "Typ_Tov.h"
#include "../sem/structures/list/linked_list.h"

using namespace std;
using namespace structures;

class Vozidlo
{
private:
	Typ_Tov typ_vozidla;
	string spz;
	int prevadzkoveNaklady;
	int kapacita;
	int datumEvidencie;
	int pocetRegionov;
	int celkoveNaklady = 0;
	bool naSklade = true;
	int momentalnaKapacita;
	LinkedList<int> *regiony;
	


public:
	Vozidlo(Typ_Tov typVozidla, string spz, int datum);
	~Vozidlo();
	Typ_Tov getTypVozidla();
	void setTypVozidla(int tv);
	void setPocetAktRegionov(int pocet);
	int getPocetAktRegionov();
	int getKapacita();
	int getPrevadzkoveNaklady();
	string getSpz();
	int getDatumEvidencie();
	int getCelkoveNaklady();
	bool isNasklade();
	void vysliNaCestu();
	void upravKapacitu(int mnozstvo);
	int getAktualnuVolnuKapacitu();
	void pridajRegion(int region);
	int getPrvyRegion();
	void toString();
	void resetKapacity();
	void vratDoGaraze();
	int pocetPrejdenychRegionov();
	bool kontrolaDuplicity(int prvok);
	void setCelkoveNaklady(int naklady);
	void nastavCN(int CN);
};

