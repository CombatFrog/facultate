#pragma once
#include "medicament.h"

#include <vector>
#include <string>
#include <ostream>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::ostream;

class VirtualRepo {
public:
	VirtualRepo() = default;

	VirtualRepo(const VirtualRepo& ot) = delete;

	virtual ~VirtualRepo() = default;

	virtual void adauga(const Medicament& m) = 0;

	virtual void sterge(const string& denumire) = 0;

	virtual const Medicament& cauta(string denumire) const = 0;

	virtual void modifica(const string& denumire, const Medicament& m) = 0;

	virtual const vector<Medicament> getAll() const noexcept = 0;
};

class Repo : public VirtualRepo {
	//vector<Medicament> all;
	map<string, Medicament> all;
	vector<Medicament> reteta;
public:
	/*
	Adauga un medicament in lista
	*/
	void adauga(const Medicament& m) override;

	/*
	Cauta un medicament in lista
	*/
	const Medicament& cauta(string denumire) const override;

	/*
	Returneaza toate medicamentele salvate
	*/
	const vector<Medicament> getAll() const noexcept override {
		vector<Medicament> lista;
		for (const auto& m : all) {
			lista.push_back(m.second);
		}
		return lista;
	}

	const vector<Medicament> getReteta() const noexcept {
		return reteta;
	}

	/*
	Sterge un medicament din lista
	*/
	void sterge(const string& denumire) override;

	/*
	Modifica un medicament din lista
	*/
	void modifica(const string& denumire, const Medicament& m) override;

	void adaugaReteta(const string& denumire);

	int dimensiuneRetata() noexcept {
		return reteta.size();
	}

	void golesteReteta() noexcept;

	void genereazaReteta(int numar);


private:
	/*
	Verifica dace un medicament exista in lista
	*/
	bool exista(const Medicament& m) const;
};

class FileRepo : public Repo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	FileRepo(std::string fName) :Repo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	void adauga(const Medicament& m) override {
		Repo::adauga(m);
		writeToFile();
	}

	void sterge(const string& denumire) override {
		Repo::sterge(denumire);//apelam metoda din clasa de baza
		writeToFile();
	}

	void modifica(const string& denumire, const Medicament& m) override {
		Repo::modifica(denumire, m);
		writeToFile();
	}
};

class RepoException {
	string msg;
public:
	RepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);


void testRepoAdauga();
void testRepoSterge();
void testRepoModifica();
void testFileRepo();