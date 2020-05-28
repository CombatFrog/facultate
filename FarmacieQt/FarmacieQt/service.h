#pragma once

#include "medicament.h"
#include "repo.h"
#include "validator.h"
#include "undoActions.h"

#include <string>
#include <vector>
#include <numeric>

using std::vector;
using std::unique_ptr;

class Service {
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	Repo& rep;
	Validator& val;
public:
	Service(Repo& rep, Validator& val) noexcept :rep{ rep }, val{ val }{};

	/*
	nu permite copierea de obiecte
	*/
	Service(const Service& ot) = delete;

	const Medicament& cautaMedicament(string denumire) {
		return rep.cauta(denumire);
	}

	/*
	returneaza toate medicamentele din lista
	*/
	const vector<Medicament> getAll() noexcept {
		return rep.getAll();
	}

	const vector<Medicament> getReteta() noexcept {
		return rep.getReteta();
	}

	/*
	adauga un medicament in lista
	*/
	void adaugaMedicament(const string& denumire, int pret, const string& producator, const string& substanta);

	/*
	sterge un medicament din lista
	*/
	void stergeMedicament(const string& denumire);

	/*
	modifica un medicament din lista
	*/
	void modificaMedicament(const string& denumire, int pretNou, const string& producatorNou, const string& substantaNoua);

	/*
	filtreaza lista dupa pret
	*/
	const vector<Medicament> filtreazaPret(int pret);

	/*
	fitreaza lista dupa substanta activa
	*/
	const vector<Medicament> filtreazaSubstanta(const string& substanta);

	/*
	Functie care sorteaza o lista alfabetic dupa denumire
	*/
	const vector<Medicament> sorteazaDenumire();

	/*
	Functie care sorteaza o lista alfabetic dupa producator
	*/
	const vector<Medicament> sorteazaProducator();

	/*
	Functie care sorteaza o lista alfabetic dupa substanta activa.
	Medicamentele care au aceeasi substanta activa sunt sortate crescator dupa pret
	*/
	const vector<Medicament> sorteazaSubstantaPret();

	void adaugaReteta(const string& denumire);

	int dimensiuneReteta() noexcept {
		return rep.dimensiuneRetata();
	}

	int suma() {
		vector<Medicament> v = rep.getReteta();
		int suma = std::accumulate(v.begin(), v.end(), 0, [](int i, const Medicament& m) { return m.getPret() + i; });
		return suma;
	}

	void golesteReteta() noexcept;

	void genereazaReteta(int numar);

	void undo();

};

void testServiceSuma();
void testServiceAdauga();
void testServiceSterge();
void testServiceModifica();
void testServiceFiltru();
void testServiceSortare();
void testServiceReteta();
void testUndo();