from Infrastructura.repos import RepoClienti, RepoFilme, RepoInchirieri
from Domain.entitati import Film, Client, Inchiriere
from Business.services import ServiceFilme, ServiceClienti, ServiceInchirieri
from Validare.validatoare import ValidFilme, ValidClienti, ValidInchirieri

class Teste():

    def __test_creeaza_film(self):
        film = Film(1, 'a', 'a', 'a', 0)
        assert (film.get_id() == 1)
        assert (film.get_titlu() == 'a')
        assert (film.get_descriere() == 'a')
        assert (film.get_gen() == 'a')
        assert (film.get_inchirieri() == 0)
        film.set_titlu('b')
        assert (film.get_titlu() == 'b')
        film.set_descriere('b')
        assert (film.get_descriere() == 'b')
        film.set_gen('b')
        assert (film.get_gen() == 'b')

    def __test_creeaza_client(self):
        client = Client(1, 'a', 1234567890123, 0)
        assert (client.get_id() == 1)
        assert (client.get_nume() == 'a')
        assert (client.get_cnp() == 1234567890123)
        assert (client.get_inchirieri() == 0 )
        client.set_nume('b')
        assert (client.get_nume() == 'b')
        client.set_cnp(2234567890123)
        assert (client.get_cnp() == 2234567890123)

    def __test_creeaza_inchiriere(self):
        film = Film(1, 'a', 'a', 'a', 0)
        client = Client(1, 'a', 1234567890123, 0)
        inchiriere = Inchiriere(client, film)
        assert (inchiriere.get_client() == client)
        assert (inchiriere.get_film() == film)
        assert (inchiriere.get_id_client() == client.get_id())
        assert (inchiriere.get_id_film() == film.get_id())

    def __test_adauga_client(self):
        client = Client(1, 'a', 1234567890123, 0)
        testRepoCLient = RepoClienti()
        testRepoCLient.adauga_client(client)
        lista = testRepoCLient.get_all()
        assert (len(lista) == 1)

    def __test_adauga_film(self):
        film = Film(1, 'a', 'a', 'a', 0)
        testRepoFilme = RepoFilme()
        testRepoFilme.adauga_film(film)
        lista = testRepoFilme.get_all()
        assert (len(lista) == 1)

    def __test_modifica_client(self):
        client = Client(1, 'a', 1234567890123, 0)
        testRepoCLient = RepoClienti()
        testRepoCLient.adauga_client(client)
        testValidClienti = ValidClienti()
        testServiceClient = ServiceClienti(testRepoCLient, testValidClienti)
        testServiceClient.modifica_client(1, 'b', 1231231231231)
        assert (client.get_id() == 1)
        assert (client.get_nume() == 'b')
        assert (client.get_cnp() == 1231231231231)

    def __test_modifica_film(self):
        film = Film(1, 'a', 'a', 'a', 0)
        testRepoFilme = RepoFilme()
        testRepoFilme.adauga_film(film)
        testValidFilme = ValidFilme()
        testServiceFilme = ServiceFilme(testRepoFilme, testValidFilme)
        testServiceFilme.modifica_film(1, 'b', 'b', 'b')
        assert (film.get_id() == 1)
        assert (film.get_titlu() == 'b')
        assert (film.get_descriere() == 'b')
        assert (film.get_gen() == 'b')

    def __test_sterge_client(self):
        client = Client(1, 'a', 1234567890123, 0)
        testRepoCLient = RepoClienti()
        testRepoCLient.adauga_client(client)
        testRepoCLient.sterge_client(client)
        lista = testRepoCLient.get_all()
        assert (len(lista) == 0)

    def __test_sterge_film(self):
        film = Film(1, 'a', 'a', 'a', 0)
        testRepoFilme = RepoFilme()
        testRepoFilme.adauga_film(film)
        testRepoFilme.sterge_film(film)
        lista = testRepoFilme.get_all()
        assert (len(lista) == 0)

    def __test_inchiriaza(self):
        film = Film(1, 'a', 'a', 'a', 0)
        client = Client(1, 'a', 1234567890123, 0)
        inchiriere = Inchiriere(client, film)
        testRepoInchiriere = RepoInchirieri()
        testRepoInchiriere.inchiriaza(inchiriere)
        lista = testRepoInchiriere.get_all()
        assert (len(lista) == 1)

    def __test_returneaza(self):
        film = Film(1, 'a', 'a', 'a', 0)
        client = Client(1, 'a', 1234567890123, 0)
        inchiriere = Inchiriere(client, film)
        testRepoInchiriere = RepoInchirieri()
        testRepoInchiriere.inchiriaza(inchiriere)
        testRepoInchiriere.returneaza(inchiriere)
        lista = testRepoInchiriere.get_all()
        assert (len(lista) == 0)

    def run_all_tests(self):
        self.__test_creeaza_film()
        self.__test_creeaza_client()
        self.__test_creeaza_inchiriere()
        self.__test_adauga_client()
        self.__test_adauga_film()
        self.__test_modifica_client()
        self.__test_modifica_film()
        self.__test_sterge_client()
        self.__test_sterge_film()
        self.__test_inchiriaza()
        self.__test_returneaza()