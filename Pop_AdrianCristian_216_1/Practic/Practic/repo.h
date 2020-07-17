#pragma once
#include "produs.h"
#include <qmessagebox.h>

#include <vector>
#include <string>
#include <fstream>

using std::vector;

class Repo {
	vector<Produs> produse;
public:
	Repo() = default;

	Repo(const Repo& ot) = delete;

	~Repo() = default;

	//adauga un produs nou in lista de produse
	virtual void adauga(const Produs& p);

	//returneaza toate produsele
	const vector<Produs> getAll() const noexcept {
		return produse;
	}
private:

	//verifica daca produsul cu id-ul id exista in lista de produse
	bool exista(int id) const;
};

class FileRepo : public Repo
{
	string fileName;
	void loadFromFile();
	void writeToFile();
public:

	FileRepo(string file) :Repo(), fileName{ file }
	{
		loadFromFile();
	}

	void adauga(const Produs& p) override
	{
		Repo::adauga(p);
		writeToFile();
	}
};

void testRepo();