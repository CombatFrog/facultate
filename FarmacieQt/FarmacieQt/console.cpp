#include "console.h"

#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

using std::cin;
using std::cout;

/*
Adauga un medicament in lista
*/
void Console::adaugaUI() {
	string denumire, producator, substanta;
	int pret;
	cout << "Denumire: ";
	cin >> denumire;
	cout << "Pret: ";
	cin >> pret;
	cout << "Producator: ";
	cin >> producator;
	cout << "Substanta activa: ";
	cin >> substanta;
	service.adaugaMedicament(denumire, pret, producator, substanta);
	cout << "Medicament adaugat cu succes!\n";
	cout << "\n";
}

/*
Afiseaza toate medicamentele din lista
*/
void Console::afiseazaUI(const vector <Medicament>& medicamente) {
	cout << "Medicamente:\n";
	for (const auto& medicament : medicamente) {
		cout << "Denumire: " << medicament.getDenumire() << " Pret: " << medicament.getPret() << " Producator: " << medicament.getProducator() << " Substanta activa: " << medicament.getSubstantaActiva() << '\n';
	}
	cout << "\n";
}

/*
Sterge un medicament din lista
*/
void Console::stergeUI() {
	cout << "Introduceti denumirea medicamentului: ";
	string denumire;
	cin >> denumire;
	service.stergeMedicament(denumire);
	cout << "Medicament sters cu succes!\n";
	cout << "\n";
}

/*
Modifica un meidcament din lista
*/
void Console::modificaUI() {
	string denumire;
	cout << "Introduceti denumirea medicamentului: ";
	cin >> denumire;

	string producatorNou, substantaNoua;
	int pretNou;
	cout << "Introduceti noul pret: ";
	cin >> pretNou;
	cout << "Introduceti noul producator: ";
	cin >> producatorNou;
	cout << "Introduceti noua substanta activa: ";
	cin >> substantaNoua;

	service.modificaMedicament(denumire, pretNou, producatorNou, substantaNoua);
	cout << "Medicament modificat cu succes!\n";
	cout << "\n";
}

void Console::adaugaRetetaUI() {
	string denumire;
	cout << "Introduceti denumirea medicamentului: ";
	cin >> denumire;
	service.adaugaReteta(denumire);
	cout << "Medicament adaugat cu succes!\n";
	cout << "\n";
}

void Console::golesteRetetaUI() {
	service.golesteReteta();
	cout << "Reteta golita cu succes!\n";
	cout << "\n";
}

void Console::genereazaRetetaUI() {
	int numarMedicamenente;
	cout << "Introduceti numarul de medicamente: ";
	cin >> numarMedicamenente;
	service.genereazaReteta(numarMedicamenente);
	cout << "Reteta generata cu succes!\n";
	cout << "\n";
}

void Console::exportUI() {
	std::ofstream fisierExport;
	string denumireFisier;
	cout << "Introduceti denumirea fisierului: ";
	cin >> denumireFisier;
	fisierExport.open(denumireFisier);
	vector<Medicament> reteta = service.getReteta();
	fisierExport << "Denumire" << " " << "Pret" << " " << "Producator" << " " << "Substanta" << "\n";
	for (const auto& medicament : reteta) {
		fisierExport << medicament.getDenumire() << " " << medicament.getPret() << " " << medicament.getProducator() << " " << medicament.getSubstantaActiva() << "\n";
	}
	fisierExport.close();
}



void Console::start() {
	while (true)
	{
		cout << "------------------------------------------\n";
		cout << " Reteta este alcatuita din " << service.dimensiuneReteta() << " medicamente. \n";
		cout << " Pret total: " << service.suma() << "\n";
		cout << "------------------------------------------\n";
		cout << "\n";
		cout << "1. Adauga\n2. Afiseaza\n3. Sterge\n4. Modifica\n5. Filtreaza dupa pret\n6. Filtreaza dupa substanta activa\n"
			"7. Sorteaza dupa denumire\n8. Sorteaza dupa producator\n9. Sorteaza dupa substanta activa si pret\n"
			"10. Adauga pe reteta\n11. Goleste reteta\n12. Genereaza reteta\n13. Export\n14. Undo\n0. Exit\nComanda: ";
		int cmd;
		cin >> cmd;
		try {
			switch (cmd)
			{
			case 1:
				adaugaUI();
				break;
			case 2:
				afiseazaUI(service.getAll());
				break;
			case 3:
				stergeUI();
				break;
			case 4:
				modificaUI();
				break;
			case 5: {
				int pret;
				cout << "Introduceti pretul: ";
				cin >> pret;
				afiseazaUI(service.filtreazaPret(pret));
				break;
			}
			case 6: {
				string substanta;
				cout << "Introduceti substanta activa: ";
				cin >> substanta;
				afiseazaUI(service.filtreazaSubstanta(substanta));
				break;
			}
			case 7:
				afiseazaUI(service.sorteazaDenumire());
				break;
			case 8:
				afiseazaUI(service.sorteazaProducator());
				break;
			case 9:
				afiseazaUI(service.sorteazaSubstantaPret());
				break;
			case 10:
				adaugaRetetaUI();
				break;
			case 11:
				golesteRetetaUI();
				break;
			case 12:
				genereazaRetetaUI();
				break;
			case 13:
				exportUI();
				break;
			case 14:
				service.undo();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!";
			}
		}
		catch (const RepoException & ex) {
			cout << ex << '\n';
		}
		catch (const ValidatorException & ex) {
			cout << ex << '\n';
		}
	}
}