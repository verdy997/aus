#pragma once
#include <iostream>

using namespace std;

class Zakaznik
{

private:
	string obchodnyNazov;
	int cisloRegionu;

public:
	Zakaznik(string nazov, int adresa);
	~Zakaznik();
	string getObchodnyNazov();
	int getCisloRegionu();


};

