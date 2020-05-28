#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

int Colectie::d(TElem e) const{
	//theta(1)
	return abs(e) % m;
}

void Colectie::reSize()
{
	//theta(m)
	//copiaza elementele si frecventele
	TElem* eVechi = new TElem[m];
	int* frecVechi = new int[m];
	int mVechi = m;
	for (int i = 0; i < m; i++)
	{
		eVechi[i] = e[i];
		frecVechi[i] = frec[i];
	}

	//redimensionare
	m = m * 2;
	TElem* eNou = new TElem[m];
	int* frecNou = new TElem[m];
	int* urmNou = new int[m];
	for (int i = 0; i < m; i++)
	{
		eNou[i] = NIL;
		urmNou[i] = NIL;
		frecNou[i] = 0;
	}
	delete[] e;
	delete[] frec;
	delete[] urm;
	e = eNou;
	frec = frecNou;
	urm = urmNou;
	

	//reHash
	primLiber = 0;
	dimensiune = 0;
	for (int i = 0; i < mVechi; i++)
	{
		while (frecVechi[i] > 0)
		{
			adauga(eVechi[i]);
			frecVechi[i]--;
		}	
	}

	delete[] eVechi;
	delete[] frecVechi;
}

Colectie::Colectie() {
	/* de adaugat */
	//theta(m)
	m = 13;
	e = new TElem[m];
	frec = new int[m];
	urm = new int[m];
	dimensiune = 0;
	for (int i = 0; i < m; i++)
	{
		e[i] = NIL;
		urm[i] = NIL;
		frec[i] = 0;
	}
	primLiber = 0;
}

void Colectie::actPrimLiber() {
	primLiber++;
	while(primLiber < m && e[primLiber] != NIL)
	{
		primLiber++;
	}
}


void Colectie::adauga(TElem elem) {
	/* de adaugat */
	//theta(1)
	int i = d(elem);

	//pozitia este libera
	if (e[i] == NIL) 
	{
		e[i] = elem;
		frec[i]++;
		dimensiune++;
		if (i == primLiber)
			actPrimLiber();
		return;
	}

	//iteram pana la capatul inalntuirii
	int j = NIL;
	while (i != NIL && e[i] != elem)
	{
		j = i;
		i = urm[i];
	}

	//pozitia este ocupata de un element de valoare identica cu elem
	if (i != NIL)
	{
		frec[i]++;
		dimensiune++;
		return;
	}
		
	//adaugam elementul
	if (primLiber < m)
	{
		e[primLiber] = elem;
		frec[primLiber]++;
		urm[j] = primLiber;
		dimensiune++;
		actPrimLiber();
		return;
	}
	else //tabela este plina
	{
		reSize();
		adauga(elem);
	}
}


bool Colectie::sterge(TElem elem) {
	/* de adaugat */
	//theta(1)

	/*
	int i = d(elem);
	int j = NIL;

	//iteram pana la capatul inlantuirii sau pana gasim elementul
	while (i != NIL && e[i] != elem)
	{
		j = i;
		i = urm[i];
	}

	if (i != NIL) //gasit
	{
		if (frec[i] > 1) //exista mai multe elemente cu aceasta valoare
		{
			frec[i]--;
			dimensiune--;
			return true;
		}

		else //exista un singur element cu aceasta valoare
		{
			if (urm[i] == NIL)//nu exista elemente dupa el
			{
				e[i] = NIL;
				frec[i]=0;
				dimensiune--;
				if(j != NIL)
					urm[j] = NIL;//urmatorul pentru nodul precedent este setat la NIL
				if (i < primLiber)
					primLiber = i;
				return true;
			}
			else
			{
				frec[i]=0;
				dimensiune--;
				bool doneMoving = false;
				do 
				{
					int curent = urm[i];
					int prec = i;
					while (curent != NIL && d(e[i]) != i)
					{
						prec = curent;
						curent = urm[curent];
					}
					if (curent == NIL)
						doneMoving = true;
					else
					{
						e[i] = e[curent];
						i = curent;
						j = prec;
					}
				} while (!doneMoving);
				if (j != NIL) {
					urm[j] = urm[i];
				}
				e[i] = NIL;
				urm[i] = NIL;
				if (i < primLiber) {
					primLiber = i;
				}
				return true;
			}
		}
	}
	*/
	int actual = d(elem);
	int precendet = NIL;
	
	while (actual != NIL && e[actual] != elem)
	{
		precendet = actual;
		actual = urm[actual];
	}

	if(actual == NIL) //nu exista elementul
		return false;
	else
	{
		if (frec[actual] > 1) //exista mai multe elemente cu valoarea cautata
		{
			frec[actual]--;
			dimensiune--;
			return true;
		}
		else //exista un singur element cu aceasta valoare
		{
			bool doneMoving = false;
			do {
				int pozitieCurenta = urm[actual];
				int pozitiePrecedenta = actual;

				while (pozitieCurenta != NIL && d(e[pozitieCurenta]) != actual)//cauta primul element care se
																	//potriveste pe pozitia curenta
				{
					pozitiePrecedenta = pozitieCurenta;
					pozitieCurenta = urm[pozitieCurenta];
				}

				if (pozitieCurenta == NIL) //nu gasim elementul potrivit
					doneMoving = true;
				else {
					e[actual] = e[pozitieCurenta];
					frec[actual] = frec[pozitieCurenta];
					actual = pozitieCurenta;
					precendet = pozitiePrecedenta;
				}
			} while (doneMoving == false);
			if (precendet != NIL)
			{
				urm[precendet] = urm[actual];
			}
			e[actual] = NIL;
			frec[actual] = 0;
			urm[actual] = NIL;
			if (actual < primLiber)
				primLiber = actual;
		}
		dimensiune--;
		return true;
	}
}


bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	//theta(1)
	int i = d(elem);

	while (i != NIL && e[i] != elem)
	{
		i = urm[i];
	}

	if (i != NIL)
		return true;
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	//theta(1)
	int i = d(elem);
	while (i != NIL && e[i] != elem)
	{
		i = urm[i];
	}
	if (i!=NIL)
		return frec[i];
	return 0;
}


int Colectie::dim() const {
	/* de adaugat */
	//theta(1)
	return dimensiune;
}


bool Colectie::vida() const {
	/* de adaugat */
	//theta(1)
	if(dimensiune == 0)
		return true;
	return false;
}


void Colectie::golește() {
	// elimină toate elementele colecției
	//theta(m)
	for (int i = 0; i < m; i++)
	{
		if (e[i] != NIL)
		{
			e[i] = NIL;
			urm[i] = NIL;
			frec[i] = 0;
		}
	}
	dimensiune = 0;

}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}



Colectie::~Colectie() {
	/* de adaugat */
	delete[] e;
	delete[] urm;
	delete[] frec;
}

