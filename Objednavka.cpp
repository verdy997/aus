#include "Objednavka.h"



Objednavka::Objednavka(int datumEvidencie, Zakaznik *zakaznik, Typ_Tov typTovaru, int mnozstvo, int datumDorucenia, double jednotkovaCena, int ID):
datumEvidencie(datumEvidencie), zakaznik(zakaznik), typTovaru(typTovaru), mnozstvo(mnozstvo), datumDorucenia(datumDorucenia), jednotkovaCena(jednotkovaCena), ID(ID)
{
}

Objednavka::Objednavka(int datumEvidencie, string dodavatel, Typ_Polotovaru typTovaru, int mnozstvo, int datumDorucenia, double jednotkovaCena):
	datumEvidencie(datumEvidencie), dodavatel(dodavatel), tp(typTovaru), mnozstvo(mnozstvo), datumDorucenia(datumDorucenia), jednotkovaCena(jednotkovaCena)
{
}

Objednavka::~Objednavka()
{
}

int Objednavka::getDatumEvidencie()
{
	return datumEvidencie;
}

Zakaznik *Objednavka::getZakaznik()
{
	return zakaznik;
}

Typ_Tov Objednavka::getTypTovaru()
{
	return typTovaru;
}

Typ_Polotovaru Objednavka::getTypPolotovaru()
{
	return tp;
}

int Objednavka::getMnozstvo()
{
	return mnozstvo;
}

void Objednavka::setMnozstvo(int mnoz)
{
	mnozstvo -= mnoz;
}

void Objednavka::pridajMnozstvo(int mnoz)
{
	mnozstvo += mnoz;
}

string Objednavka::dajDodavatela()
{
	return dodavatel;
}


void Objednavka::resetujMnozstvo()
{
	mnozstvo = 0;
}


int Objednavka::getDatumDorucenia()
{
	return datumDorucenia;
}

double Objednavka::getJednotkovaCena()
{
	return jednotkovaCena;
}

bool Objednavka::isZrusena()
{
	return zrusena;
}

bool Objednavka::isSpracovavana()
{
	return spracovavana;
}

bool Objednavka::isZrealizovana()
{
	return zrealizovana;
}

void Objednavka::zrealizujObjednavku()
{
	zrealizovana = true;
}

void Objednavka::spracujObjednavku()
{
	spracovavana = true;
}


void Objednavka::zrusenieObjednavky()
{
	zrusena = true;
}

double Objednavka::getTrzba()
{
	return getJednotkovaCena()*getMnozstvo();
}

void Objednavka::vypis()
{

	cout << getZakaznik()->getObchodnyNazov() << "  " << getMnozstvo() << "\n";
}

int Objednavka::getID()
{
	return ID;
}
