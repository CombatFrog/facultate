#pragma once

#include "service.h"
class Console {
	Service& service;
public:
	Console(Service& service) noexcept :service{ service } {}

	/*
	Nu permite copierea de obiecte
	*/
	Console(const Service& ot) = delete;

	/*
	Porneste aplicatia
	*/
	void start();
private:
	/*
	Adauga un medicament in lista
	*/
	void adaugaUI();

	/*
	Afiseaza toate medicamentele din lista
	*/
	void afiseazaUI(const vector <Medicament>& medicamente);

	/*
	Sterge un medicament din lista
	*/
	void stergeUI();

	/*
	Modifica un medicament din lista
	*/
	void modificaUI();

	void adaugaRetetaUI();

	void golesteRetetaUI();

	void genereazaRetetaUI();

	void exportUI();
};
