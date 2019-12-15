from Infrastructura.repos import RepoHouse
from Domain.entitati import House

class RepoHouseFile(RepoHouse):


    def __init__(self, nume_fisier):
        RepoHouse.__init__(self)
        self.__nume_fisier = nume_fisier
        self.incarca_din_fisier()


    def __creeaza_house(self, linie):
        campuri = linie.split(',')
        house = House(int(campuri[0]), campuri[1], campuri[2], int(campuri[3]), int(campuri[4]))
        return house

    def incarca_din_fisier(self):
        RepoHouse.empty(self)
        f = open(self.__nume_fisier)
        continut = f.read()
        f.close()
        linii = continut.split('\n')
        for linie in linii:
            if linie.strip() == '':
                continue
            house = self.__creeaza_house(linie)
            RepoHouse.adauga(self, house)