#include "Biofarmar.h"
#include <cstdlib>


Biofarmar::Biofarmar(string nazov, int pocetPolotovarov) :
	obchodnyNazov(nazov)
	{
		polotovary = new Array<Polotovar*>(pocetPolotovarov);
		objednavkyCac = new LinkedList<Objednavka*>;
	}


	Biofarmar::~Biofarmar()
	{
		for (int i = 0; i < polotovary->size(); ++i)
		{
			delete polotovary->operator[](i);
		}
		for (int i = 0; i < objednavkyCac->size(); ++i)
		{
			delete objednavkyCac->operator[](i);
		}
		delete polotovary;
		delete objednavkyCac;
		polotovary = nullptr;
		objednavkyCac = nullptr;
	}

	string Biofarmar::getObchodnyNazov()
	{
		return obchodnyNazov;
	}

	
	string Biofarmar::getPolotovarNaIndexe(int index)
	{
		 return preklad(index);
	}

	void Biofarmar::pridajPolotovar(int pocet)
	{
		int pom;
		int pocet_ = pocet;
		
		for (int j = 0; j < pocet_; ++j)
		{
			Typ_Polotovaru tp = Zemiaky;
			int cena = 0;
			int mnozstvo = 0;

			cout << "Zadaj cislo polotovaru podla napovedy: \n";
			cout << "1. Zemiaky\n";
			cout << "2. Olej\n";
			cout << "3. Ochucovadla\n";
			cin >> pom;

			if (pom <= 3)
			{
				if (!kontrolaTovaru(pom, j))
				{
					switch (pom)
					{
					case 1:
						tp = Zemiaky;
						break;
					case 2:
						tp = Olej;
						break;
					case 3:
						tp = Ochucovadla;
						
						break;
					default:
						break;
					}
					polotovary->operator[](j) = new Polotovar(tp, cena, mnozstvo);
				}
				else
				{
					cout << "VYSKYTLA SA CHYBA!!!\n-Zadany polotovor uz Biofarmar poskytuje!\n";
					j--;
				}
			}
			else
			{
				cout << "Zly typ!"; //neskor zmenit na vynimku
			}
		}
	}

	void Biofarmar::toString(int datum)
	{
		int pom = 0;

		cout << "" + this->getObchodnyNazov() + "\n";
		cout << "Nazov polotovaru:\t" << "Priemerna jednotkova cena:\n";
		for (int i = 0; i < polotovary->size(); i++)
		{
			if(polotovary->operator[](i)->getTypPolotovaru() == 1)
			{
				pom = 1;
			}
			if (polotovary->operator[](i)->getTypPolotovaru() == 2)
			{
				pom = 2;
			}
			if (polotovary->operator[](i)->getTypPolotovaru() == 3)
			{
				pom = 3;
			}
			cout << this->getPolotovarNaIndexe(i) << "\t\t\t" << priemernaCena(pom, datum) << "\n";
		}
	}

	bool Biofarmar::kontrolaTovaru(int kont, int pom)
	{
		if (pom != 0)
		{
			for (int i = pom - 1; i >= 0; --i)
			{
				cout << polotovary->operator[](i)->getTypPolotovaru();
				if (polotovary->operator[](i)->getTypPolotovaru() == kont)
				{
					return true;
				}
			}
		}
		return false;
	}

	int Biofarmar::prijmiObjednavku(int polotovar, int mnozstvo, int datum)
	{
		Typ_Polotovaru tp;
		int pomCislo = 0;
		
			for (int i = 0; i < polotovary->size(); ++i)
			{
				if (polotovary->operator[](i)->getTypPolotovaru() == polotovar)
				{
					polotovary->operator[](i)->vygenerujMnozstvo(polotovar);
					pomCislo += polotovary->operator[](i)->getMnozstvoPolotovaru();
					if (pomCislo != 0)
					{
						int cena = polotovary->operator[](i)->vygenerujCenu(polotovar);
						objednavkyCac->add(new Objednavka(datum, getObchodnyNazov(), polotovary->operator[](i)->getTypPolotovaru(), pomCislo, datum + 1, cena));
					}
					return pomCislo;
				}
			}
	}

	int Biofarmar::dajJednotkovuCenu(int polotovar)
	{
		//polotovary->operator[]()
		return 0;
	}

	double Biofarmar::priemernaCena(int polotovar, int datum)
	{
		double pom = 0;
		double pom2 = 0;
		if (objednavkyCac->size() != 0)
		{
			for (int i = 0; i < objednavkyCac->size(); ++i)
			{
				if (objednavkyCac->operator[](i)->getTypPolotovaru() == polotovar)
				{
					if (objednavkyCac->operator[](i)->getDatumEvidencie() >= datum - 30)
					{
						pom += objednavkyCac->operator[](i)->getJednotkovaCena();
						pom2++;
					}
				}
			}
			if(pom != 0 && pom2 != 0)
			{
				return pom / pom2;
			}
		}
		return 999;
	}

	int Biofarmar::pocetPredanychPolotovarov(int polotovar, int datum)
	{

		int mnozstvo = 0;
		for (int i = 0; i < objednavkyCac->size(); ++i)
		{
			if (polotovar == objednavkyCac->operator[](i)->getTypPolotovaru())
			{
				if (objednavkyCac->operator[](i)->getDatumEvidencie() >= datum-30)
				{
					mnozstvo += objednavkyCac->operator[](i)->getMnozstvo();

				}
			}
		}
		
		return mnozstvo;
	}

	bool Biofarmar::ponukaPolotovar(int polotovar)
	{
		cout << "biofarmar: " << this->getObchodnyNazov() << "polotovar: " << polotovar << "\n";
		if (polotovary->size() != 0)
		{
			for (int i = 0; i < polotovary->size(); ++i)
			{
				if (polotovary->operator[](i)->getTypPolotovaru() == polotovar)
				{
					return true;
				}
			}
		}
		
		return false;
	}

	int Biofarmar::velkostPola()
	{
		return polotovary->size();
	}

	int Biofarmar::getPrvokPolaNaPozicii(int pozicia)
	{
		return polotovary->operator[](pozicia)->getTypPolotovaru();
	}

	void Biofarmar::zapisObjednavok(string nazov)
	{
		zapis.open(nazov);
		for (int i = 0; i < objednavkyCac->size(); ++i)
		{
			zapis << objednavkyCac->operator[](i)->getDatumEvidencie();
			zapis << " ";
			zapis << objednavkyCac->operator[](i)->dajDodavatela();
			zapis << " ";
			zapis << objednavkyCac->operator[](i)->getTypPolotovaru();
			zapis << " ";
			zapis << objednavkyCac->operator[](i)->getMnozstvo();
			zapis << " ";
			zapis << objednavkyCac->operator[](i)->getDatumDorucenia();
			zapis << " ";
			zapis << objednavkyCac->operator[](i)->getJednotkovaCena();
			zapis << " ";
		}
		zapis.close();
	}

	void Biofarmar::nacitanieObjednavok(string nazov)
	{
		Typ_Polotovaru typT;
		string spolocnost;
		int DE, typ, mnozstvo, DD, JC;
		ifstream nacitaj(nazov);
		while (!nacitaj.eof())
		{
			nacitaj >> DE >> spolocnost >> typ >> mnozstvo >> DD >> JC;

			if (typ == 1)
			{
				typT = Zemiaky;
			}
			else if (typ == 2)
			{
				typT = Olej;
			}
			else if (typ == 3)
			{
				typT = Ochucovadla;
			}

			if (getObchodnyNazov() == spolocnost)
			{
					objednavkyCac->add(new Objednavka(DE, getObchodnyNazov(), typT, mnozstvo, DD, JC));
			}
		}
		nacitaj.close();
	}
		
	

	void Biofarmar::setPolotovar(int typ, int pozicia)
	{
		Typ_Polotovaru tp;

		switch (typ)
		{
		case 1:
			tp = Zemiaky;
			break;
		case 2:
			tp = Olej;
			break;
		case 3:
			tp = Ochucovadla;
			break;
		}
			polotovary->operator[](pozicia) = new Polotovar(tp, 0, 0);
		
		
	}

	string Biofarmar::preklad(int poradie)
	{
		if (polotovary->operator[](poradie)->getTypPolotovaru() == 1)
		{
			return "Zemiaky";
		}
		else if (polotovary->operator[](poradie)->getTypPolotovaru() == 2)
		{
			return "Olej";
		}
		else if (polotovary->operator[](poradie)->getTypPolotovaru() == 3)
		{
			return "Ochucovadla";
		}
		else
		{
			cout << "Zly typ!";
		}
	}

