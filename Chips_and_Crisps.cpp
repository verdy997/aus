#include "Chips_and_Crisps.h"
#include "../sem/structures/heap_monitor.h"



Chips_and_Crisps::Chips_and_Crisps()
{
	biofarmari = new LinkedList<Biofarmar*>;
	vozidla = new LinkedList<Vozidlo*>;
	zakaznici = new LinkedList<Zakaznik*>;
	objednavky = new LinkedList<Objednavka*>;
	zamietnute = new LinkedList<Objednavka*>;
	zrusene = new LinkedList<Objednavka*>;
	spracovavane = new PriorityQueueLinkedList<Objednavka*>;
	aktualneNaCeste = new LinkedList<Objednavka*>;
	zrealizovane = new LinkedList<Objednavka*>;
}


Chips_and_Crisps::~Chips_and_Crisps()
{
	zapisBiofarmarov();
	zapisVozidla();
	zapisZakaznikov();
	zapisObjednavky();
	zapisZamietnute();
	zapisZrealizovane();
	zapisZrusene();
	zapisObjednavokBiofarmara();

	for (Objednavka *objednavka : *objednavky)
	{
		delete objednavka;
	}
	for (Biofarmar *biofarmar : *biofarmari)
	{
		delete biofarmar;
	}
	for (Vozidlo *vozidlo : *vozidla)
	{
		delete vozidlo;
	}
	for (Zakaznik *zakaznik : *zakaznici)
	{
		delete zakaznik;
	}
	for (Objednavka *zamietnuta : *zamietnute)
	{
		delete zamietnuta;
	}
	for (Objednavka *zrusena : *zrusene)
	{
		delete zrusena;
	}
	for (Objednavka *aktNaCeste : *aktualneNaCeste)
	{
		delete aktNaCeste;
	}
	if (nacitavalSom)
	{
		for (Objednavka *zrealizovana : *zrealizovane)
		{
			delete zrealizovana;
		}
	}
	
	

	spracovavane->clear();

	delete biofarmari;
	delete vozidla;
	delete zakaznici;
	delete objednavky;
	delete zamietnute;
	delete zrusene;
	delete aktualneNaCeste;
	delete spracovavane;
	delete zrealizovane;

	biofarmari = nullptr;
	vozidla = nullptr;
	zakaznici = nullptr;
	objednavky = nullptr;
	zamietnute = nullptr;
	zrusene = nullptr;
	aktualneNaCeste = nullptr;
	spracovavane = nullptr;
	zrealizovane = nullptr;
}

void Chips_and_Crisps::pridajBiofarmara(string nazov, int pocetPolotovarov)
{
	if (biofarmari->size() == 0)
	{
		biofarmari->add(new Biofarmar(nazov, pocetPolotovarov));
		if (biofarmari->operator[](0)->getObchodnyNazov() == nazov)
		{
			biofarmari->operator[](0)->pridajPolotovar(pocetPolotovarov);
		}
	}
	else
	{
		for (int i = 0; i < biofarmari->size(); i++)
		{

			if (nazov < biofarmari->operator[](i)->getObchodnyNazov())
			{
				biofarmari->insert(new Biofarmar(nazov, pocetPolotovarov), i);
				cout << biofarmari->operator[](i)->getObchodnyNazov();
				if (biofarmari->operator[](i)->getObchodnyNazov() == nazov)
				{
					biofarmari->operator[](i)->pridajPolotovar(pocetPolotovarov);
					break;
				}
			}
			else if (biofarmari->size() -1 == i)
			{
				i++;
				biofarmari->add(new Biofarmar(nazov, pocetPolotovarov));
				if (biofarmari->operator[](i)->getObchodnyNazov() == nazov)
				{
					biofarmari->operator[](i)->pridajPolotovar(pocetPolotovarov);
					break;
				}
			}
		}
	}
}

void Chips_and_Crisps::pridajVozidlo()
{
	Typ_Tov typ_vozidla;
	string spz;
	int intpom;

	cout << "Zadaj podla napovedy typ vozidla: \n";
	cout << "1. Auto na prevoz Hranolcekov\n";
	cout << "2. Auto na prevoz Lupienkov\n";
	cin >> intpom;

	switch (intpom)
	{
		case 1:
			typ_vozidla = Hranolceky;
			break;
		case 2:
			typ_vozidla = Lupienky;
			break;
		default:
			cout << "Neplatny vstup!\n";
			break;
	}

	cout << "Zadaj spz: \n";
	cin >> spz;

	if (kontrolaSPZ(spz))
	{
		cout << "VYSKYTLA SA CHYBA!\n-Vozidlo s takouto SPZ uz existuje!\n";
	}
	else
	{

		vozidla->add(new Vozidlo(typ_vozidla, spz, dnesnyDatum));
	}
}

void Chips_and_Crisps::vypisVozidiel()
{
	cout << "SPZ\t typ vozidla\t datum evidencie\t celkove naklady\n";
	for (int j = 0; j < vozidla->size(); ++j)
	{
		if (vozidla->operator[](j)->getTypVozidla() == 1)
		{
			cout << vozidla->operator[](j)->getSpz() << "\t" << "Hranolceky\t" << vozidla->operator[](j)->getDatumEvidencie() << "\t"
				<< vozidla->operator[](j)->getCelkoveNaklady() << "\n";
		}
		else
		{
			cout << vozidla->operator[](j)->getSpz() << "\t" << "Lupienky\t" << vozidla->operator[](j)->getDatumEvidencie() << "\t"
				<< vozidla->operator[](j)->getCelkoveNaklady() << "\n";
		}
	}
}

void Chips_and_Crisps::pridajZakaznika()
{
	string pomString;
	int pomCislo;

	cout << "Zadaj obchodny nazov noveho zakaznika:\n";
	cin >> pomString;

	if (kontrolaZakaznika(pomString))
	{
		cout << "VYSKYTLA SA CHYBA!!!\n-Zakaznik s takymto nazvom uz existuje!\n";
	}
	else
	{
		cout << "Zadaj cislo regionu (od 1 po 8)\n";
		cin >> pomCislo;
		if (pomCislo > 8)
		{
			cout << "VYSKYTLA SA CHYBA!!!\n-Zadany region neexistuje!\n";
		}
		else
		{
			if (zakaznici->size() == 0)
			{
				zakaznici->add(new Zakaznik(pomString, pomCislo));
			}
			else
			{
				for (int i = 0; i < zakaznici->size(); i++)
				{

					if (pomString < zakaznici->operator[](i)->getObchodnyNazov())
					{
						zakaznici->insert(new Zakaznik(pomString, pomCislo), i);
						break;
					}
					else if (zakaznici->size() - 1 == i)
					{
						i++;
						zakaznici->add(new Zakaznik(pomString, pomCislo));
						break;
					}
				}
			}
		}
	}
}

void Chips_and_Crisps::vypisZakaznikov()
{
	int datum;
	int pom;
	
	cout << "Zadaj region z ktoreho chces vypisat zoznam zakaznikov: \n";
	cin >> pom;
	cout << "Od ktoreho datumu chces vidiet vypis: \n";
	cin >> datum;
	for (int i = 0; i < zakaznici->size(); ++i)
	{
		if (zakaznici->operator[](i)->getCisloRegionu() == pom)
		{
			cout << zakaznici->operator[](i)->getObchodnyNazov() << "\n";
			int mnozstvo = 0;
			double trzba = 0;
			int pocet = 0;
			cout << "Zrealizovane: \n";
			for (int j = 0; j < zrealizovane->size(); ++j)
			{
				
				if (zrealizovane->operator[](j)->getZakaznik()->getObchodnyNazov() == zakaznici->operator[](i)->getObchodnyNazov())
				{
					if (zrealizovane->operator[](j)->getDatumDorucenia() > datum)
					{
						pocet++;
						mnozstvo += zrealizovane->operator[](j)->getMnozstvo();
						trzba += zrealizovane->operator[](j)->getMnozstvo()*zrealizovane->operator[](j)->getJednotkovaCena();
					}
				}
			}
			cout << "Celkovy pocet objednavok: " << pocet << "\tHmotnost: " << mnozstvo << "\tCelkova trzba:" << trzba <<"\n";
			cout << "Zrusene: \n";
			mnozstvo = 0;
			trzba = 0;
			pocet = 0;
			for (int j = 0; j < zrusene->size(); ++j)
			{

				if (zrusene->operator[](j)->getZakaznik()->getObchodnyNazov() == zakaznici->operator[](i)->getObchodnyNazov())
				{
					if (zrusene->operator[](j)->getDatumDorucenia() > datum)
					{
						pocet++;
						mnozstvo += zrusene->operator[](j)->getMnozstvo();
						trzba += zrusene->operator[](j)->getMnozstvo()*zrusene->operator[](j)->getJednotkovaCena();
					}
				}
			}
			cout << "Celkovy pocet objednavok: " << pocet << "\tHmotnost: " << mnozstvo << "\tCelkova trzba:" << trzba << "\n";

			cout << "Zamietnute: \n";
			mnozstvo = 0;
			trzba = 0;
			pocet = 0;
			for (int j = 0; j < zamietnute->size(); ++j)
			{

				if (zamietnute->operator[](j)->getZakaznik()->getObchodnyNazov() == zakaznici->operator[](i)->getObchodnyNazov())
				{
					if (zamietnute->operator[](j)->getDatumDorucenia() > datum)
					{
						pocet++;
						mnozstvo += zamietnute->operator[](j)->getMnozstvo();
						trzba += zamietnute->operator[](j)->getMnozstvo()*zamietnute->operator[](j)->getJednotkovaCena();
					}
				}
			}
			cout << "Celkovy pocet objednavok: " << pocet << "\tHmotnost: " << mnozstvo << "\tCelkova trzba:" << trzba << "\n";
		}
	}
}

void Chips_and_Crisps::novaObjednavka()
{
	Typ_Tov Typ;
	string zakaznik;
	int typTovaru, datumDorucenia, jednotkovaCena;
	int mnozstvo;

	cout << "Zadajte obchodny nazov zakaznika: \n";
	cin >> zakaznik;
	if (kontrolaZakaznika(zakaznik))
	{
		cout << "Zadajte typ tovaru: \n";
		cout << "1. Hranolceky\n";
		cout << "2. Lupienky\n";
		cin >> typTovaru;
		switch (typTovaru)
		{
		case 1:
			Typ = Hranolceky;
			break;
		case 2:
			Typ = Lupienky;
			break;
		default:
			cout << "Neplatny vstup!\n";
			return;
		}

		cout << "Zadajte mnozstvo tovaru: \n";
		cin >> mnozstvo;

		cout << "Zadajte jednotkovu cenu tovaru: \n";
		cin >> jednotkovaCena;

		cout << "Zadajte datum dorucenia tovaru: \n";
		cin >> datumDorucenia;
		if (datumDorucenia >= dnesnyDatum + 7)
		{
			for (int i = 0; i < zakaznici->size(); ++i)
			{
				if (Typ == Hranolceky && mnozstvo < 5000 || Typ == Lupienky && mnozstvo < 2000) // vyhodit
				{
					if(zakaznici->operator[](i)->getObchodnyNazov() == zakaznik)
					{
						if (KontrolaKapacity(datumDorucenia, Typ, mnozstvo))
						{
							cout << "typ tovaru:" << typTovaru << " \n";
							objednavky->add(new Objednavka(dnesnyDatum, zakaznici->operator[](i), Typ, mnozstvo, datumDorucenia, jednotkovaCena, objednavky->size()+1));
						}
						else
						{
							cout << "Objednavka bola ZAMIETNUTA!\n Na zadany den su objednavky plne!";
							zamietnute->add(new Objednavka(dnesnyDatum, zakaznici->operator[](i), Typ, mnozstvo, datumDorucenia, jednotkovaCena, zamietnute->size() + 1));
						}
					}
				}
				else
				{
					if (zakaznici->operator[](i)->getObchodnyNazov() == zakaznik)
					{
						cout << "Objednavka bola ZAMIETNUTA!\n Prekroceny limit!";
						zamietnute->add(new Objednavka(dnesnyDatum, zakaznici->operator[](i), Typ, mnozstvo, datumDorucenia, jednotkovaCena, zamietnute->size() + 1));
					}
				}
			}
			
		}
		else
		{
			cout << "VYSKYTLA SA CHYBA! - Nieje mozne v casovom obdobi objednavku zrealizovat!";
		}
	}
}



bool Chips_and_Crisps::kontrolaNazvuBiofarmara(string nazov)
{
	if(biofarmari->size() != 0)
	{
		for (int i = 0; i <= biofarmari->size() - 1; i++)
		{
			if (biofarmari->operator[](i)->getObchodnyNazov() == nazov)
			{
				return true;
			}
		}
	}
	return false;
}

bool Chips_and_Crisps::kontrolaZakaznika(string nazov)
{
	if (zakaznici->size() != 0)
	{
		for (int i = 0; i < zakaznici->size(); ++i)
		{
			if (zakaznici->operator[](i)->getObchodnyNazov() == nazov)
			{
				return true;
			}
		}
	}
	return false;
}

bool Chips_and_Crisps::kontrolaSPZ(string spz)
{
	if (vozidla->size() != 0)
	{
		for (int i = 0; i < vozidla->size(); ++i)
		{
			if (vozidla->operator[](i)->getSpz() == spz)
			{
				return true;
			}
		}
	}
	return false;
}

void Chips_and_Crisps::setDatum(int datum)
{
	dnesnyDatum = datum;
}

int Chips_and_Crisps::getDnesnyDatum()
{
	return dnesnyDatum;
}

void Chips_and_Crisps::posunDen()
{
	dnesnyDatum++;
	cout << "NOVY DEN! CISLO DNA JE: " << dnesnyDatum << "\n";
}

int Chips_and_Crisps::getCelkovaKapacitaVozidielPreDen(int den, int typ)
{
	return celkovaKapacitaVozidielPreDen;
}

int Chips_and_Crisps::KapacitaVozidiel(Typ_Tov tp)
{
	int pom = 0;

	for (int i = 0; i < vozidla->size(); ++i)
	{
		if (vozidla->operator[](i)->getTypVozidla() == tp)
		{
			pom += vozidla->operator[](i)->getKapacita();
		}
	}
	return pom;
}

bool Chips_and_Crisps::KontrolaKapacity(int den, int typ, int mnozstvo)
{
	Typ_Tov tp;
	int pom = 0;

	if (typ == 1)
	{
		tp = Hranolceky;
	}
	else if (typ == 2)
	{
		tp = Lupienky;
	}

	for (int i = 0; i < objednavky->size(); ++i)
	{
		if (objednavky->operator[](i)->getTypTovaru() == tp)
		{
			if (objednavky->operator[](i)->getDatumDorucenia() == den)
			{
				pom += objednavky->operator[](i)->getMnozstvo();
			}
		}
	}
	pom += mnozstvo;
	cout << "kapacita je:" << KapacitaVozidiel(tp) << "\n";
	cout << "potrebna kapacita je:" << pom << "\n";

	if(KapacitaVozidiel(tp) > pom)
	{
		return true;
	}
	return false;
}

void Chips_and_Crisps::kontrolaNasledujucich7dni(int den)
{
	double mnozstvo;
	double pomZem = 0;
	double pomOle = 0;
	double pomOch = 0;

	pomZem = vseobecnaKontrolaTovaru(dnesnyDatum, 1.5, 7, 1) + vseobecnaKontrolaTovaru(dnesnyDatum, 2, 7, 2);
	pomOle = vseobecnaKontrolaTovaru(dnesnyDatum, 0.2, 7, 1) + vseobecnaKontrolaTovaru(dnesnyDatum, 0.4, 7, 2);
	pomOch = vseobecnaKontrolaTovaru(dnesnyDatum, 0.02, 7, 2);

	cout << "je potrebne zemiakov:" << pomZem << " \n";
	cout << "je potrebne oleja:" << pomOle << " \n";
	cout << "je potrebne ochucovadiel:" << pomOch << " \n";

	LinkedList<Biofarmar*> *pomocny = new LinkedList<Biofarmar*>;
	for (int i = 0; i < biofarmari->size(); ++i)
	{
		if (biofarmari->operator[](i)->ponukaPolotovar(1))
		{
			if (pomocny->size() == 0)
			{
				pomocny->add(biofarmari->operator[](i));
			}
			else
			{
				for (int k = 0; k < pomocny->size(); ++k)
				{
					if (biofarmari->operator[](i)->priemernaCena(1, dnesnyDatum) <
						pomocny->operator[](k)->priemernaCena(1, dnesnyDatum))
					{
						pomocny->insert(biofarmari->operator[](i), k);
						break;
					}
					else if (pomocny->size() - 1 == k)
					{
						k++;
						pomocny->add(biofarmari->operator[](k));
						break;
					}
				}
			}
		}
	}


	if(mnozstvoZemiakovNaSklade < pomZem)
	{
		pomZem -= mnozstvoZemiakovNaSklade;
		for (int i = 0; i < pomocny->size(); ++i)
		{
			mnozstvo = pomocny->operator[](i)->prijmiObjednavku(1, pomZem, dnesnyDatum);
			if(mnozstvo != 0)
			{
				mnozstvoZemiakovNaSklade += mnozstvo;
				if (pomZem <= mnozstvoZemiakovNaSklade)
				{
					break;
				}
			}
		}
		cout << "donesu mi zemiakov:" << mnozstvoZemiakovNaSklade << " \n";
	}
	pomocny->clear();
	
	for (int i = 0; i < biofarmari->size(); ++i)
	{
		if (biofarmari->operator[](i)->ponukaPolotovar(2))
		{
			if (pomocny->size() == 0)
			{
				pomocny->add(biofarmari->operator[](i));
			}
			else
			{
				for (int k = 0; k < pomocny->size(); ++k)
				{
					if (biofarmari->operator[](i)->priemernaCena(2, dnesnyDatum) <
						pomocny->operator[](k)->priemernaCena(2, dnesnyDatum))
					{
						pomocny->insert(biofarmari->operator[](i), k);
						break;
					}
					else if (pomocny->size() - 1 == k)
					{
						k++;
						pomocny->add(biofarmari->operator[](k));
						break;
					}
				}
			}
		}
	}

	if (mnozstvoOlejaNaSklade < pomOle)
	{
		pomOle -= mnozstvoOlejaNaSklade;
		for (int i = 0; i < pomocny->size(); ++i)
		{
			mnozstvo = pomocny->operator[](i)->prijmiObjednavku(2, pomOle, dnesnyDatum);
			if (mnozstvo != 0)
			{
				mnozstvoOlejaNaSklade += mnozstvo;
				if (pomOle <= mnozstvoOlejaNaSklade)
				{
					break;
				}
			}
		}
	}

	cout << "donesu mi oleja:" << mnozstvoOlejaNaSklade << " \n";

	pomocny->clear();

	for (int i = 0; i < biofarmari->size(); ++i)
	{
		if (biofarmari->operator[](i)->ponukaPolotovar(3))
		{
			if (pomocny->size() == 0)
			{
				pomocny->add(biofarmari->operator[](i));
			}
			else
			{
				for (int k = 0; k < pomocny->size(); ++k)
				{
					if (biofarmari->operator[](i)->priemernaCena(3, dnesnyDatum) <
						pomocny->operator[](k)->priemernaCena(3, dnesnyDatum))
					{
						pomocny->insert(biofarmari->operator[](i), k);
						break;
					}
					else if (pomocny->size() - 1 == k)
					{
						k++;
						pomocny->add(biofarmari->operator[](k));
						break;
					}
				}
			}
		}
	}

	if (mnozstvoOchucovadielNaSklade < pomOch)
	{
		pomOch -= mnozstvoOchucovadielNaSklade;
		for (int i = 0; i < pomocny->size(); ++i)
		{
			mnozstvo = pomocny->operator[](i)->prijmiObjednavku(3, pomOch, dnesnyDatum);
			if (mnozstvo != 0)
			{
				mnozstvoOchucovadielNaSklade += mnozstvo;
				if (pomOch <= mnozstvoOchucovadielNaSklade)
				{
					break;
				}

			}
		}
	}

	pomocny->clear();
	delete pomocny;
	pomocny = nullptr;
}

double Chips_and_Crisps::getFinancieFirmy()
{
	return financieFirmy;
}


void Chips_and_Crisps::vypisBiofarmarov()
{
	for (int i = 0; i <= biofarmari->size()-1; ++i)
	{
		biofarmari->operator[](i)->toString(dnesnyDatum);
	}
}

void Chips_and_Crisps::kontrolaNasledujucehoDna(int den)
{
	double trzba;
	int pomint = 0;

	double pomZem = 0;
	double pomOle = 0;
	double pomOch = 0;

	for (int i = 0; i < objednavky->size(); ++i)
	{
		pomZem = vseobecnaKontrolaTovaru(den, 1.5, 0, 1) + vseobecnaKontrolaTovaru(den, 2, 0, 2);
		pomOle = vseobecnaKontrolaTovaru(den, 0.2, 0, 1) + vseobecnaKontrolaTovaru(den, 0.4, 0, 2);
		pomOch = vseobecnaKontrolaTovaru(den, 0.02, 0, 2);

		if (pomZem > mnozstvoZemiakovNaSklade || pomOle > mnozstvoOlejaNaSklade || pomOch > mnozstvoOchucovadielNaSklade)
		{
			zrusObjednavkuSNajnizsovTrzbov();
			pomint++;
		}
		else
		{
			cout << "potrebny pocet zemiakov je " << pomZem << "\n";
			break;
		}
	}

	cout << "Nazov zakaznika\t Region cislo\t Datum evidencie\t Typ tovaru  mnozstvo  jednotkova cena  celkove Trzby\n\n";

	for (int i = 0; i < objednavky->size(); ++i)
	{
		if (objednavky->operator[](i)->getDatumDorucenia() == den)
		{
			if (!objednavky->operator[](i)->isZrusena())
			{
				cout << objednavky->operator[](i)->getZakaznik()->getObchodnyNazov() << "\t\t\t" << objednavky->operator[](i)->getZakaznik()->getCisloRegionu()
				<< "\t\t" << objednavky->operator[](i)->getDatumEvidencie()
					<< "\t\t" << objednavky->operator[](i)->getTypTovaru() << "\t\t" << objednavky->operator[](i)->getMnozstvo() << "\t\t" <<
					objednavky->operator[](i)->getJednotkovaCena() << "\t\t" << objednavky->operator[](i)->getTrzba() << "\n\n";
			}
		}
	}

	cout << "ZAMIETNUTE OBJEDNAVKY\n\n";
	cout << "Nazov zakaznika\t Region cislo\t Datum evidencie\t Typ tovaru  mnozstvo  jednotkova cena  celkove Trzby\n\n";
	
	for (int i = 0; i < zamietnute->size(); ++i)
	{
		if (zamietnute->operator[](i)->getDatumDorucenia() == den)
		{
			cout << zamietnute->operator[](i)->getZakaznik()->getObchodnyNazov() << "\t\t\t" << zamietnute->operator[](i)->getZakaznik()->getCisloRegionu()
			<< "\t\t" << zamietnute->operator[](i)->getDatumEvidencie()
				<< "\t\t" << zamietnute->operator[](i)->getTypTovaru() << "\t\t" << zamietnute->operator[](i)->getMnozstvo() << "\t\t" <<
				zamietnute->operator[](i)->getJednotkovaCena() << "\t\t" << zamietnute->operator[](i)->getTrzba() << "\n\n";
		}
	}

	cout << "ZRUSENE OBJEDNAVKY\n\n";
	cout << "Nazov zakaznika\t Region cislo\t Datum evidencie\t Typ tovaru  mnozstvo  jednotkova cena  celkove Trzby\n\n";
	for (int i = 0; i < zrusene->size(); ++i)
	{
		if (zrusene->operator[](i)->getDatumDorucenia() == den)
		{
			cout << zrusene->operator[](i)->getZakaznik()->getObchodnyNazov() << "\t\t\t" << zrusene->operator[](i)->getZakaznik()->getCisloRegionu()
				<< "\t\t" << zrusene->operator[](i)->getDatumEvidencie()
				<< "\t\t" << zrusene->operator[](i)->getTypTovaru() << "\t\t" << zrusene->operator[](i)->getMnozstvo() << "\t\t" <<
				zrusene->operator[](i)->getJednotkovaCena() << "\t\t" << zrusene->operator[](i)->getTrzba() << "\n\n";
		}
	}
}

double Chips_and_Crisps::vseobecnaKontrolaTovaru(int zacDatum, double konstanta, int kolkoDni, int typ)
{
	double konPolotovar = 0;
	for (int i = zacDatum; i <= zacDatum + kolkoDni; ++i)
	{
		for (int j = 0; j < objednavky->size(); ++j)
		{
			if (objednavky->operator[](j)->getDatumDorucenia() == i)
			{
				if (!objednavky->operator[](j)->isZrusena())
				{
					if (objednavky->operator[](j)->getTypTovaru() == typ)
					{
						konPolotovar += objednavky->operator[](j)->getMnozstvo() * konstanta;
					}
				}
			}
		}
	}
	return konPolotovar;
}

void Chips_and_Crisps::naplnVozidlo()
{
	for (int i = 0; i < objednavky->size(); ++i)
	{
		if (!objednavky->operator[](i)->isZrusena())
		{
			if (objednavky->operator[](i)->getDatumDorucenia() == dnesnyDatum)
			{
				int priorita = (objednavky->operator[](i)->getDatumDorucenia() * 100) + objednavky->operator[](i)->getZakaznik()->getCisloRegionu();
				spracovavane->push(priorita, objednavky->operator[](i));
				objednavky->removeAt(i);
				i--;
			}
		}
	}

	for (int i = 0; i < spracovavane->size(); ++i)
	{
		for (int j = 0; j < vozidla->size(); ++j)
		{
			if (spracovavane->size() != 0)
			{
				if (spracovavane->peek()->getTypTovaru() == vozidla->operator[](j)->getTypVozidla())
				{
					if (vozidla->operator[](j)->getAktualnuVolnuKapacitu() != 0)
					{
						if (vozidla->operator[](j)->isNasklade())
						{
							int region;
							double mnozstvo;
							mnozstvo = spracovavane->peek()->getMnozstvo();
							
							if (vozidla->operator[](j)->getAktualnuVolnuKapacitu() >= mnozstvo)
							{
								vozidla->operator[](j)->upravKapacitu(mnozstvo);
								aktualneNaCeste->add(spracovavane->peek());
								region = spracovavane->peek()->getZakaznik()->getCisloRegionu();
								vozidla->operator[](j)->pridajRegion(region);
								cout << "pridany region je " << region << "\n";
								spracovavane->pop();
								
								if (vozidla->operator[](j)->getAktualnuVolnuKapacitu() == 0)
								{
									vozidla->operator[](j)->vysliNaCestu();
								}
								j--;
							}
							else
							{
								if (vozidla->operator[](j)->getKapacita() == vozidla->operator[](j)->getAktualnuVolnuKapacitu())
								{
									mnozstvo -= vozidla->operator[](j)->getKapacita();
									vozidla->operator[](j)->upravKapacitu(vozidla->operator[](j)->getKapacita());
									region = spracovavane->peek()->getZakaznik()->getCisloRegionu();
									vozidla->operator[](j)->pridajRegion(region);
									cout << "pridany region je " << region << "\n";
									vozidla->operator[](j)->vysliNaCestu();
									spracovavane->peek()->setMnozstvo(vozidla->operator[](j)->getKapacita());
									j--;
								}
								else
								{
									int pom = vozidla->operator[](j)->getKapacita() - (vozidla->operator[](j)->getKapacita() - vozidla->operator[](j)->getAktualnuVolnuKapacitu());
									//aktualneNaCeste->add();
									region = spracovavane->peek()->getZakaznik()->getCisloRegionu();
									vozidla->operator[](j)->pridajRegion(region);
									cout << "pridany region je " << region << "\n";
									vozidla->operator[](j)->vysliNaCestu();
									aktualneNaCeste->add(new Objednavka(spracovavane->peek()->getDatumEvidencie(), spracovavane->peek()->getZakaznik() ,
										spracovavane->peek()->getTypTovaru(), pom, spracovavane->peek()->getDatumDorucenia(),
										spracovavane->peek()->getJednotkovaCena(), spracovavane->peek()->getID()));

									spracovavane->peek()->setMnozstvo(vozidla->operator[](j)->getAktualnuVolnuKapacitu());
									
									j--;
								}
							}
						}
					}
				}
			}
		}
		if (spracovavane->size() <= i)
		{
			i = -1;
		}
	}

	for (int i = 0; i < vozidla->size(); i++)
	{
		cout << "prvy region auta " << vozidla->operator[](i)->getSpz() << " je " << vozidla->operator[](i)->getPrvyRegion() << "\n";
	}

	for (int i = 0; i < vozidla->size(); i++)
	{
		if (vozidla->operator[](i)->isNasklade())
		{
			for (int j = 0; j < objednavky->size(); j++)
			{
				if (objednavky->operator[](j)->getDatumDorucenia() == dnesnyDatum+i && 
					vozidla->operator[](i)->getAktualnuVolnuKapacitu() > objednavky->operator[](j)->getMnozstvo() &&
					vozidla->operator[](i)->getTypVozidla() == objednavky->operator[](j)->getTypTovaru() &&
					vozidla->operator[](i)->getPrvyRegion() == objednavky->operator[](j)->getZakaznik()->getCisloRegionu())
				{
					double mnozstvo;
					mnozstvo = objednavky->operator[](j)->getMnozstvo();
					vozidla->operator[](i)->upravKapacitu(mnozstvo);
					aktualneNaCeste->add(objednavky->operator[](j));
					vozidla->operator[](i)->pridajRegion(objednavky->operator[](j)->getZakaznik()->getCisloRegionu());
					objednavky->removeAt(j);
					vozidla->operator[](i)->vysliNaCestu();
				}
			}
		}
	}

	for (int i = 0; i < aktualneNaCeste->size(); i++)
	{
		cout << aktualneNaCeste->operator[](i)->getZakaznik()->getObchodnyNazov() << "  " << aktualneNaCeste->operator[](i)->getMnozstvo() << "\n";
	}

	for (int i = 0; i < vozidla->size(); i++)
	{
		if (vozidla->operator[](i)->isNasklade() && vozidla->operator[](i)->getAktualnuVolnuKapacitu() != vozidla->operator[](i)->getKapacita())
		{
			vozidla->operator[](i)->vysliNaCestu();
		}
	}
}

void Chips_and_Crisps::zrusObjednavkuSNajnizsovTrzbov()
{
	double mintrzba = 9999999;

	for (int i = 0; i < objednavky->size(); i++)
	{
		if (!objednavky->operator[](i)->isZrusena())
		{
			double trzba = objednavky->operator[](i)->getJednotkovaCena()*objednavky->operator[](i)->getMnozstvo();
			if (trzba < mintrzba)
			{
				mintrzba = trzba;
			}
		}
	}
	for (int i = 0; i < objednavky->size(); i++)
	{
		if (!objednavky->operator[](i)->isZrusena())
		{
			if (objednavky->operator[](i)->getJednotkovaCena()*objednavky->operator[](i)->getMnozstvo() == mintrzba)
			{
				objednavky->operator[](i)->zrusenieObjednavky();
				zrusene->add(objednavky->operator[](i));
				objednavky->removeAt(i);
				break;
			}
		}
	}
}

void Chips_and_Crisps::vylozVozidla()
{
	for (int i = 0; i < vozidla->size(); ++i)
	{
		if (!vozidla->operator[](i)->isNasklade())
		{
			vozidla->operator[](i)->resetKapacity();
			vozidla->operator[](i)->vratDoGaraze();
			vozidla->operator[](i)->pocetPrejdenychRegionov();
			vozidla->operator[](i)->setCelkoveNaklady(vozidla->operator[](i)->pocetPrejdenychRegionov());
		}
	}
	
	for (int i = 0; i < aktualneNaCeste->size(); ++i)
	{
		for (int j = 0; j < aktualneNaCeste->size(); ++j)
		{
			if (i != j && aktualneNaCeste->operator[](i)->getID() == aktualneNaCeste->operator[](j)->getID())
			{
				if (aktualneNaCeste->operator[](i)->getMnozstvo() !=0 && aktualneNaCeste->operator[](j)->getMnozstvo() !=0)
				{
					int mnozstvo = aktualneNaCeste->operator[](j)->getMnozstvo();
					aktualneNaCeste->operator[](i)->pridajMnozstvo(mnozstvo);
					aktualneNaCeste->operator[](j)->resetujMnozstvo();
					delete aktualneNaCeste->removeAt(j);
					j--;
				}
				
			}
		}
	}
	
	for (int i = 0; i < aktualneNaCeste->size(); i++)
	{
		if (aktualneNaCeste->operator[](i)->getMnozstvo() != 0)
		{
			zrealizovane->add(aktualneNaCeste->operator[](i));
		}
		
	}
}

void Chips_and_Crisps::vypisObjednavokOdDatumu()
{
	int od;
	int po;
	cout << "Zadaj datum od ktoreho chces vypisat zrealizovane objednavky: \n";
	cin >> od;
	cout << "Zadaj datum po ktory chces vypisat zrealizovane objednavky: \n";
	cin >> po;
	cout << "Datum\t Zakaznik\t Typ produktu\t Mnozstvo\t Celkove trzby\n";
	for (int i = 0; i < zrealizovane->size(); ++i)
	{
		if (zrealizovane->operator[](i)->getDatumDorucenia() >= od && zrealizovane->operator[](i)->getDatumDorucenia() <= po)
		{

			if (zrealizovane->operator[](i)->getTypTovaru() == 1)
			{
				double trzba = zrealizovane->operator[](i)->getJednotkovaCena()*zrealizovane->operator[](i)->getMnozstvo();

				cout << zrealizovane->operator[](i)->getDatumDorucenia() << "\t" << zrealizovane->operator[](i)->getZakaznik()->getObchodnyNazov() << 
					"\t\t" << "Hranolceky\t " << zrealizovane->operator[](i)->getMnozstvo() << "\t\t" <<  trzba << "\n";
			}
			else
			{
				double trzba = zrealizovane->operator[](i)->getJednotkovaCena()*zrealizovane->operator[](i)->getMnozstvo();

				cout << zrealizovane->operator[](i)->getDatumDorucenia() << "\t" << zrealizovane->operator[](i)->getZakaznik()->getObchodnyNazov() <<
					"\t\t" << "Lupienky\t " << zrealizovane->operator[](i)->getMnozstvo() << "\t\t" << trzba << "\n";
			}
		}
	}
}

void Chips_and_Crisps::vypisNezrealizovanychObjednavok()
{
	int od;
	int po;
	cout << "Zadaj datum od ktoreho chces vypisat nezrealizovane objednavky: \n";
	cin >> od;
	cout << "Zadaj datum po ktory chces vypisat nezrealizovane objednavky: \n";
	cin >> po;
	cout << "ZRUSENE\n";
	cout << "Datum\t Zakaznik\t Typ produktu\t Mnozstvo\t Celkove trzby\n";
	for (int i = 0; i < zrusene->size(); ++i)
	{
		if (zrusene->operator[](i)->getDatumEvidencie() >= od && zrusene->operator[](i)->getDatumEvidencie() <= po)
		{

			if (zrusene->operator[](i)->getTypTovaru() == 1)
			{
				double trzba = zrusene->operator[](i)->getJednotkovaCena()*zrusene->operator[](i)->getMnozstvo();

				cout << zrusene->operator[](i)->getDatumEvidencie() << "\t" << zrusene->operator[](i)->getZakaznik()->getObchodnyNazov() <<
					"\t\t" << "Hranolceky\t " << zrusene->operator[](i)->getMnozstvo() << "\t\t" << trzba << "\n";
			}
			else
			{
				double trzba = zrusene->operator[](i)->getJednotkovaCena()*zrusene->operator[](i)->getMnozstvo();

				cout << zrusene->operator[](i)->getDatumEvidencie() << "\t" << zrusene->operator[](i)->getZakaznik()->getObchodnyNazov() <<
					"\t\t" << "Lupienky\t " << zrusene->operator[](i)->getMnozstvo() << "\t\t" << trzba << "\n";
			}
		}
	}

	cout << "ZAMIETNUTE\n";

	for (int i = 0; i < zamietnute->size(); ++i)
	{
		if (zamietnute->operator[](i)->getDatumEvidencie() >= od && zamietnute->operator[](i)->getDatumEvidencie() <= po)
		{

			if (zamietnute->operator[](i)->getTypTovaru() == 1)
			{
				double trzba = zamietnute->operator[](i)->getJednotkovaCena()*zamietnute->operator[](i)->getMnozstvo();

				cout << zamietnute->operator[](i)->getDatumEvidencie() << "\t" << zamietnute->operator[](i)->getZakaznik()->getObchodnyNazov() <<
					"\t\t" << "Hranolceky\t " << zamietnute->operator[](i)->getMnozstvo() << "\t\t" << trzba << "\n";
			}
			else
			{
				double trzba = zamietnute->operator[](i)->getJednotkovaCena()*zamietnute->operator[](i)->getMnozstvo();

				cout << zamietnute->operator[](i)->getDatumEvidencie() << "\t" << zamietnute->operator[](i)->getZakaznik()->getObchodnyNazov() <<
					"\t\t" << "Lupienky\t " << zamietnute->operator[](i)->getMnozstvo() << "\t\t" << trzba << "\n";
			}
		}
	}
}

void Chips_and_Crisps::vyhladanieBiofarmara()
{
	int TypPolotovaru = 0;
	
	cout << "Zadaj datum typ polotovaru: \n 1.Zemiaky\n2.Olej\n3.Ochucovadla\n";
	cin >> TypPolotovaru;
	if (TypPolotovaru > 3)
	{
		cout << "Mas moznost od 1 po 3... \n";
	}
	else
	{
		int max = biofarmari->operator[](0)->pocetPredanychPolotovarov(TypPolotovaru, dnesnyDatum);
		int pozicia = 0;
		for (int i = 0; i < biofarmari->size(); ++i)
		{
			if (biofarmari->operator[](i)->pocetPredanychPolotovarov(TypPolotovaru, dnesnyDatum) > max)
			{
				max = biofarmari->operator[](i)->pocetPredanychPolotovarov(TypPolotovaru, dnesnyDatum);
				pozicia = i;
			}
		}

		cout << "Nazov Biofarmara\t Celkove mnozstvo\t celkova cena\t priemerna jednotkova cena\n";
		cout << biofarmari->operator[](pozicia)->getObchodnyNazov() << "\t\t\t\t"
		<< biofarmari->operator[](pozicia)->pocetPredanychPolotovarov(TypPolotovaru, dnesnyDatum) << "\t\t\t" <<
		biofarmari->operator[](pozicia)->pocetPredanychPolotovarov(TypPolotovaru, dnesnyDatum)*biofarmari->operator[](pozicia)->priemernaCena(TypPolotovaru, dnesnyDatum)
		<< "\t\t\t" << biofarmari->operator[](pozicia)->priemernaCena(TypPolotovaru, dnesnyDatum) << "\n\n";
	}
}

void Chips_and_Crisps::celkovyZisk()
{
	int den;
	cout << "Zadaj od ktoreho chces zisk za posledny mesiac: \n";
	cin >> den;
	double pom = 0;

	for (int i = 0; i < biofarmari->size(); ++i)
	{
		pom += biofarmari->operator[](i)->pocetPredanychPolotovarov(1, den)*biofarmari->operator[](i)->priemernaCena(1, den);
		pom += biofarmari->operator[](i)->pocetPredanychPolotovarov(2, den)*biofarmari->operator[](i)->priemernaCena(2, den);
		pom += biofarmari->operator[](i)->pocetPredanychPolotovarov(3, den)*biofarmari->operator[](i)->priemernaCena(3, den);
	}

	int udrzba = 0;

	for (int i = 0; i < vozidla->size(); ++i)
	{
		udrzba += vozidla->operator[](i)->getCelkoveNaklady();
	}

	int plus = 0;

	for (int i = 0; i < zrealizovane->size(); ++i)
	{
		if (zrealizovane->operator[](i)->getDatumDorucenia() <= den && zrealizovane->operator[](i)->getDatumDorucenia() >= den -30)
		{
			plus += zrealizovane->operator[](i)->getJednotkovaCena()*zrealizovane->operator[](i)->getMnozstvo();
		}
	}

	plus -= udrzba + pom;
	cout << "Celkovy zisk je: " << plus << "\n";
}

void Chips_and_Crisps::zapisBiofarmarov()
{
	zapis.open("biofarmari.txt");
	for (int i = 0; i < biofarmari->size(); ++i)
	{
		zapis << biofarmari->operator[](i)->getObchodnyNazov();
		zapis << " ";
		zapis << biofarmari->operator[](i)->velkostPola();
		zapis << " ";
		for (int k = 0; k < biofarmari->operator[](i)->velkostPola(); ++k)
		{
			zapis << biofarmari->operator[](i)->getPrvokPolaNaPozicii(k);
			if (k + 1 != biofarmari->operator[](i)->velkostPola())
			{
				zapis << " ";
			}
		}
	}
	zapis.close();
}

void Chips_and_Crisps::nacitajBiofarmarov()
{
	string nazov;
	int pocetOpakovani = 0;
	int velkost, prvokNapozicii;
	ifstream nacitaj("biofarmari.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> nazov >> velkost;
		
		biofarmari->add(new Biofarmar(nazov, velkost));
		for (int i = 0; i < velkost; ++i)
		{
			nacitaj >> prvokNapozicii;
			for (int k = 0; k < biofarmari->size(); ++k)
			{
				if (biofarmari->operator[](k)->getObchodnyNazov() == nazov)
				{
					biofarmari->operator[](k)->setPolotovar(prvokNapozicii, i);
				}
			}
		}
		pocetOpakovani++;
	}
	nacitaj.close();
}

void Chips_and_Crisps::zapisVozidla()
{
	zapis.open("vozidla.txt");
	for (int i = 0; i < vozidla->size(); ++i)
	{
		zapis << vozidla->operator[](i)->getTypVozidla();
		zapis << " ";
		zapis << vozidla->operator[](i)->getSpz();
		zapis << " ";
		zapis << vozidla->operator[](i)->getDatumEvidencie();
		zapis << " ";
		zapis << vozidla->operator[](i)->getCelkoveNaklady();
		if (i + 1 != vozidla->size())
		{
			zapis << " ";
		}
	}
	zapis.close();
}

void Chips_and_Crisps::nacitajVozidla()
{
	string spz;
	int typ, datumE, cN;
	Typ_Tov typ_vozidla;
	ifstream nacitaj("vozidla.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> typ >> spz >> datumE;
		if (typ == 1)
		{
			typ_vozidla = Hranolceky;
		}
		else if (typ == 2)
		{
			typ_vozidla = Lupienky;
		}

		vozidla->add(new Vozidlo(typ_vozidla, spz, datumE));
		nacitaj >> cN;

		for (int i = 0; i < vozidla->size(); ++i)
		{
			if (vozidla->operator[](i)->getSpz() == spz)
			{
				vozidla->operator[](i)->nastavCN(cN);
				break;
			}
		}
	}
	nacitaj.close();
}

void Chips_and_Crisps::zapisZakaznikov()
{
	zapis.open("zakaznici.txt");
	for (int i = 0; i < zakaznici->size(); ++i)
	{
		zapis << zakaznici->operator[](i)->getObchodnyNazov();
		zapis << " ";
		zapis << zakaznici->operator[](i)->getCisloRegionu();
		if (i + 1 != zakaznici->size())
		{
			zapis << " ";
		}
	}
	zapis.close();
}

void Chips_and_Crisps::nacitajZakaznikov()
{
	string nazov;
	int region;
	ifstream nacitaj("zakaznici.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> nazov >> region;
		zakaznici->add(new Zakaznik(nazov, region));
	}
	nacitaj.close();
}

void Chips_and_Crisps::zapisObjednavky()
{
	zapis.open("objednavky.txt");
	for (int i = 0; i < objednavky->size(); ++i)
	{
		zapis << objednavky->operator[](i)->getDatumEvidencie();
		zapis << " ";
		zapis << objednavky->operator[](i)->getZakaznik()->getObchodnyNazov();
		zapis << " ";
		zapis << objednavky->operator[](i)->getTypTovaru();
		zapis << " ";
		zapis << objednavky->operator[](i)->getMnozstvo();
		zapis << " ";
		zapis << objednavky->operator[](i)->getDatumDorucenia();
		zapis << " ";
		zapis << objednavky->operator[](i)->getJednotkovaCena();
		zapis << " ";
		zapis << objednavky->operator[](i)->getID();
		if (i + 1 != objednavky->size())
		{
			zapis << " ";
		}
	}
	zapis.close();
}

void Chips_and_Crisps::nacitanieObjednavky()
{
	Typ_Tov typT;
	string nazov;
	int DE, typ, mnozstvo ,DD, JC, ID;
	ifstream nacitaj("objednavky.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> DE >> nazov >>typ >> mnozstvo >> DD >> JC >> ID;

		if (typ == 1)
		{
			typT = Hranolceky;
		}
		else if (typ == 2)
		{
			typT = Lupienky;
		}

		for (int i = 0; i < zakaznici->size(); ++i)
		{
			if (zakaznici->operator[](i)->getObchodnyNazov() == nazov)
			{
				objednavky->add(new Objednavka(DE, zakaznici->operator[](i), typT, mnozstvo, DD, JC, ID));
			}
		}
	}
	nacitaj.close();
}

void Chips_and_Crisps::zapisZamietnute()
{
	zapis.open("zamietnute.txt");
	for (int i = 0; i < zamietnute->size(); ++i)
	{
		zapis << zamietnute->operator[](i)->getDatumEvidencie();
		zapis << " ";
		zapis << zamietnute->operator[](i)->getZakaznik()->getObchodnyNazov();
		zapis << " ";
		zapis << zamietnute->operator[](i)->getTypTovaru();
		zapis << " ";
		zapis << zamietnute->operator[](i)->getMnozstvo();
		zapis << " ";
		zapis << zamietnute->operator[](i)->getDatumDorucenia();
		zapis << " ";
		zapis << zamietnute->operator[](i)->getJednotkovaCena();
		zapis << " ";
		zapis << zamietnute->operator[](i)->getID();
		if (i + 1 != zamietnute->size())
		{
			zapis << " ";
		}
	}
	zapis.close();

}

void Chips_and_Crisps::nacitanieZamietnutych()
{
	Typ_Tov typT;
	string nazov;
	int DE, typ, mnozstvo, DD, JC, ID;
	ifstream nacitaj("zamietnute.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> DE >> nazov >> typ >> mnozstvo >> DD >> JC >> ID;

		if (typ == 1)
		{
			typT = Hranolceky;
		}
		else if (typ == 2)
		{
			typT = Lupienky;
		}

		for (int i = 0; i < zakaznici->size(); ++i)
		{
			if (zakaznici->operator[](i)->getObchodnyNazov() == nazov)
			{
				zamietnute->add(new Objednavka(DE, zakaznici->operator[](i), typT, mnozstvo, DD, JC, ID));
			}
		}
	}
	nacitaj.close();
}

void Chips_and_Crisps::zapisZrealizovane()
{
	zapis.open("zrealizovane.txt");
	for (int i = 0; i < zrealizovane->size(); ++i)
	{
		zapis << zrealizovane->operator[](i)->getDatumEvidencie();
		zapis << " ";
		zapis << zrealizovane->operator[](i)->getZakaznik()->getObchodnyNazov();
		zapis << " ";
		zapis << zrealizovane->operator[](i)->getTypTovaru();
		zapis << " ";
		zapis << zrealizovane->operator[](i)->getMnozstvo();
		zapis << " ";
		zapis << zrealizovane->operator[](i)->getDatumDorucenia();
		zapis << " ";
		zapis << zrealizovane->operator[](i)->getJednotkovaCena();
		zapis << " ";
		zapis << zrealizovane->operator[](i)->getID();
		zapis << " ";
	}
	zapis.close();
}

void Chips_and_Crisps::nacitanieZrealizovanych()
{
	Typ_Tov typT;
	string nazov;
	int DE, typ, mnozstvo, DD, JC, ID;
	ifstream nacitaj("zrealizovane.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> DE >> nazov >> typ >> mnozstvo >> DD >> JC >> ID;

		if (typ == 1)
		{
			typT = Hranolceky;
		}
		else if (typ == 2)
		{
			typT = Lupienky;
		}

		for (int i = 0; i < zakaznici->size(); ++i)
		{
			if (zakaznici->operator[](i)->getObchodnyNazov() == nazov)
			{
				zrealizovane->add(new Objednavka(DE, zakaznici->operator[](i), typT, mnozstvo, DD, JC, ID));
			}
		}
	}
	nacitaj.close();
	nacitavalSom = true;
}


void Chips_and_Crisps::zapisZrusene()
{
	zapis.open("zrusene.txt");
	for (int i = 0; i < zrusene->size(); ++i)
	{
		zapis << zrusene->operator[](i)->getDatumEvidencie();
		zapis << " ";
		zapis << zrusene->operator[](i)->getZakaznik()->getObchodnyNazov();
		zapis << " ";
		zapis << zrusene->operator[](i)->getTypTovaru();
		zapis << " ";
		zapis << zrusene->operator[](i)->getMnozstvo();
		zapis << " ";
		zapis << zrusene->operator[](i)->getDatumDorucenia();
		zapis << " ";
		zapis << zrusene->operator[](i)->getJednotkovaCena();
		zapis << " ";
		zapis << zrusene->operator[](i)->getID();
		zapis << " ";
	}
	zapis.close();
}

void Chips_and_Crisps::nacitanieZrusene()
{
	Typ_Tov typT;
	string nazov;
	int DE, typ, mnozstvo, DD, JC, ID;
	ifstream nacitaj("zrusene.txt");
	while (!nacitaj.eof())
	{
		nacitaj >> DE >> nazov >> typ >> mnozstvo >> DD >> JC >> ID;

		if (typ == 1)
		{
			typT = Hranolceky;
		}
		else if (typ == 2)
		{
			typT = Lupienky;
		}

		for (int i = 0; i < zakaznici->size(); ++i)
		{
			if (zakaznici->operator[](i)->getObchodnyNazov() == nazov)
			{
				zrusene->add(new Objednavka(DE, zakaznici->operator[](i), typT, mnozstvo, DD, JC, ID));
			}
		}
	}
	nacitaj.close();
}

void Chips_and_Crisps::zapisObjednavokBiofarmara()
{
	for (int i = 0; i < biofarmari->size(); ++i)
	{
		string nazov = biofarmari->operator[](i)->getObchodnyNazov() + ".txt";
		biofarmari->operator[](i)->zapisObjednavok(nazov);
	}
}

void Chips_and_Crisps::nacitanieObjednavokBiofarmara()
{
	for (int i = 0; i < biofarmari->size(); ++i)
	{
		string nazov = biofarmari->operator[](i)->getObchodnyNazov() + ".txt";

		biofarmari->operator[](i)->nacitanieObjednavok(nazov);
	}
}
