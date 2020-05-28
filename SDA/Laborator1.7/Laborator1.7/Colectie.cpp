#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
	/* de adaugat */	
	capacitate = 5;
	dimensiuneElemente = 0;
	dimensiunePozitii = 0;
	elemente = new TElem[capacitate];
	pozitii = new int[capacitate];
}


void Colectie::adauga(TElem elem) {
	/* de adaugat */
	//Complexitate O(n)
	int pozitie;
	if (cauta(elem) == true) 
	{
		for (int i = 0; i < dimensiuneElemente; i++)
		{
			if (elemente[i] == elem)
			{
				pozitie = i;
				break;
			}
		}
		pozitii[dimensiunePozitii] = pozitie;
		dimensiunePozitii++;
	}
	else
	{
		elemente[dimensiuneElemente] = elem;
		pozitii[dimensiunePozitii] = dimensiuneElemente;
		dimensiuneElemente++;
		dimensiunePozitii++;
	}
	if (dimensiunePozitii >= capacitate || dimensiuneElemente >= capacitate)
		redim();
}

void Colectie::redim() {
	//Complexitate* O(n)
	TElem* eNou = new TElem[capacitate * 2];
	int* pNou = new int[capacitate * 2];

	for (int i = 0; i < dimensiuneElemente; i++)
		eNou[i] = elemente[i];

	for (int i = 0; i < dimensiunePozitii; i++)
		pNou[i] = pozitii[i];

	capacitate = capacitate * 2;
	delete[] elemente;
	delete[] pozitii;

	elemente = new TElem[capacitate];
	elemente = eNou;
	pozitii = new int[capacitate];
	pozitii = pNou;
}


bool Colectie::sterge(TElem elem) {
	/* de adaugat */
	//Complexitate O(n)
	if (cauta(elem) == true)
	{
		int pozitie;
		int aparitie;
		if (nrAparitii(elem) > 1)
		{
			for (int i = 0; i < dimensiuneElemente; i++)
			{
				if (elemente[i] == elem)
					pozitie = i;
			}
			for (int i = 0; i < dimensiunePozitii; i++)
			{
				if (pozitii[i] == pozitie)
				{
					aparitie = i;
				}
			}
			for (int i = aparitie; i < dimensiunePozitii - 1; i++)
				pozitii[i] = pozitii[i + 1];
			dimensiunePozitii--;
		}
		else
		{
			for (int i = 0; i < dimensiuneElemente; i++)
			{
				if (elemente[i] == elem)
				{
					pozitie = i;
					break;
				}
			}
			for (int i = pozitie; i < dimensiuneElemente - 1; i++)
			{
				elemente[i] = elemente[i + 1];
			}
			dimensiuneElemente--;

			for (int i = 0; i < dimensiunePozitii; i++)
			{
				if (pozitii[i] == pozitie)
				{
					aparitie = i;
					break;
				}	
			}

			for (int i = aparitie; i < dimensiunePozitii - 1; i++)
			{
				pozitii[i] = pozitii[i + 1];
				if (pozitii[i] > pozitie)
					pozitii[i]--;
			}
			dimensiunePozitii--;
		}
		return true;
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	//Complexitate O(n)
	for (int i = 0; i < dimensiuneElemente; i++)
		if (elemente[i] == elem)
			return true;
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	//Complexitate O(n)
	int pozitie;
	int aparitii = 0;
	if(cauta(elem) == false)
		return 0;
	else
	{
		for (int i = 0; i < dimensiuneElemente; i++)
		{
			if (elemente[i] == elem)
			{
				pozitie = i;
				break;
			}
		}
		for (int i = 0; i < dimensiunePozitii; i++)
		{
			if (pozitii[i] == pozitie)
			{
				aparitii++;
			}
		}
		return aparitii;
	}
}


int Colectie::dim() const {
	/* de adaugat */
	return dimensiunePozitii;
}


bool Colectie::vida() const {
	/* de adaugat */
	//Complexitate omega(1)
	if (dimensiuneElemente == 0)
		return true;
	return false;
}

IteratorColectie Colectie::iterator() const {
	//Complexitate omega(1)
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	delete[] elemente;
	delete[] pozitii;
	dimensiuneElemente = -1;
	dimensiunePozitii = -1;
	capacitate = -1;
}

