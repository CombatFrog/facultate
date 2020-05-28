#pragma once

#define NULL_TELEM -1
#define NIL -100000

typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	int m;
	TElem* e;
	int* urm;
	int* frec;
	int primLiber;
	int dimensiune;

	//actualizare primLiber
	void actPrimLiber();
	//functia de dispersie
	int d(TElem e) const;
	//functie de redimensionare
	void reSize();


public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// elimină toate elementele colecției
	void golește();

	// destructorul colectiei
	~Colectie();

};

