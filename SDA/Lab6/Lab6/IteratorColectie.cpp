#include "IteratorColectie.h"
#include "Colectie.h"
#include <iostream>


void IteratorColectie::deplasare() {
	//O(m)
	while (curent < col.m && col.e[curent] == NIL)
		curent++;
}

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	//O(m)
	curent = 0;
	indexFrecv = 1;
	deplasare();
}

void IteratorColectie::prim() {
	/* de adaugat */
	//O(m)
	curent = 0;
	indexFrecv = 1;
	deplasare();
}


void IteratorColectie::urmator() {
	/* de adaugat */
	//O(m)
	if (indexFrecv < col.frec[curent])
		indexFrecv++;
	else 
	{
		indexFrecv = 1;
		curent++;
		deplasare();
	}
	/*
	if (!valid())
		throw std::exception{ "Invalid" };
	*/
}


bool IteratorColectie::valid() const {
	/* de adaugat */
	//theta(1)
	if (curent < col.m)
		return true;
	return false;
}



TElem IteratorColectie::element() const {
	/* de adaugat */
	if(valid())
		return col.e[curent];
	throw std::exception{ "Invalid" };
}