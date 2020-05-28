#include "service.h"

#include <assert.h>
#include <algorithm>
#include <numeric>

using std::sort;
using std::copy_if;


void Service::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista operatii");
	}
	/*
	ActiuneUndo* act = undoActions.back();
	act->doUndo();
	undoActions.pop_back();
	delete act;
	*/
	// Varianta cu unique_ptr
	//obs: la obiecte unique_ptr nu putem face copie			
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

/*
Functie care verifica daca un medicament este valid,
iar in caz contrar il  adauga la lista de medicamente
input: denumire - denumirea medicamentului
	   pret - pretul medicamentului
	   producator - producatorul medicamentului
	   substanta - substanta activa a medicamentului
output: medicamentul cu denumirea denumire, pretul pret, producatorul producator,
		substanta activa substanta este adaugat la lista de medicamente
*/
void Service::adaugaMedicament(const string& denumire, int pret, const string& producator, const string& substanta) {
	Medicament m{ denumire, pret, producator, substanta };
	val.valideaza(m);
	rep.adauga(m);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, m));
}

/*
Functie care sterge un medicament din lista de medicamente
input: denumire - denumirea medicamentului
output: medicamentul cu denumirea denumire este sters din lista de medicamente
*/
void Service::stergeMedicament(const string& denumire) {
	undoActions.push_back(std::make_unique<UndoSterge>(rep, rep.cauta(denumire)));
	rep.sterge(denumire);
}


/*
Functie care valideaza noile valori ale unui medicament,
iar in caz ca sunt valide, medicamentul primeste aceste noi valori
input: denumire - denumirea medicamentului
	   denumireNoua - noua denumire a medicamnetului
	   pretNou - noul pret al medicamentului
	   producatorNou - noul producator al medicamentului
	   substantaNoua - noua substanta activa a medcamentului
output - medicamentul cu denumirea denumire primeste noile valori
		 (denumireNoua, pretNou, producatorNou, substantaNoua)
*/
void Service::modificaMedicament(const string& denumire, int pretNou, const string& producatorNou, const string& substantaNoua) {
	Medicament m{ denumire, pretNou, producatorNou, substantaNoua };
	undoActions.push_back(std::make_unique<UndoModifica>(rep, denumire, rep.cauta(denumire)));
	val.valideaza(m);
	rep.modifica(denumire, m);
}

/*
Functie care filtreaza elementele dintr-o list dupa pret
input: pret - pretul cautat
output: filru - un vector care contine doar elementele din lista care au pretul pret
*/
const vector<Medicament> Service::filtreazaPret(int pret) {
	vector<Medicament> filtru;
	vector<Medicament> lista = rep.getAll();
	copy_if(lista.begin(), lista.end(), std::back_inserter(filtru), [pret](const Medicament& m) noexcept {
		return m.getPret() == pret;
		});
	return filtru;
}


/*
Functie care filtreaza elementele dintr-o list dupa substanta activa
input: substanta - substanta activa cautata
output: filru - un vector care contine doar elementele din lista care au substanta activa substanta
*/
const vector<Medicament> Service::filtreazaSubstanta(const string& substanta) {
	vector<Medicament> filtru;
	vector<Medicament> lista = rep.getAll();
	copy_if(lista.begin(), lista.end(), std::back_inserter(filtru), [substanta](const Medicament& m) {
		return m.getSubstantaActiva() == substanta;
		});
	return filtru;
}


/*
Functie care sorteaza o lista alfabetic dupa denumire
*/
const vector<Medicament> Service::sorteazaDenumire() {
	vector<Medicament> lista = rep.getAll();
	sort(lista.begin(), lista.end(), [](const Medicament& m1, const Medicament& m2) {
		return m1.getDenumire() < m2.getDenumire();
		});
	return lista;
}


/*
Functie care sorteaza o lista alfabetic dupa producator
*/
const vector<Medicament> Service::sorteazaProducator() {
	vector<Medicament> lista = rep.getAll();
	sort(lista.begin(), lista.end(), [](const Medicament& m1, const Medicament& m2) {
		return m1.getProducator() < m2.getProducator();
		});
	return lista;
}

/*
Functie care sorteaza o lista alfabetic dupa substanta activa.
Medicamentele care au aceeasi substanta activa sunt sortate crescator dupa pret
*/
const vector<Medicament> Service::sorteazaSubstantaPret() {
	vector<Medicament> lista = rep.getAll();
	sort(lista.begin(), lista.end(), [](const Medicament& m1, const Medicament& m2) {
		return (m1.getSubstantaActiva() < m2.getSubstantaActiva()) || ((m1.getSubstantaActiva() == m2.getSubstantaActiva()) && (m1.getPret() < m2.getPret()));
		});
	return lista;
}

void Service::adaugaReteta(const string& denumire) {
	rep.adaugaReteta(denumire);
}

void Service::golesteReteta() noexcept {
	rep.golesteReteta();
}

void Service::genereazaReteta(int numar) {
	rep.genereazaReteta(numar);
}



void testServiceReteta() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };

	try {
		testService.genereazaReteta(5);
	}
	catch (RepoException&) {
		assert(true);
	}

	testService.adaugaMedicament("a", 1, "a", "a");
	testService.adaugaMedicament("b", 1, "b", "b");
	testService.adaugaMedicament("c", 1, "c", "c");

	testService.genereazaReteta(10);
	assert(testService.dimensiuneReteta() == 10);
	testService.golesteReteta();
	assert(testService.getReteta().size() == 0);

	testService.adaugaReteta("a");
	testService.adaugaReteta("a");
	testService.adaugaReteta("b");
	testService.adaugaReteta("c");
	assert(testService.dimensiuneReteta() == 4);
	testService.golesteReteta();

	try {
		testService.adaugaReteta("z");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testServiceAdauga() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };

	testService.adaugaMedicament("a", 1, "a", "a");
	assert(testService.getAll().size() == 1);
	testService.adaugaMedicament("b", 1, "b", "b");
	assert(testService.getAll().size() == 2);

	try {
		testService.adaugaMedicament("a", 1, "a", "a");
	}
	catch (RepoException&) {
		assert(true);
	}

	assert(testService.getAll().size() == 2);

	try {
		testService.adaugaMedicament("", -1, "", "");
	}
	catch (ValidatorException&) {
		assert(true);
	}
	assert(testService.getAll().size() == 2);
}

void testServiceSterge() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };

	testService.adaugaMedicament("a", 1, "a", "a");
	testService.adaugaMedicament("b", 1, "b", "b");
	testService.stergeMedicament("a");
	assert(testService.getAll().size() == 1);

	try {
		testService.stergeMedicament("c");
	}
	catch (RepoException&) {
		assert(true);
	}
	assert(testService.getAll().size() == 1);
}

void testServiceModifica() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };

	testService.adaugaMedicament("a", 1, "a", "a");
	testService.adaugaMedicament("b", 1, "b", "b");

	testService.modificaMedicament("a", 1, "c", "c");
	assert(testService.getAll().size() == 2);
}

void testServiceFiltru() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };
	testService.adaugaMedicament("a", 1, "a", "a");
	testService.adaugaMedicament("b", 1, "b", "b");
	testService.adaugaMedicament("c", 1, "a", "b");
	testService.adaugaMedicament("d", 2, "a", "b");
	testService.adaugaMedicament("e", 2, "a", "b");
	assert(testService.filtreazaPret(1).size() == 3);
	assert(testService.filtreazaPret(2).size() == 2);
	assert(testService.filtreazaSubstanta("a").size() == 1);
	assert(testService.filtreazaSubstanta("b").size() == 4);
}

void testServiceSortare() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };
	testService.adaugaMedicament("d", 1, "a", "c");
	testService.adaugaMedicament("b", 3, "b", "b");
	testService.adaugaMedicament("c", 1, "e", "b");
	testService.adaugaMedicament("a", 2, "c", "a");
	testService.adaugaMedicament("e", 7, "d", "b");

	vector <Medicament> sort = testService.sorteazaDenumire();
	assert(sort[0].getDenumire() == "a");
	assert(sort[1].getDenumire() == "b");
	assert(sort[2].getDenumire() == "c");
	assert(sort[3].getDenumire() == "d");
	assert(sort[4].getDenumire() == "e");

	sort = testService.sorteazaProducator();
	assert(sort[0].getProducator() == "a");
	assert(sort[1].getProducator() == "b");
	assert(sort[2].getProducator() == "c");
	assert(sort[3].getProducator() == "d");
	assert(sort[4].getProducator() == "e");



	sort = testService.sorteazaSubstantaPret();
	assert(sort[0].getSubstantaActiva() == "a");
	assert(sort[0].getPret() == 2);

	assert(sort[1].getSubstantaActiva() == "b");
	assert(sort[1].getPret() == 1);

	assert(sort[2].getSubstantaActiva() == "b");
	assert(sort[2].getPret() == 3);

	assert(sort[3].getSubstantaActiva() == "b");
	assert(sort[3].getPret() == 7);

	assert(sort[4].getSubstantaActiva() == "c");
	assert(sort[4].getPret() == 1);
}

void testUndo() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };
	testService.adaugaMedicament("d", 1, "a", "c");
	testService.adaugaMedicament("b", 3, "b", "b");
	testService.adaugaMedicament("c", 1, "e", "b");
	testService.undo();
	testService.undo();
	assert(testService.getAll().size() == 1);
	testService.stergeMedicament("d");
	testService.undo();
	assert(testService.getAll().size() == 1);
	testService.modificaMedicament("d", 200, "test", "test");
	testService.undo();
	assert(testService.getAll().front().getProducator() == "a");
	testService.undo();
	try {
		testService.undo();
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testServiceSuma() {
	Repo testRepo;
	Validator testValidator;
	Service testService{ testRepo, testValidator };
	testService.adaugaMedicament("d", 1, "a", "c");
	testService.adaugaMedicament("b", 3, "b", "b");
	testService.adaugaMedicament("c", 1, "e", "b");
	testService.adaugaReteta("b");
	testService.adaugaReteta("c");
	testService.adaugaReteta("d");
	assert(testService.suma() == 5);
}