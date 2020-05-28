#include "repo.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <random>
#include <qmessagebox.h>

using std::ostream;
using std::stringstream;


/*
Functie care adauga un medicament
input: m - medicament
output: medicamentul m este adaugat la lista de medicamente
*/
void Repo::adauga(const Medicament& m) {
	if (exista(m)) {
		QMessageBox::critical(nullptr, "Error", "Exista deja un medicament cu aceasta denumire!");
		//throw RepoException("Exista deja un medicament cu denumirea: " + m.getDenumire() + "\n");
	}
	all.insert({ m.getDenumire(), m });
}

/*
Functie care sterge un medicament
input: denumire - denumirea medicamentului
output: medicamentul cu denumirea denumire este sters din lista de medicamente
raises: RepoException - daca nu exista medicament cu denumirea denumire
*/
void Repo::sterge(const string& denumire) {
	if (exista(cauta(denumire)))
		all.erase(denumire);
}


/*
Functie care modifica un medicament
input: denumire - denumirea medicamentului
	   m - noile valori ale medicamentului
outptu: medicamentul cu denumirea denumire primeste valorile medicamentului m
raises: RepoException - dace nu exista medicament cu denumirea demumire
*/
void Repo::modifica(const string& denumire, const Medicament& m) {
	map<string, Medicament>::iterator it = all.find(denumire);
	if (it != all.end())
	{
		it->second = m;
	}
}

/*
Functie care verifica dace un medicament exista in lista
input: m - un medicament
output: true - dace medicamentul m exista in lista
		false - in caz contrar
*/
bool Repo::exista(const Medicament& m) const {
	try {
		cauta(m.getDenumire());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}


/*
Functie care cauta un medicament in lista de medicamente
input: denumire - denumirea medicamentului
output: medicamentul cu denumirea denumire
reises: RepoException - dace nu exista medicament cu denumirea denumire
*/
const Medicament& Repo::cauta(string denumire) const {
	map<string, Medicament>::const_iterator it;
	it = all.find(denumire);
	if (it != all.end())
		return it->second;
	throw RepoException("Nu exista medicament cu denumirea: " + denumire + "\n");
}

void Repo::adaugaReteta(const string& denumire) {
	try {
		reteta.push_back(cauta(denumire));
	}
	catch (RepoException&) {
		throw RepoException("Nu exista medicament cu denumirea: " + denumire + "\n");
	}
}

void Repo::golesteReteta() noexcept {
	reteta.clear();
}

void Repo::genereazaReteta(int numar) {
	if (all.size() == 0)
		throw RepoException("Nu exista medicamente!\n");
	for (int i = 0; i < numar; i++) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, all.size() - 1);
		int rndNr = dist(mt);
		map<string, Medicament>::iterator rndIt = all.begin();
		std::advance(rndIt, rndNr);
		reteta.push_back(rndIt->second);
	}
}

void FileRepo::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw RepoException("Unable to open file:" + fName);
	}
	while (!in.eof()) {
		string denumire, producator, substanta;
		int pret;
		in >> denumire >> pret >> producator >> substanta;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}
		Medicament m{ denumire.c_str(), pret, producator.c_str(), substanta.c_str() };
		Repo::adauga(m);
	}
	in.close();
}

void FileRepo::writeToFile() {
	std::ofstream out(fName);

	for (auto& m : getAll()) {
		out << m.getDenumire();
		out << std::endl;
		out << m.getPret();
		out << std::endl;
		out << m.getProducator();
		out << std::endl;
		out << m.getSubstantaActiva();
		out << std::endl;
	}
	out.close();
}


ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}


void testRepoAdauga() {
	Repo testRepo;
	testRepo.adauga(Medicament{ "a", 1, "a", "a" });
	assert(testRepo.getAll().size() == 1);
	testRepo.adauga(Medicament{ "b", 1, "b", "b" });
	assert(testRepo.getAll().size() == 2);

	try {
		testRepo.adauga(Medicament{ "a", 1, "a", "a" });
	}
	catch (const RepoException&) {
		assert(true);
	}

	try
	{
		testRepo.adauga(Medicament{ "a", 1, "a", "a" });
	}
	catch (const RepoException & ex) {
		stringstream os;
		os << ex;
		assert(os.str().find("exista") >= 0);
	}
}

void testRepoSterge() {
	Repo testRepo;
	testRepo.adauga(Medicament{ "a", 1, "a", "a" });
	testRepo.adauga(Medicament{ "b", 1, "b", "b" });
	assert(testRepo.getAll().size() == 2);
	testRepo.sterge("a");
	assert(testRepo.getAll().size() == 1);

	try {
		testRepo.sterge("a");
	}
	catch (const RepoException&) {
		assert(true);
	}
	assert(testRepo.getAll().size() == 1);
}

void testRepoModifica() {
	Repo testRepo;
	testRepo.adauga(Medicament{ "a", 1, "a", "a" });
	testRepo.adauga(Medicament{ "b", 1, "b", "b" });
	testRepo.modifica("a", Medicament("a", 2, "c", "c"));
	assert(testRepo.getAll().front().getPret() == 2);
	assert(testRepo.getAll().front().getProducator() == "c");
	assert(testRepo.getAll().front().getSubstantaActiva() == "c");

}

void testFileRepo() {
	std::ofstream out("testMedicamente.txt", std::ios::trunc);
	out.close();//creez un fisier gol
	FileRepo repF{ "testMedicamente.txt" };
	repF.adauga(Medicament{ "aaa",12,"aaa", "aaa" });
	assert(repF.getAll().size() == 1);
	auto m = repF.cauta("aaa");
	assert(m.getPret() == 12);
	assert(m.getProducator() == "aaa");
	assert(m.getDenumire() == "aaa");
	assert(m.getSubstantaActiva() == "aaa");
	repF.modifica("aaa", Medicament{ "aaa", 200, "vvv", "bbb" });
	auto p = repF.cauta("aaa");
	assert(p.getPret() == 200);
	FileRepo repF2{ "testMedicamente.txt" };
	assert(repF2.getAll().size() == 1);
	repF.sterge("aaa");
	assert(repF.getAll().size() == 0);

	try {
		FileRepo repF3{ "test123.txt" };
	}
	catch (RepoException&) {
		assert(true);
	}
}
