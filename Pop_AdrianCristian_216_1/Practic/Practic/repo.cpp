#pragma once
#include "repo.h"

/*Verifica daca produsul cu id-ul id exista in lista de produse
input: id - numar intreg care reprezinta id-ul unui produs
output: true - daca exista un produs cu id-ul id in lista
		false - in caz contrar
*/
bool Repo::exista(int id) const
{
	for (auto& p : produse)
	{
		if (p.getId() == id)
		{
			return true;
		}
	}
	return false;
}

/*
Functie care adauga produsul p in lista de produse 
input: p - un produs
output: produsul p este adaugat in lista de produse
*/
void Repo::adauga(const Produs& p)
{
	if (exista(p.getId()))
	{
		QMessageBox msg;
		msg.setText("Exista deja un produs cu id " + QString::number(p.getId()));
		msg.exec();
	}
	else
	{
		produse.push_back(p);
	}
}

//Functie care incarca produse dintr-un fisier
void FileRepo::loadFromFile()
{
	std::ifstream in(fileName);
	if(!in.is_open())
	{
		QMessageBox msg;
		msg.setText("Unable to open file");
		msg.exec();
	}
	while (!in.eof())
	{
		int id;
		string nume;
		string tip;
		double pret;
		in >> id >> nume >> tip >> pret;
		if (in.eof())
		{
			break;
		}
		Produs p{ id, nume, tip ,pret };
		Repo::adauga(p);
	}
	in.close();
}

//Functie care scrie produsele din memorie in fisier
void FileRepo::writeToFile()
{
	std::ofstream out(fileName);
	for (auto& p : getAll())
	{
		out << p.getId() << ' ';
		out << p.getNume() << ' ';
		out << p.getTip() << ' ';
		out << p.getPret() << ' ' << std::endl;
	}
	out.close();
}

void testRepo()
{
	Repo testRepo;
	assert(testRepo.getAll().size() == 0);
	Produs p{ 1, "testNume", "testTip", 10.2 };
	assert(p.getId() == 1);
	assert(p.getNume() == "testNume");
	assert(p.getTip() == "testTip");
	assert(p.getPret() == 10.2);
	testRepo.adauga(p);
	assert(testRepo.getAll().size() == 1);
	testRepo.adauga(p);
	assert(testRepo.getAll().size() == 1);
	FileRepo testFileRepo("test.txt");
	try {
		testFileRepo.getAll();
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}
	
}