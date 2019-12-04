from Exceptii.exceptii import ValidError, RepoError

class Consola:

    def __init__(self, srvClienti, srvFilme, srvInchirieri):
        self.__srvFilme = srvFilme
        self.__srvClienti = srvClienti
        self.__srvInchirieri = srvInchirieri
        self.__comenzi = {
            "add_client": self.__ui_adauga_client,
            "print_clienti": self.__ui_print_clienti,
            "modifica_client": self.__ui_modifica_client,
            "sterge_client": self.__ui_sterge_client,
            "cauta_client": self.__ui_cauta_client,

            "add_film": self.__ui_adauga_film,
            "print_filme": self.__ui_print_filme,
            "modifica_film":self.__ui_modifica_film,
            "sterge_film": self.__ui_sterge_film,
            "cauta_film": self.__ui_cauta_film,

            "inchiriaza": self.__ui_inchiriaza,
            "print_inchirieri": self.__ui_print_inchirieri,
            "returneaza": self.__ui_returneaza,

            "clienti_ordonati": self.__ui_clienti_ordonati,
            "cele_mai_inchiriate": self.__ui_cele_mai_inchiriate,
            "top30": self.__ui_top30,
            "cele_mai_slabe": self.__ui_cele_mai_slabe
        }

    def __ui_adauga_client(self, parametrii):
        if len(parametrii) != 3:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma add_client [id_client] [nume_client] [cnp_client]")
        id_client = int(parametrii[0])
        nume_client = parametrii[1]
        cnp_client = parametrii[2]
        self.__srvClienti.adauga_client(id_client, nume_client, cnp_client)

    def __ui_print_clienti(self, parametrii):
        if len(parametrii) != 0:
            raise ValueError("Comanda print_clienti nu accepta parametrii!")
        clienti = self.__srvClienti.get_clienti()
        for client in clienti:
            print(client)
            print("---------------------------------")

    def __ui_modifica_client(self, parametrii):
        if len(parametrii) != 3:
            raise ValueError(
                "Numarul parametrilor invalid!\nComanda este de forma modifica_client [id_client] [nume_nou] [cnp_nou]")
        id_client = int(parametrii[0])
        nume_nou = parametrii[1]
        cnp_nou = parametrii[2]
        self.__srvClienti.modifica_client(id_client, nume_nou, cnp_nou)

    def __ui_sterge_client(self, parametrii):
        if len(parametrii) != 1:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma sterge_client [id_client]")
        id_client = int(parametrii[0])
        self.__srvClienti.sterge_client(id_client)

    def __ui_adauga_film(self, parametrii):
        if len(parametrii) != 4:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma add_film [id_film] [titlu] [descriere] [gen]")
        id_film = int(parametrii[0])
        titlu = parametrii[1]
        descriere = parametrii[2]
        gen = parametrii[3]
        self.__srvFilme.adauga_film(id_film, titlu, descriere, gen)

    def __ui_print_filme(self, parametrii):
        if len(parametrii) != 0:
            raise ValueError("Comanda print_filme nu accepta parametrii!")
        filme = self.__srvFilme.get_filme()
        for film in filme:
            print(film)
            print("---------------------------------")

    def __ui_modifica_film(self, parametrii):
        if len(parametrii) != 4:
            raise ValueError(
                "Numarul parametrilor invalid!\nComanda este de forma modifica_film [id_film] [titlu_nou] [descriere_noua] [gen_nou]")
        id_film = int(parametrii[0])
        titlu_nou = parametrii[1]
        descriere_noua = parametrii[2]
        gen_nou = parametrii[3]
        self.__srvFilme.modifica_film(id_film, titlu_nou, descriere_noua, gen_nou)

    def __ui_sterge_film(self, parametrii):
        if len(parametrii) != 1:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma sterge_film [id_film]")
        id_film = int(parametrii[0])
        self.__srvFilme.sterge_film(id_film)

    def __ui_cauta_client(self, parametrii):
        if len(parametrii) != 2:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma cauta_client [tipul_cautarii] [valoarea_cautata]\nTipul cautarii: id, nume, cnp")
        tip_cautare = parametrii[0]
        valoare_cautata = parametrii[1]
        if tip_cautare == "id":
            print(self.__srvClienti.cauta_id(int(valoare_cautata)))
        elif tip_cautare == "nume":
            print(self.__srvClienti.cauta_nume(valoare_cautata))
        elif tip_cautare == "cnp":
            print(self.__srvClienti.cauta_cnp(valoare_cautata))
        else:
            raise ValueError("Tipul cautarii invalid!\Tipul cautarii: id, nume, cnp")

    def __ui_cauta_film(self, parametrii):
        if len(parametrii) != 2:
            raise ValidError("Numarul parametrilor invalid!\nComanda este de forma cauta_film [tipul_cautarii] [valoarea_cautata]\nTipul cautarii: id, nume")
        tip_cautare = parametrii[0]
        valoare_cautata = parametrii[1]
        if tip_cautare == "id":
            print(self.__srvFilme.cauta_id(int(valoare_cautata)))
        else:
            raise ValueError("Tipul cautarii invalid!\nTipul cautarii: id, nume")

    def __ui_inchiriaza(self, parametrii):
        if len(parametrii) != 2:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma inchiriaza [id_client] [id_film]")
        id_client = int(parametrii[0])
        id_film = int(parametrii[1])
        self.__srvInchirieri.inchiriaza(id_client, id_film)

    def __ui_print_inchirieri(self, parametrii):
        if len(parametrii) != 0:
            raise ValueError("Comanda print_inchirieri nu accepta parametrii!")
        inchirieri = self.__srvInchirieri.get_inchirieri()
        for inchiriere in inchirieri:
            print(inchiriere)
            print("---------------------------------")

    def __ui_returneaza(self, parametrii):
        if len(parametrii) != 2:
            raise ValueError("Numarul parametrilor invalid!\nComanda este de forma returneaza [id_client] [id_film]")
        id_client = int(parametrii[0])
        id_film = int(parametrii[1])
        self.__srvInchirieri.returneaza(id_client, id_film)

    def __ui_clienti_ordonati(self, parametrii):
        if len(parametrii) != 1:
            raise ValueError("Numarul parametrilor invalid!\nComanda este do forma clienti_ordonati [tipul_ordonarii]")
        if parametrii[0] == "nume":
            lista = self.__srvClienti.clienti_ordonati_nume()
            for client in lista:
                print(client)
                print("---------------------------------")
        elif parametrii[0] == "filme":
            lista = self.__srvClienti.clienti_ordonati_filme()
            for client in lista:
                print(client)
                print("---------------------------------")

    def __ui_cele_mai_inchiriate(self, parametrii):
        if len(parametrii) != 0:
            raise ValueError("Comanda cele_mai_inchiriate nu accepta parametrii!")
        lista = self.__srvFilme.cele_mai_inchiriate()
        for film in lista:
            print(film)
            print("---------------------------------")

    def __ui_cele_mai_slabe(self, parametrii):
        if len(parametrii) != 0:
            raise ValueError("Comanda cele_mai_slabe nu accepta parametrii!")
        lista = self.__srvFilme.cele_mai_slabe()
        for film in lista:
            print(film)
            print("---------------------------------")

    def __ui_top30(self, parametrii):
        if len(parametrii) != 0:
            raise ValueError("Comanda top30 nu accepta parametrii!")
        lista = self.__srvClienti.top30()
        for client in lista:
            print(client)
            print("---------------------------------")

    def run(self):
        while True:
            cmd = input(">> ")
            if len(cmd) >= 2:
                cmd = cmd.strip()
                if cmd == "exit":
                    return
                cmd = cmd.split()
                comanda = cmd[0]
                parametrii = cmd[1:]
                if comanda in self.__comenzi:
                    try:
                        self.__comenzi[comanda](parametrii)
                    except ValueError as vae:
                        print(str(vae))
                    except ValidError as ve:
                        print(str(ve))
                    except RepoError as re:
                        print(str(re))
                else:
                    print("comanda invalida!")