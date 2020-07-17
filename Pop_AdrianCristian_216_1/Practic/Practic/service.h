#pragma once
#include "produs.h"
#include "repo.h"
#include "validator.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Service {
private:
	Repo& rep;
	Validator& val;
public:
	Service(Repo& r, Validator& v) :rep{ r }, val{ v }{}

	Service(const Service& ot) = delete;

	//Returneaa un vector cu toate produsele
	const vector<Produs> getAll()
	{
		return rep.getAll();
	}

	//Returneaza numarul de produse de un anumit tip
	int nrTip(const string tip);

	//Sorteaza produsele alfabetic dupa nume
	const vector<Produs> sorteaza();

	//Adauga un produs in lista de produse
	void adauga(const Produs& p);

	//Returneaza un vector cu toate produsele
	const vector<string> toateTipurile();

	//Verifica daca un tip exista deja intr-o lista de tipuri
	bool tipNou(const vector<string> tipuri, string tip);
};

void testService();