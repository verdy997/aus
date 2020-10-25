
//#include "../sem/Biofarmar.h"
//#include "../sem/Polotovar.h"
#include "Chips_and_Crisps.h"

using namespace structures;

	int main()
	{
		initHeapMonitor();
		//int den;
		int pomCislo;
		string pomString;
		Chips_and_Crisps *CaC = new Chips_and_Crisps();
		bool isRunning = true;

		cout << "Zadaj datum (iba cele cislo od kedy sa program pouziva) :";
		cin >> pomCislo;
		CaC->setDatum(pomCislo);

		while (isRunning)
		{
			cout << "98. Zobraz dnesny den\n";
			cout << "99. Posun na dalsi den\n";
			cout << "0. Ukoncit\n";
			cout << "1. Pridanie noveho biofarmara\n";
			cout << "2. Vypis Biofarmarov\n";
			cout << "3. Pridanie noveho vozidla\n";
			cout << "4. Zoznam vozidiel\n"; 
			cout << "5. Pridaj noveho zakaznika\n";
			cout << "6. Pridaj objednavku\n";
			cout << "7. Kontrola nasledujucich 7 dni\n";
			cout << "8. Kontrola nasledujuceho dna\n";
			cout << "9. Naloz vozidla\n";
			cout << "10. Vyloz vozidla\n";
			cout << "11. Vypis zakaznikov regionu a statistiky objednavok\n";
			cout << "12. Vypis objednavok od datumu\n";
			cout << "13. Vypis neuspesnych objednavok od datumu\n";
			cout << "14. Vyhladanie najlepsieho dodavatela\n";
			cout << "15. Vypis celkovy zisk za obdobie\n";
			cout << "16. Nacitanie zrusenych objednavok\n";


			cin >> pomCislo;
			switch (pomCislo)
			{
				case 98:	
					cout << "Dnesny datum je: " << CaC->getDnesnyDatum() << "\n";
						break;
				case 99:
					CaC->posunDen();
					break;

				case 0:
					isRunning = false;
					break;

				case 1:
					cout << "Zadaj obchodny nazov Biofarmara:\n";
					cin >> pomString;
					if(CaC->kontrolaNazvuBiofarmara(pomString))
					{
						cout << "VYSKYTLA SA CHYBA!!!\n-Biofarmar s takymto nazvom uz existuje!\n";
						break;
					}
					else
					{
						cout << "Zadaj pocet polotovarov Biofarmara:\n";
						cin >> pomCislo;
						if (pomCislo <= 3)
						{
							CaC->pridajBiofarmara(pomString, pomCislo);
						}
						else
						{
							cout << "Nespravny pocet polotovarov!\n";
							break;
						}
					}
					break;

				case 2:
					CaC->vypisBiofarmarov();
					break;

				case 3:
					CaC->pridajVozidlo();
					break;
						
				case 4:
					CaC->vypisVozidiel();
					break;
				case 5:
					CaC->pridajZakaznika();
					break;

				case 6:
					CaC->novaObjednavka();
					break;

				case 7:
					CaC->kontrolaNasledujucich7dni(CaC->getDnesnyDatum());
					break;

				case 8:
					CaC->kontrolaNasledujucehoDna(CaC->getDnesnyDatum() + 1);
					break;
				case 9:
					CaC->naplnVozidlo();
					break;
				case 10:
					CaC->vylozVozidla();
					break;
				case 11:
					CaC->vypisZakaznikov();
					break;
				case 12:
					CaC->vypisObjednavokOdDatumu();
					break;
				case 13:
					CaC->vypisNezrealizovanychObjednavok();
					break;
				case 14:
					CaC->vyhladanieBiofarmara();
					break;
				case 15:
					CaC->celkovyZisk();
					break;
				case 16:
					CaC->nacitajBiofarmarov();
					CaC->nacitajVozidla();
					CaC->nacitajZakaznikov();
					CaC->nacitanieObjednavky();
					CaC->nacitanieZamietnutych();
					CaC->nacitanieZrealizovanych();
					CaC->nacitanieZrusene();
					CaC->nacitanieObjednavokBiofarmara();
					break;

				default:
					cout << "CHYBA!";
					break;
			}
			/*if(pomCislo == 0)
			{
				isRunning = false;
				break;
			}*/

		}
		delete CaC;
		return 0;
	}	



