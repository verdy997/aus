#include "Zakaznik.h"


Zakaznik::Zakaznik(string nazov, int adresa):
obchodnyNazov(nazov), cisloRegionu(adresa)
{
}

Zakaznik::~Zakaznik()
{
}

string Zakaznik::getObchodnyNazov()
{
	return obchodnyNazov;
}

int Zakaznik::getCisloRegionu()
{
	return cisloRegionu;
}

