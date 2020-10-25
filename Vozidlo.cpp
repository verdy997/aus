#include "Vozidlo.h"



Vozidlo::Vozidlo(Typ_Tov typVozidla, string spz, int datum):
spz(spz), datumEvidencie(datum)
{
	setTypVozidla(typVozidla);

	if (typVozidla == 1)
	{
		kapacita = 5000;
		momentalnaKapacita = 5000;
		prevadzkoveNaklady = 100;
	} 
	else if (typVozidla == 2)
	{
		kapacita = 2000;
		momentalnaKapacita = 2000;
		prevadzkoveNaklady = 70;
	}
	else
	{
		cout << "Chybny typ vozidla!";
	}

	regiony = new LinkedList<int>;
}

Vozidlo::~Vozidlo()
{
	delete regiony;
	regiony = nullptr;
}

Typ_Tov Vozidlo::getTypVozidla()
{
	return typ_vozidla;
}

void Vozidlo::setTypVozidla(int tv)
{
	if (tv == 1)
	{
		typ_vozidla = Hranolceky;
	}
	else if (tv == 2)
	{
		typ_vozidla = Lupienky;
	}
	else
	{
		cout << "vyskyla sa chyba, pozadovany typ neexistuje!";
	}
}

void Vozidlo::setPocetAktRegionov(int pocet)
{
	pocetRegionov = pocet;
}

int Vozidlo::getPocetAktRegionov()
{
	return pocetRegionov;
}

int Vozidlo::getKapacita()
{
	return kapacita;
}

int Vozidlo::getPrevadzkoveNaklady()
{
	return prevadzkoveNaklady;
}

string Vozidlo::getSpz()
{
	return spz;
}

int Vozidlo::getDatumEvidencie()
{
	return datumEvidencie;
}

int Vozidlo::getCelkoveNaklady()
{
	return celkoveNaklady;
}

bool Vozidlo::isNasklade()
{
	return naSklade;
}

void Vozidlo::vysliNaCestu()
{
	naSklade = false;
}

void Vozidlo::upravKapacitu(int mnozstvo)
{
	momentalnaKapacita -= mnozstvo;
}

int Vozidlo::getAktualnuVolnuKapacitu()
{
	return momentalnaKapacita;
}

void Vozidlo::pridajRegion(int region)
{
	cout << "velkost pola regionov pri vozidle" << this->getSpz() << "je" << regiony->size() << "\n";
	if (regiony->size() != 0)
	{
		cout << "index rovnakeho prvku je:  " << this->kontrolaDuplicity(region);
		
		if (!this->kontrolaDuplicity(region))
		{
			regiony->add(region);
			cout << "pridal som vozidlu" << this->getSpz() << "region s cislom " << region << "\n";
		}
	}
	else
	{
		regiony->add(region);
		cout << "pridal som vozidlu" << this->getSpz() << "region s cislom " << region << "\n";
	}
	
}

int Vozidlo::getPrvyRegion()
{
	if (regiony->size() != 0)
	{
		return regiony->operator[](0);
	}
	else
	{
		return 99;
	}
	
}

void Vozidlo::toString()
{

	//cout << &getTypVozidla << "  " << &getSpz << "  " << &getAktualnuVolnuKapacitu << " " << regiony->size() << " \n";
}

void Vozidlo::resetKapacity()
{
	momentalnaKapacita = kapacita;
}

void Vozidlo::vratDoGaraze()
{
	naSklade = true;
}

int Vozidlo::pocetPrejdenychRegionov()
{
	cout << "vozidlo: " << this->getSpz() << " ma regiony: ";
	for (int i = 0; i < regiony->size(); ++i)
	{
		cout << regiony->operator[](i);
	}

	cout << "\n";

	return regiony->size();
}

bool Vozidlo::kontrolaDuplicity(int prvok)
{
	for (int i = 0; i < regiony->size(); ++i)
	{
		if(regiony->operator[](i) == prvok)
		{
			return true;
		}
	}
	return false;
}

void Vozidlo::setCelkoveNaklady(int naklady)
{
	celkoveNaklady = prevadzkoveNaklady*naklady;
}

void Vozidlo::nastavCN(int CN)
{
	celkoveNaklady = CN;
}
