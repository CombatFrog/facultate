from Domain.entitati import Film, Client, Inchiriere

class ServiceClienti:

    def __init__(self, repoClienti, validClienti):
        self.__repoClienti = repoClienti
        self.__validClienti = validClienti

    def adauga_client(self, id_client, nume, cnp):
        #functia care adauga un client nou in lista de clienti
        #input: id_client, nume, cnp
        #output: clientul cu idul id_client, numele nume si cnpul cnp este adaugat in lista de clienti
        client = Client(id_client, nume, cnp, 0)
        self.__validClienti.validare_client(client)
        self.__repoClienti.adauga_client(client)

    def modifica_client(self, id_client, nume_nou, cnp_nou):
        #functie care modifica un client
        #input: idul clientului care va fi modificat, noul nume, noul cnp
        #output: clientul cu idul id_client va primi numele nume_nou si cnpul cnp_nou
        client = Client(id_client, nume_nou, cnp_nou, 0)
        self.__validClienti.validare_client(client)
        self.__repoClienti.modifica_client(client)

    def sterge_client(self, id_client):
        #functie care sterge clientul cu idul id_client din lista de clienti
        #input: id_client - idul clientului care va fi sters
        #output: clientul cu idul id_client va fi sters din lista de clienti
        client = Client(id_client, None, None, 0)
        self.__validClienti.validare_id(id_client)
        self.__repoClienti.sterge_client(client)

    def cauta_id(self, id_client):
        #functie care cauta un client dupa id
        #input: id_client - idul clientului cautat
        #output: clientul cu idul id_client
        client = Client(id_client, None, None, 0)
        self.__validClienti.validare_id(id_client)
        return self.__repoClienti.cauta_client(client)

    def cauta_nume(self, nume_client):
        #fuctie care cauta un client dupa nume
        #input: nume_client - numele clientului cautat
        #output: clientul cu numele nume_client
        client = Client(None, nume_client, None, 0)
        self.__validClienti.validare_nume(nume_client)
        return self.__repoClienti.cauta_client(client)

    def cauta_cnp(self, cnp_client):
        #functie care cauta un client dupa cnp
        #input: cnp_client - cnpul clientului cautat
        #output: clientul cu cnpul cnp_client
        client = Client(None, None, cnp_client, 0)
        self.__validClienti.validare_cnp(cnp_client)
        return self.__repoClienti.cauta_client(client)

    def get_clienti(self):
        #functia care returneaza o lista cu toti clientii
        return self.__repoClienti.get_all()

    def clienti_ordonati_nume(self):
        #functie care returneaza lista clientilor ordonata dupa numel clientilor
        lista_nume = []
        lista_ordonata = []
        lista_clienti = self.get_clienti()
        for client in lista_clienti:
            lista_nume.append(client.get_nume())
        lista_nume.sort()
        for nume in lista_nume:
            client = self.cauta_nume(nume)
            lista_ordonata.append(client)
        return lista_ordonata

    def clienti_ordonati_filme(self):
        #functie care returneaza lista de clienti ordonata dupa numarul filmelor inchiriate
        lista_clienti = self.get_clienti()
        ok = False
        while ok is False:
            ok = True
            for i in range(len(lista_clienti) - 1):
                if lista_clienti[i].get_inchirieri() > lista_clienti[i+1].get_inchirieri():
                    temp = lista_clienti[i]
                    lista_clienti[i] = lista_clienti[i+1]
                    lista_clienti[i+1] = temp
                    ok = False
        return lista_clienti

    def top30(self):
        #functie care afiseaza primii 30% clienti dupa numarul de filme inchiriate
        lista = self.clienti_ordonati_filme()
        lista.reverse()
        final = []
        total = 0
        for client in lista:
            total = total + client.get_inchirieri()
        total = total / 100
        total = total * 30
        if int(total) < 1:
            return lista[0]
        else:
            for n in range(int(total)):
                final.append(lista[n])
        return final


class ServiceFilme:

    def __init__(self, repoFilme, validFilme):
        self.__repoFilme = repoFilme
        self.__validFilme = validFilme

    def adauga_film(self, id_film, titlu, descriere, gen):
        #functie care adauga un film in lista de filme
        #input: id_film, titlul filmului, descrierea filmului, genul filmului
        #output: clientul este adaugat in lista de clienti
        self.__repoFilme.incarca_din_fisier()
        film = Film(id_film, titlu, descriere, gen, 0)
        self.__validFilme.valideaza_film(film)
        self.__repoFilme.adauga_film(film)

    def modifica_film(self, id_film, titlu_nou, descriere_noua, gen_nou):
        #functie care modifica titlul, descrierea si genul unui film
        #input: id_film -idul fimului care va fi modificat, noul titlu, noua descriere, noul gen
        #output: filmul cu idul id_film primeste titlul titlu_nou, descrierea descreire_noua si genul gen_nou
        self.__repoFilme.incarca_din_fisier()
        film = Film(id_film, titlu_nou, descriere_noua, gen_nou, 0)
        self.__validFilme.valideaza_film(film)
        self.__repoFilme.modifica_film(film)

    def sterge_film(self, id_film):
        #functie care sterge filmul cu idul id_film din lista de filme
        #input: id_film - idul filmului care va fi sters
        #output: filmul cu idul id_film este sters din lista de filme
        self.__repoFilme.incarca_din_fisier()
        film = Film(id_film, None, None, None, 0)
        self.__validFilme.valideaza_film(film)
        self.__repoFilme.sterge_film(film)

    def cauta_id(self, id_film):
        #functie care returneaza filmul cu idul id_film
        #input: id_film - idul filmului cautat
        #output: filmul cu idul id_film
        self.__repoFilme.incarca_din_fisier()
        film = Film(id_film, None, None, None, 0)
        self.__validFilme.valideaza_film(film)
        return self.__repoFilme.cauta_film(film)

    def cele_mai_inchiriate(self):
        #functie care returneaza lista de filme ordoata descrescator dupa numarul de inchirieri
        self.__repoFilme.incarca_din_fisier()
        lista_filme = self.get_filme()
        ok = False
        while ok is False:
            ok = True
            for i in range(len(lista_filme) - 1):
                if lista_filme[i].get_inchirieri() > lista_filme[i + 1].get_inchirieri():
                    temp = lista_filme[i]
                    lista_filme[i] = lista_filme[i + 1]
                    lista_filme[i + 1] = temp
                    ok = False
        lista_filme.reverse()
        return lista_filme

    def cele_mai_slabe(self):
        #functie care returneaza lista de filme ordonata crescator dupa numarul filmelor inchiriate
        #daca numarul inchirierilor este egal, filmele sunt ordonate alfabetic dupa titlu
        self.__repoFilme.incarca_din_fisier()
        lista_filme = self.get_filme()
        ok = False
        while ok is False:
            ok = True
            for i in range(len(lista_filme) - 1):
                if lista_filme[i].get_inchirieri() < lista_filme[i + 1].get_inchirieri():
                    temp = lista_filme[i]
                    lista_filme[i] = lista_filme[i + 1]
                    lista_filme[i + 1] = temp
                    ok = False
                elif lista_filme[i].get_inchirieri() == lista_filme[i + 1].get_inchirieri():
                    if lista_filme[i].get_titlu() < lista_filme[i + 1].get_titlu():
                        temp = lista_filme[i]
                        lista_filme[i] = lista_filme[i + 1]
                        lista_filme[i + 1] = temp
        lista_filme.reverse()
        return lista_filme


    def get_filme(self):
        #functie care returneaza lista de filme
        self.__repoFilme.incarca_din_fisier()
        return self.__repoFilme.get_all()

class ServiceInchirieri:

    def __init__(self, repoInchirieri, validInchirieri, repoClienti, repoFilme):
        self.__repoInchirieri = repoInchirieri
        self.__validInchirieri = validInchirieri
        self.__repoClienti = repoClienti
        self.__repoFilme = repoFilme

    def inchiriaza(self, id_client, id_film):
        #functie in care clientul cu idul id_client inchiriaza filmul cu idul id_film
        #input: id_client - idul clientului care inchiriaza, id_film - idul filmului care este inchiriat
        #output: inchirierea este adaugata la lista de inchirieri
        client = Client(id_client, None, None, 0)
        film = Film(id_film, None, None, None, 0)
        client = self.__repoClienti.cauta_client(client)
        film = self.__repoFilme.cauta_film(film)
        inchiriere = Inchiriere(client, film)
        self.__repoInchirieri.inchiriaza(inchiriere)

    def returneaza(self, id_client, id_film):
        #functie in care  clientul cu idul id_client returneaza filmul cu idul id_film
        #input: id_client - idul clientului care returneaza un film, id_film - idul filmului returnat
        #output: filmul cu idul id_film, inchiriat de clientul cu idul id_client este sters din lista de inchirieri
        client = Client(id_client, None, None, 0)
        film = Film(id_film, None, None, None, 0)
        client = self.__repoClienti.cauta_client(client)
        film = self.__repoFilme.cauta_film(film)
        inchiriere = Inchiriere(client, film)
        self.__repoInchirieri.returneaza(inchiriere)

    def get_inchirieri(self):
        #functie care returneaza lista de inchirieri
        return self.__repoInchirieri.get_all()