from Infrastructura.repos import RepoFilme, RepoClienti, RepoInchirieri
from Domain.entitati import Film, Client, Inchiriere

class RepoFilmeFromFile(RepoFilme):

    def __init__(self, nume_fisier):
        RepoFilme.__init__(self)
        self.__nume_fisier = nume_fisier
        self.incarca_din_fisier()

    def __creeaza_film(self, linie):
        #functie care creeaza un film din campurile unei linii din fisier
        campuri = linie.split(' ')
        film = Film(int(campuri[0]), campuri[1], campuri[2], campuri[3], 0)
        return film

    def incarca_din_fisier(self):
        #functie care incarca filme dintr-un fisier
        RepoFilme.empty(self)
        f = open(self.__nume_fisier)
        continut = f.read()
        f.close()
        linii = continut.split('\n')
        for linie in linii:
            if linie.strip() == '':
                continue
            film = self.__creeaza_film(linie)
            if not RepoFilme.id_in_list(self, film.get_id()):
                RepoFilme.adauga_film(self, film)


    def __adauga_in_fisier(self, film):
        #functie care adauga un film in fisier
        with open(self.__nume_fisier, 'w') as f:
            filme = self.get_all()
            for film in filme:
                f.write(str(film.get_id()) + " " + film.get_titlu() + " " + film.get_descriere() + " " + film.get_gen())
                f.write('\n')


    def adauga_film(self, film):
        #functie care adauga un film in fisier si in memorie
        RepoFilme.adauga_film(self, film)
        self.__adauga_in_fisier(film)

    def __sterge_din_fisier(self):
        #functie care sterge un film din fisier
        with open(self.__nume_fisier, 'w') as f:
            filme = self.get_all()
            for film in filme:
                f.write(str(film.get_id()) + " " + film.get_titlu() + " " + film.get_descriere() + " " + film.get_gen())
                f.write('\n')

    def sterge_film(self, film):
        #functie care sterge un film din fisier si din memorie
        RepoFilme.sterge_film(self, film)
        self.__sterge_din_fisier()

    def modifica_film(self, film):
        #functie care modifica un film din fisier si din memorie
        RepoFilme.modifica_film(self, film)
        self.__sterge_din_fisier()

class RepoClientiFromFile(RepoClienti):

    def __init__(self, nume_fisier):
        RepoClienti.__init__(self)
        self.__nume_fisier = nume_fisier
        self.__incarca_din_fisier()

    def __creeaza_client(self, linie):
        #functie care creeaza un client din campurile unie linii din fisier
        campuri = linie.split(' ')
        client = Client(int(campuri[0]), campuri[1], campuri[2], 0)
        return client

    def __incarca_din_fisier(self):
        #functie care incarca clienti dintr-un fisier in memorie
        RepoClienti.empty(self)
        f = open(self.__nume_fisier)
        continut = f.read()
        f.close()
        linii = continut.split('\n')
        for linie in linii:
            if linie.strip() == '':
                continue
            client = self.__creeaza_client(linie)
            if not RepoClienti.id_in_list(self, client.get_id()):
                RepoClienti.adauga_client(self, client)

    def __adauga_in_fisier(self, client):
        #functie care adauga un client in fisier
        with open(self.__nume_fisier, 'a') as f:
            linie = str(client.get_id()) + ' ' + client.get_nume() + ' ' + client.get_cnp()
            f.write(linie)
            f.write('\n')

    def adauga_client(self, client):
        #functie care adauga un client in fisier si in memorie
        RepoClienti.adauga_client(self, client)
        self.__adauga_in_fisier(client)

    def __sterge_din_fisier(self):
        #functie care sterge un film din fisier
        with open(self.__nume_fisier, 'w') as f:
            clienti = self.get_all()
            for client in clienti:
                f.write(str(client.get_id()) + " " + client.get_nume() + " " + client.get_cnp())
                f.write('\n')

    def sterge_client(self, client):
        #functie care sterge un client din fisier si din memorie
        RepoClienti.sterge_client(self, client)
        self.__sterge_din_fisier()

    def modifica_client(self, client):
        #functie xare modifica un client din fisier si din memorie
        RepoClienti.modifica_client(self, client)
        self.__sterge_din_fisier()

class RepoInchirieriFromFile(RepoInchirieri):

    def __init__(self, nume_fisier, repoClienti, repoFilme):
        RepoInchirieri.__init__(self)
        self.__repoClienti = repoClienti
        self.__repoFilme = repoFilme
        self.__nume_fisier = nume_fisier
        self.__incarca_din_fisier()

    def __incarca_din_fisier(self):
        #functie care adauga inchirieri din fisier in memorie
        f = open(self.__nume_fisier)
        continut = f.read()
        f.close()
        linii = continut.split('\n')
        for linie in linii:
            if linie.strip() == '':
                continue
            inchiriere = self.__creeaza_inchiriere(linie)
            RepoInchirieri.inchiriaza(self, inchiriere)

    def __creeaza_inchiriere(self, linie):
        #functie care creeaza o inchiriere din campurile unei linii din fisier
        campuri = linie.split(' ')
        client = Client(int(campuri[0]), None, None, 0)
        film = Film(int(campuri[1]), None, None, None, 0)
        client = self.__repoClienti.cauta_client(client)
        film = self.__repoFilme.cauta_film(film)
        inchiriere = Inchiriere(client, film)
        return inchiriere

    def __adauga_in_fisier(self, inchiriere):
        #functie care adauga o inchiriere in fiser
        with open(self.__nume_fisier, 'w') as f:
            clienti = self.get_all()
            for client in clienti:
                f.write(str(client.get_id()) + " " + client.get_nume() + " " + client.get_cnp())
                f.write('\n')

    def inchiriaza(self, inchiriere):
        #functie care adauga o inchiriere in fisier si in memorie
        RepoInchirieri.inchiriaza(self, inchiriere)
        self.__adauga_in_fisier(inchiriere)

    def __sterge_din_fisier(self):
        #functie care sterge o inchiriere din fisier
        with open(self.__nume_fisier, 'w') as f:
            inchirieri = self.get_all()
            for inchiriere in inchirieri:
                f.write(str(inchiriere.get_id_client()) + " " + str(inchiriere.get_id_film()))
                f.write('\n')

    def returneaza(self, inchiriere):
        #functie care terge o inchiriere din fisier si din memorie
        RepoInchirieri.returneaza(self, inchiriere)
        self.__sterge_din_fisier()