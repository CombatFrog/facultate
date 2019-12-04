class Client:

    def __init__(self, id_client, nume, cnp, inchirieri):
        self.__id_client = id_client
        self.__nume = nume
        self.__cnp = cnp
        self.__inchirieri = inchirieri

    def get_id(self):
        return self.__id_client

    def get_nume(self):
        return self.__nume

    def get_cnp(self):
        return self.__cnp

    def get_inchirieri(self):
        return self.__inchirieri

    def set_nume(self, value):
        self.__nume = value

    def set_cnp(self, value):
        self.__cnp = value

    def inchiriaza(self):
        self.__inchirieri = self.__inchirieri + 1

    def returneaza(self):
        self.__inchirieri = self.__inchirieri - 1

    def __str__(self):
        return "Id: " + str(self.__id_client) + "\n" + "Nume: " + self.__nume + "\n" +"CNP: " + self.__cnp + "\n" + "Filme inchiriate: " + str(self.__inchirieri)

class Film:

    def __init__(self, id_film, titlu, descriere, gen, inchirieri):
        self.__id_film = id_film
        self.__titlu = titlu
        self.__descriere = descriere
        self.__gen = gen
        self.__inchirieri = inchirieri

    def get_id(self):
        return self.__id_film

    def get_titlu(self):
        return self.__titlu

    def get_descriere(self):
        return self.__descriere

    def get_gen(self):
        return self.__gen

    def get_inchirieri(self):
        return self.__inchirieri

    def set_titlu(self, value):
        self.__titlu = value

    def set_descriere(self, value):
        self.__descriere = value

    def set_gen(self, value):
        self.__gen = value

    def inchiriaza(self):
        self.__inchirieri = self.__inchirieri + 1

    def returneaza(self):
        self.__inchirieri = self.__inchirieri - 1

    def __str__(self):
        return "Id: " + str(self.__id_film) + "\n" + "Titlu: " + self.__titlu + "\n" + "Descriere: " + self.__descriere + "\n" + "Gen: " + self.__gen + "\n" + "Inchirieri: " + str(self.__inchirieri)

class Inchiriere:

    def __init__(self, client, film):
        self.__client = client
        self.__film = film

    def __str__(self):
        return "Id client: " + str(self.__client.get_id()) + "\n" + "Nume client: " + self.__client.get_nume() + "\n" + "Id film: " + str(self.__film.get_id()) + "\n" + "Ttlu film: " + self.__film.get_titlu()

    def get_film(self):
        return self.__film

    def get_id_film(self):
        film = self.get_film()
        return film.get_id()

    def get_client(self):
        return self.__client

    def get_id_client(self):
        client = self.get_client()
        return client.get_id()