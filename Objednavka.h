#pragma once
#include "Zakaznik.h"
#include "Typ_Tov.h"
#include "Typ_Polotovaru.h"
#include <iostream>
#include <string>

using namespace std;

class Objednavka
{
private:
	int datumEvidencie;
	string dodavatel;
	Zakaznik *zakaznik;
	Typ_Tov typTovaru;
	Typ_Polotovaru tp;
	int mnozstvo;
	int datumDorucenia;
	double jednotkovaCena;
	bool zrusena = false;
	bool spracovavana = false;
	bool zrealizovana = false;
	int ID;

public:
	Objednavka(int datumEvidencie, Zakaznik *zakaznik, Typ_Tov typTovaru, int mnozstvo, int datumDorucenia, double jednotkovaCena, int ID);
	Objednavka(int datumEvidencie, string dodavatel , Typ_Polotovaru typTovaru, int mnozstvo, int datumDorucenia, double jednotkovaCena);
	~Objednavka();
	int getDatumEvidencie();
	Zakaznik *getZakaznik();
	Typ_Tov getTypTovaru();
	Typ_Polotovaru getTypPolotovaru();
	int getMnozstvo();
	void setMnozstvo(int mnoz);
	int getDatumDorucenia();
	double getJednotkovaCena();
	bool isZrusena();
	bool isSpracovavana();
	bool isZrealizovana();
	void zrealizujObjednavku();
	void spracujObjednavku();
	void zrusenieObjednavky();
	double getTrzba();
	void vypis();
	int getID();
	void pridajMnozstvo(int mnoz);
	string dajDodavatela();
	void resetujMnozstvo();

};

