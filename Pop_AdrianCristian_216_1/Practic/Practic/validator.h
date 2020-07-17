#pragma once
#include "produs.h"

class Validator {
public:
	/*Functie care valideaza un produs*/
	bool valideaza(const Produs& p);
};

void testValidator();