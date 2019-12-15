from Exceptii.exceptii import RepoError

class RepoHouse:

    def __init__(self):
        self.__lista_entitati = []

    def cauta(self, house):
        lista = []
        if house.get_id() != None:
            for h in self.__lista_entitati:
                if h.get_id() == house.get_id():
                    return h
        for h in self.__lista_entitati:
            if house.get_location() in h.get_location() and h.get_capacity() >= house.get_capacity():
                lista.append(h)
        return lista
        raise RepoError("Casa inexistenta!")

    def adauga(self, house):
        if self.id_in_list(house.get_id()):
            raise RepoError("Exista o casa cu acest Id!")
        self.__lista_entitati.append(house)

    def id_in_list(self, id_house):
        ok = False
        for house in self.__lista_entitati:
            if house.get_id() == id_house:
                ok = True
        return ok

    def empty(self):
        self.__lista_entitati = []

    def get_all(self):
        return self.__lista_entitati[:]
