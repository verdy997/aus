#include "../sem/Polotovar.h"



	Polotovar::Polotovar(Typ_Polotovaru typ, double cena_polotovaru, int mnozstvo) :
	typPolotovaru(typ), cenaPolotovaru(cena_polotovaru), mnozstvoPolotovaru(mnozstvo)
	{
	}

	Polotovar::~Polotovar()
	{
		
	}

	Typ_Polotovaru Polotovar::getTypPolotovaru()
	{
		return typPolotovaru;
	}

	void Polotovar::setTypPolotovaru(int typ)
	{
		if (typ == 1)
		{
			typPolotovaru = Zemiaky;
		}
		else if (typ == 2)
		{
			typPolotovaru = Olej;
		}
		else if (typ == 3)
		{
			typPolotovaru = Ochucovadla;
		}
		else
		{
			cout << "Zly typ!"; //neskor zmenit na vynimku
		}
	}

	double Polotovar::getCenaPolotovaru()
	{
		return cenaPolotovaru;
	}

	int Polotovar::getMnozstvoPolotovaru()
	{
		return mnozstvoPolotovaru;
	}

	void Polotovar::setMnozstvoPolotovaru(int mnozstvo)
	{
		mnozstvoPolotovaru = mnozstvo;
	}

	void Polotovar::setCenaPolotovaru(double cena)
	{
		cenaPolotovaru = cena;
	}

	double Polotovar::getPriemernaCena()
	{
		return priemernaCena;
	}

	int Polotovar::vygenerujCenu(int polotovar)
	{
		int cena;
		if (polotovar == 1)
		{
			cena = rand() % 3 + 1;
		}
		if (polotovar == 2)
		{
			cena = rand() % 4 + 1;
		}
		if (polotovar == 3)
		{
			cena = rand() % 2 + 1;
		}

		return cena;
	}

	void Polotovar::vygenerujMnozstvo(int polotovar)
	{
		if(polotovar == 1)
		{
			mnozstvoPolotovaru = rand() % 5000;
		}
		if (polotovar == 2)
		{
			mnozstvoPolotovaru = rand() % 1000;
		}
		if(polotovar == 3)
		{
			mnozstvoPolotovaru = rand() % 50;
		}
	}


	