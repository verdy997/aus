#pragma once
#include "Biofarmar.h"
#include "Vozidlo.h"
#include "Zakaznik.h"
#include "Objednavka.h"
#include "../sem/structures/list/linked_list.h"
#include "../sem/structures/priority_queue/priority_queue_linked_list.h"
#include <iostream>
#include <fstream>

using namespace  std;
using namespace  structures;

class Chips_and_Crisps
{

private:
	LinkedList<Biofarmar*> *biofarmari;
	LinkedList<Vozidlo*> *vozidla;
	LinkedList<Zakaznik*> *zakaznici;
	LinkedList<Objednavka*> *objednavky;
	LinkedList<Objednavka*> *zamietnute;
	LinkedList<Objednavka*> *zrealizovane;
	LinkedList<Objednavka*> *zrusene;
	LinkedList<Objednavka*>	*aktualneNaCeste;
	PriorityQueueLinkedList<Objednavka*> *spracovavane;
	ofstream zapis;
	
	int dnesnyDatum = 1;
	int celkovaKapacitaVozidielPreDen;
	int celkovaKapacita;
	int mnozstvoZemiakovNaSklade = 0;
	int mnozstvoOlejaNaSklade = 0;
	int mnozstvoOchucovadielNaSklade = 0;
	double financieFirmy = 10000;
	void zapisBiofarmarov();
	void zapisVozidla();
	void zapisZakaznikov();
	void zapisObjednavky();
	void zapisZamietnute();
	void zapisZrealizovane();
	void zapisZrusene();
	void zapisObjednavokBiofarmara();
	bool nacitavalSom = false;

public:
	Chips_and_Crisps();
	~Chips_and_Crisps();
	void pridajBiofarmara(string nazov, int pocetPolotovarov);
	void pridajVozidlo();
	void nacitajZakaznikov();
	void nacitajVozidla();
	void nacitanieZrealizovanych();
	void nacitanieZamietnutych();
	void vypisVozidiel();
	void pridajZakaznika();
	void vypisZakaznikov();
	void novaObjednavka();
	bool kontrolaNazvuBiofarmara(string nazov);
	bool kontrolaZakaznika(string nazov);
	bool kontrolaSPZ(string spz);
	bool kontrolaObjednavok;
	void setDatum(int datum);
	int getDnesnyDatum();
	void posunDen();
	int getCelkovaKapacitaVozidielPreDen(int den, int typ);
	int KapacitaVozidiel(Typ_Tov tp);
	bool KontrolaKapacity(int den, int typ, int mnozstvo);
	void kontrolaNasledujucich7dni(int den);
	double getFinancieFirmy();
	void vypisBiofarmarov();
	void kontrolaNasledujucehoDna(int den);
	double vseobecnaKontrolaTovaru(int zacDatum, double konstanta, int kolkoDni, int typ);
	void naplnVozidlo();
	void zrusObjednavkuSNajnizsovTrzbov();
	void vylozVozidla();
	void vypisObjednavokOdDatumu();
	void vypisNezrealizovanychObjednavok();
	void vyhladanieBiofarmara();
	void celkovyZisk();
	void nacitajBiofarmarov();
	void nacitanieObjednavky();
	void nacitanieZrusene();
	void nacitanieObjednavokBiofarmara();
	

};

