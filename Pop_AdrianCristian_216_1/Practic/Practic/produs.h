#pragma once
#include <string>
#include <assert.h>

using std::string;

class Produs {
	int id;
	string nume;
	string tip;
	double pret;
public:
	Produs(int id, const string nume, const string tip, double pret) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret }{}

	//returneaza id-ul produsului
	int getId() const noexcept
	{
		return id;
	}

	//returneaza numele produsului
	string getNume() const
	{
		return nume;
	}

	//returneaza tipul produsului
	string getTip() const
	{
		return tip;
	}

	//returneaza pretul produsului
	double getPret() const
	{
		return pret;
	}
};


