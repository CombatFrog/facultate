from Infrastructura.repos import RepoClienti, RepoFilme, RepoInchirieri
from Domain.entitati import Film, Client, Inchiriere
from Business.services import ServiceFilme, ServiceClienti, ServiceInchirieri
from Validare.validatoare import ValidFilme, ValidClienti, ValidInchirieri
from Exceptii.exceptii import ValidError, RepoError
import unittest

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


class TesteUnittest(unittest.TestCase):

    def setUp(self):
        unittest.TestCase.setUp(self)

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def testCreateClient(self):
        client1 = Client(1, "Ion", 5001229172347, 0)
        self.assertEqual(client1.get_id(), 1)
        self.assertEqual(client1.get_nume(), "Ion")
        self.assertEqual(client1.get_cnp(),5001229172347)
        client1.set_nume("Vasile")
        self.assertEqual(client1.get_nume(), "Vasile")
        client1.set_cnp(1231231231231)
        self.assertEqual(client1.get_cnp(), 1231231231231)
        self.__client = client1

    def testValidClient(self):
        validClient = ValidClienti()
        self.__client_id_invalid = Client(-1, "Ion", 1231231231231, 0)
        self.__client_nume_invalid = Client(1, "", 1231231231231, 0)
        self.__client_cnp_invalid1 = Client(1, "Ion", 1, 0)
        self.__client_cnp_invalid2 = Client(1, "Ion", 12345678901234, 0)
        with self.assertRaises(ValidError):
            validClient.validare_client(self.__client_id_invalid)
            validClient.validare_client(self.__client_nume_invalid)
            validClient.validare_client(self.__client_cnp_invalid1)
            validClient.validare_client(self.__client_cnp_invalid2)
        self.__validClient = validClient

    def testRepoClient(self):
        self.__repoClient = RepoClienti()
        self.__repoClient.adauga_client(self.__client)
        client = Client(1, "Vasile", 1234567890123, 0)
        client1 = Client(2, "Sorin", 1231231231231, 0)
        client3 = Client(1, None, None, 0)
        client4 = Client(None, "Vasile", None, 0)
        with self.assertRaises(RepoError):
            self.__repoClient.adauga_client(client)
        self.assertEqual(len(self.__repoClient.get_all()), 1)
        self.__repoClient.modifica_client(client)
        self.assertEqual(self.__client.get_nume(), "Vasile")
        self.assertEqual(self.__client.get_cnp(), 1234567890123)
        with self.assertRaises(RepoError):
            self.__repoClient.modifica_client(client1)
        x = self.__repoClient.cauta_client(client3)
        self.assertEqual(x, self.__client)
        x = self.__repoClient.cauta_client(client4)
        self.assertEqual(x, self.__client)
        with self.assertRaises(RepoError):
            self.__repoClient.cauta_client(client1)
        self.__repoClient.sterge_client(self.__client)
        with self.assertRaises(RepoError):
            self.__repoClient.sterge_client(client1)
        self.assertEqual(len(self.__repoClient.get_all()), 0)

    def testCreateFilm(self):
        film1 = Film(1, 'Titlu', 'Descriere', 'Gen', 0)
        self.assertEqual(film1.get_id(), 1)
        self.assertEqual(film1.get_titlu(), "Titlu")
        self.assertEqual(film1.get_descriere(), "Descriere")
        self.assertEqual(film1.get_gen(), "Gen")
        film1.set_titlu("AltTitlu")
        self.assertEqual(film1.get_titlu(), "AltTitlu")
        film1.set_descriere("AltaDescriere")
        self.assertEqual(film1.get_descriere(), "AltaDescriere")
        film1.set_gen("AltGen")
        self.assertEqual(film1.get_gen(), "AltGen")
        self.__film = film1

    def testValidFilm(self):
        validFilme = ValidFilme()
        self.__film_id_invalid = Film(-1, 'a', 'a','a', 0)
        self.__film_titlu_invalid = Film(1, '', 'a', 'a', 0)
        self.__film_descriere_invalida = Film(1, 'a', '', 'a', 0)
        self.__film_gen_invalid = Film(1, 'a', 'a', '', 0)
        with self.assertRaises(ValidError):
            validFilme.valideaza_film(self.__film_id_invalid)
            validFilme.valideaza_film(self.__film_titlu_invalid)
            validFilme.valideaza_film(self.__film_descriere_invalida)
            validFilme.valideaza_film(self.__film_gen_invalid)
        self.__validFilme = validFilme

    def testRepoFilme(self):
        self.__repoFilme = RepoFilme()
        self.__repoFilme.adauga_film(self.__film)
        film1 = Film(1, 'b', 'b', 'b', 0)
        film2 = Film(1, None, None, None, 0)
        film3 = Film(2, None, None, None, 0)
        with self.assertRaises(RepoError):
            self.__repoFilme.adauga_film(film1)
        self.assertEqual(len(self.__repoFilme.get_all()), 1)
        self.__repoFilme.modifica_film(film1)
        self.assertEqual(self.__film.get_titlu(), 'b')
        self.assertEqual(self.__film.get_descriere(), 'b')
        self.assertEqual(self.__film.get_gen(), 'b')
        with self.assertRaises(RepoError):
            self.__repoFilme.modifica_film(film3)
        x = self.__repoFilme.cauta_film(film2)
        self.assertEqual(x, self.__film)
        with self.assertRaises(RepoError):
            self.__repoFilme.cauta_film(film3)
        with self.assertRaises(RepoError):
            self.__repoFilme.sterge_film(film3)
        self.__repoFilme.sterge_film(film1)
        self.assertEqual(len(self.__repoFilme.get_all()), 0)

    def testRepoInchirieri(self):
        self.__repoInchirieri = RepoInchirieri()
        film1 = self.__film
        client1 = self.__client
        inchiriere = Inchiriere(film1, client1)
        self.__repoInchirieri.inchiriaza(inchiriere)
        self.assertEqual(len(self.__repoInchirieri.get_all()), 1)
        self.__repoInchirieri.returneaza(inchiriere)
        self.assertEqual(len(self.__repoInchirieri.get_all()), 0)





    def runAllTests(self):
        self.testCreateClient()
        self.testValidClient()
        self.testRepoClient()
        self.testCreateFilm()
        self.testValidFilm()
        self.testRepoFilme()
        self.testRepoInchirieri()
