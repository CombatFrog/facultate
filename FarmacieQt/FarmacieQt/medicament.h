#pragma once
#include <iostream>
#include <string>

using std::string;

class Medicament {
	std::string denumire;
	int pret;
	std::string producator;
	std::string substantaActiva;
public:
	Medicament(const string d, int p, const string prod, const string s) :denumire{ d }, pret{ p }, producator{ prod }, substantaActiva{ s }{}

	string getDenumire() const {
		return denumire;
	}

	int getPret() const noexcept {
		return pret;
	}

	string getProducator() const {
		return producator;
	}

	string getSubstantaActiva() const {
		return substantaActiva;
	}

	bool operator==(const Medicament& m) const {
		return (denumire == m.getDenumire() && pret == m.getPret() && producator == m.getProducator() && substantaActiva == m.getSubstantaActiva());
	}
};
