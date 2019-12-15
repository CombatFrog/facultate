from Domain.entitati import House, Inchiriere

class ServiceHouse:

    def __init__(self, repoHouse):
        self.__repoHouse = repoHouse

    def cauta(self, location, capacity):
        house = House(None, None, location, capacity, None)
        return self.__repoHouse.cauta(house)

    def inchiriaza(self, id, zile):
        house = House(id, None, None, None, None)
        house = self.__repoHouse.cauta(house)
        pret = zile * house.get_price_per_night()
        inchiriere = Inchiriere(house, pret)
        return inchiriere

    def get_houses(self):
        self.__repoHouse.incarca_din_fisier()
        return self.__repoHouse.get_all()