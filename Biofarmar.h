#pragma once

#include <string>
#include "../sem/structures/array/array.h"
#include "../sem/Polotovar.h"
#include "structures/list/linked_list.h"
#include "Objednavka.h"
#include <fstream>

using namespace std;
using namespace structures;

	class Biofarmar
	{

	private:
		string obchodnyNazov;
		Array<Polotovar*> *polotovary;
		string preklad(int poradie);
		LinkedList<Objednavka*> *objednavkyCac;
		ofstream zapis;


	public:
		Biofarmar(string nazov, int pocetPolotovarov);
		~Biofarmar();
		string getObchodnyNazov();
		string getPolotovarNaIndexe(int index);
		void pridajPolotovar(int pocet);
		void toString(int datum);
		bool kontrolaTovaru(int kont, int pom);
		int prijmiObjednavku(int polotovar, int mnozstvo, int datum);
		int dajJednotkovuCenu(int polotovar);
		double priemernaCena(int polotovar, int datum);
		int pocetPredanychPolotovarov(int polotovar, int datum);
		bool ponukaPolotovar(int polotovar);
		int velkostPola();
		int getPrvokPolaNaPozicii(int pozicia);
		void zapisObjednavok(string nazov);
		void nacitanieObjednavok(string nazov);
		void setPolotovar(int typ, int pozicia);
	};
	




