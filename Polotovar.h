#pragma once

#include "../sem/Typ_Polotovaru.h"
#include <iostream>

using namespace std;
	class Polotovar
	{
	public:
		Polotovar(Typ_Polotovaru typ, double cena_polotovaru, int mnozstvo);
		~Polotovar();
		Typ_Polotovaru getTypPolotovaru();
		void setTypPolotovaru(int typ);
		double getCenaPolotovaru();
		int getMnozstvoPolotovaru();
		void setMnozstvoPolotovaru(int mnozstvo);
		void setCenaPolotovaru(double cena);
		double getPriemernaCena();
		void vygenerujMnozstvo(int polotovar);
		int vygenerujCenu(int polotovar);
		
		

	private:
		Typ_Polotovaru typPolotovaru;
		int cenaPolotovaru;
		int mnozstvoPolotovaru;
		double priemernaCena = 0;
	};
	


