#pragma once
#include "service.h"


/*Functie care returneaza numarul de produse de tipul tip
  input: tip - un tip de produs
  output: returneaza produsele de tipul tip
 */
int Service::nrTip(const string tip)
{
	int nr = 0;
	for (auto& p : getAll())
	{
		if (p.getTip() == tip)
			nr++;
	}
	return nr;
}

/*Functie care returneaza un vector cu produse sortate alfabetic
  input: -
  output: un vector cu produse sortate alfabetic
 */
const vector<Produs> Service::sorteaza()
{
	vector<Produs> produse = getAll();
	sort(produse.begin(), produse.end(), [](const Produs& p1, const Produs& p2) {
		return p1.getNume() < p2.getNume();
		});
	return produse;
}

/*Functie care valideaza un produs, iar daca acesta este valid, il adauga in lista de produse
input : p - un produs
output: produsul p este adaugat in lista de produse
*/
void Service::adauga(const Produs& p)
{
	if (val.valideaza(p) == true)
	{
		rep.adauga(p);
	}
}

/*Functie care returneaza un vector cu toate tipurile
  input: -
  output: un vector care contine toate tipurile unice  
*/
const vector<string> Service::toateTipurile()
{
	vector<string> tipuri;
	for (auto& p : getAll())
	{
		if (tipNou(tipuri, p.getTip()))
		{
			tipuri.push_back(p.getTip());
		}
	}
	return tipuri;
}

/*Functie care verifica daca tipul tip se afla deja in vectorul de tipuri tipuri
  input: tipuri - un vector care contine tipuri de produse
  output: false - daca tipul tip se afla deja in lista de tipuri
		  true - in caz contrar
*/
bool Service::tipNou(const vector<string> tipuri, string tip)
{
	for (auto& t : tipuri)
	{
		if (t == tip)
		{
			return false;
		}
	}
	return true;
}

void testService()
{
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };
	Produs p{ 1, "nume", "tip", 10.0 };
	testService.adauga(p);
	assert(testService.getAll().size() == 1);
	Produs p2{ 2, "", "", -10.2 };
	testService.adauga(p2);
	assert(testService.getAll().size() == 1);
	assert(testService.nrTip("tip") == 1);
	Produs p3{ 3, "nume2", "tip2", 10.0 };
	testService.adauga(p3);
	assert(testService.toateTipurile().size() == 2);
	Produs p4{ 4, "anume2", "tip2", 10.0 };
	testService.adauga(p4);
	testService.sorteaza();
	assert(testService.getAll().size() == 3);
	assert(testService.getAll()[0].getId() == 4);

	vector<string> tipuri = { "t1", "t2" , "t3"};
	assert(testService.tipNou(tipuri, "t1") == false);
	assert(testService.tipNou(tipuri, "t4") == true);

}