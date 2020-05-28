#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	iterator = 0;
}

void IteratorColectie::prim() {
	/* de adaugat */
	iterator = 0;
}


void IteratorColectie::urmator() {
	/* de adaugat */
	iterator = iterator + 1;
	if (valid() == false)
		throw;
}


bool IteratorColectie::valid() const {
	/* de adaugat */
	return iterator < col.dim();
}



TElem IteratorColectie::element() const {
	/* de adaugat */
	if (valid() == true)
		return col.elemente[col.pozitii[iterator]];
	else
		throw;
}