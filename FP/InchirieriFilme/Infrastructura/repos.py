from Exceptii.exceptii import RepoError

class RepoClienti():

    def __init__(self):
        self.__lista_clienti = []

    def adauga_client(self, client):
        #functie care adauga clientul client in lista de clienti
        if self.id_in_list(client.get_id()):
            raise RepoError("Exista un client cu acest Id")
        self.__lista_clienti.append(client)

    def modifica_client(self, client):
        #functie care modifica clientul client
        if not self.id_in_list(client.get_id()):
            raise RepoError("Id inexistent!")
        for c in self.__lista_clienti:
            if c.get_id() == client.get_id():
                c.set_nume(client.get_nume())
                c.set_cnp(client.get_cnp())

    def sterge_client(self, client):
        #functie care sterge clientul client din lista de clienti
        if not self.id_in_list(client.get_id()):
            raise RepoError("Id inexistent!")
        for c in self.__lista_clienti:
            if c.get_id() == client.get_id():
                self.__lista_clienti.remove(c)

    def cauta_client(self, client):
        #functie care cauta clientul client
        for c in self.__lista_clienti:
            if c.get_id() == client.get_id() or c.get_nume() == client.get_nume() or c.get_cnp() == client.get_cnp():
                return c
        raise RepoError("Client inexistent!")

    def get_all(self):
        #functia care returneaza lista cu toti clientii
        return self.__lista_clienti[:]

    def id_in_list(self, id_client):
        #functie care verifica daca exista un client cu idul id_client in list de clienti
        ok = False
        for client in self.__lista_clienti:
            if client.get_id() == id_client:
                ok = True
        return ok

    def empty(self):
        self.__lista_clienti = []

class RepoFilme():

    def __init__(self):
        self.__lista_filme = []

    def adauga_film(self, film):
        #functie care adauga filmul film in lista de filme
        if self.id_in_list(film.get_id()):
            raise RepoError("Exista un film cu acest Id")
        self.__lista_filme.append(film)

    def modifica_film(self, film):
        #functie care modifica filmul film
        if not self.id_in_list(film.get_id()):
            raise RepoError("Id inexistent!")
        for f in self.__lista_filme:
            if f.get_id() == film.get_id():
                f.set_titlu(film.get_titlu())
                f.set_descriere(film.get_descriere())
                f.set_gen(film.get_gen())

    def sterge_film(self, film):
        #functie care sterge filmul film din lista de filme
        if not self.id_in_list(film.get_id()):
            raise RepoError("Id inexistent!")
        for f in self.__lista_filme:
            if f.get_id() == film.get_id():
                self.__lista_filme.remove(f)

    def cauta_film(self, film):
        #functie care cauta filmul film in lista de filme
        for f in self.__lista_filme:
            if f.get_id() == film.get_id():
                return f
        raise RepoError("Film inexistent!")

    def get_all(self):
        # functia care returneaza lista cu toate filmele
        return self.__lista_filme[:]

    def id_in_list(self, id_film):
        #functie care verifica daca exista un film cu idul id_film in lista de filme
        ok = False
        for film in self.__lista_filme:
            if film.get_id() == id_film:
                ok = True
        return ok

    def empty(self):
        self.__lista_filme = []

class RepoInchirieri():

    def __init__(self):
        self.__lista_inchirieri = []

    def inchiriaza(self, inchiriere):
        #functie care adauga inchirierea inchiriere in lista de inchirieri
        self.__lista_inchirieri.append(inchiriere)
        film = inchiriere.get_film()
        client = inchiriere.get_client()
        film.inchiriaza()
        client.inchiriaza()

    def returneaza(self, inchiriere):
        #functie care sterge inchirierea inchiriere din lista de inchirieri
        for i in self.__lista_inchirieri:
            if i.get_id_client() == inchiriere.get_id_client() and i.get_id_film() == inchiriere.get_id_film():
                self.__lista_inchirieri.remove(i)
                film = inchiriere.get_film()
                client = inchiriere.get_client()
                film.returneaza()
                client.returneaza()

    def get_all(self):
        #functie care returneaza toate inchirierile din lista de inchirieri
        return self.__lista_inchirieri[:]

    def empty(self):
        self.__lista_inchirieri = []
