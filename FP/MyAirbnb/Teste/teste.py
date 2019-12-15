from Domain.entitati import House, Inchiriere
from Infrastructura.repos import RepoHouse
from Business.services import ServiceHouse

class Teste():

    def test_creeaza_casa(self):
        house = House(4, "Casa Diana", "Bistrita", 3, 150)
        assert (house.get_id() == 4)
        assert (house.get_name() == "Casa Diana")
        assert (house.get_location() == "Bistrita")
        assert (house.get_capacity() == 3)
        assert (house.get_price_per_night() == 150)

    def test_adauga_casa(self):
        repoHouse = RepoHouse()
        house = House(4, "Casa Diana", "Bistrita", 3, 150)
        house1 = House(3, "Casa Diana", "Bistrita", 3, 150)
        repoHouse.adauga(house)
        assert (len(repoHouse.get_all()) == 1)
        repoHouse.adauga(house1)
        assert (len(repoHouse.get_all()) == 2)

    def test_creeaza_inchiriere(self):
        house = House(4, "Casa Diana", "Bistrita", 3, 150)
        price = 300
        inchiriere = Inchiriere(house, price)
        assert (inchiriere.get_nume() == "Casa Diana")
        assert (inchiriere.get_price() == 300)

    def test_get_all(self):
        repoHouse = RepoHouse()
        house = House(4, "Casa Diana", "Bistrita", 3, 150)
        house1 = House(3, "Casa Diana", "Bistrita", 3, 150)
        repoHouse.adauga(house)
        repoHouse.adauga(house1)
        assert (repoHouse.get_all() == [house, house1])


    def test_srv_cauta(self):
        location = "Bi"
        capacity = 3
        repoHouse = RepoHouse()
        house1 = House(4, "Casa Diana", "Bistrita", 3, 150)
        repoHouse.adauga(house1)
        srv = ServiceHouse(repoHouse)
        h = srv.cauta(location, capacity)
        assert (h[0] == house1)

    def test_srv_inchiriaza(self):
        id = 4
        zile = 3
        repoHouse = RepoHouse()
        house1 = House(4, "Casa Diana", "Bistrita", 3, 150)
        repoHouse.adauga(house1)
        srv = ServiceHouse(repoHouse)
        inchiriere = srv.inchiriaza(id, zile)
        assert (inchiriere.get_nume() == "Casa Diana")
        assert (inchiriere.get_price() == 450)


    def run_all(self):
        self.test_creeaza_casa()
        self.test_adauga_casa()
        self.test_creeaza_inchiriere()
        self.test_get_all()
        self.test_srv_cauta()
        self.test_srv_inchiriaza()