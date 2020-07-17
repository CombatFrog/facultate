#pragma once
#include "validator.h"
#include <qmessagebox.h>

/*Functie care valideaza un produs
  input: p - un produs
  output : true - faca produsul este valid
		   false - in caz contrar
*/
bool Validator::valideaza(const Produs& p)
{
	QMessageBox msg;
	bool valid = true;
	if (p.getNume() == "")
	{
		msg.setText("Nume invalid!");
		msg.exec();
		valid = false;
	}
	if (p.getTip() == "")
	{
		msg.setText("Tip invalid!");
		msg.exec();
		valid = false;
	}
	if (p.getPret() < 1.0 || p.getPret() > 100.0)
	{
		msg.setText("Pret invalid!");
		msg.exec();
		valid = false;
	}
	return valid;
}

void testValidator()
{
	Validator validatorTest;
	Produs p{ 1, "", "tip", 10.0 };
	assert(validatorTest.valideaza(p) == false);
	Produs p1{ 1, "nume", "tip", -10.0 };
	assert(validatorTest.valideaza(p1) == false);
	Produs p2{ 1, "nume", "tip", 1000.0 };
	assert(validatorTest.valideaza(p2) == false);
	Produs p3{ 1, "nume", "tip", 100.0 };
	assert(validatorTest.valideaza(p3) == true);
	Produs p4{ 1, "nume", "", 10.3 };
	assert(validatorTest.valideaza(p4) == false);
}