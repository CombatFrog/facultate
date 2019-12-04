from Exceptii.exceptii import ValidError

class ValidFilme:

    def valideaza_film(self, film):
        #functie care valideaza filmul film
        #input: film - un film
        #output: -
        #raises: ValidError
        erori = ""
        if int(film.get_id()) < 0:
            erori += "id invalid\n"
        if film.get_titlu() == "":
            erori += "nume invalid\n"
        if film.get_descriere() == "":
            erori += "descriere invalida\n"
        if film.get_gen() == "":
            erori += "gen invalid\n"
        if len(erori) > 0:
            raise ValidError(erori)

    def valideaza_titlu(self, titlu):
        #functie care valideaza titlul unui film
        #input: titlu - titlul unui film
        #output: -
        #raises: ValidError
        if titlu == "":
            raise ValidError("Titlu invalid!")

class ValidClienti:

    def validare_client(self, client):
        #functie care valideaza clientul client
        #input: client - un client
        #output: -
        #raises: ValidError
        erori = ""
        if int(client.get_id()) < 0:
            erori += "id invalid\n"
        if client.get_nume() == "":
            erori += "nume invalid\n"
        if int(client.get_cnp()) < 1000000000000 or int(client.get_cnp()) > 9999999999999:
            erori += "cnp invalid\n"
        if len(erori) > 0:
            raise ValidError(erori)

    def validare_id(self, id_client):
        #functie care valideaza idul unui client
        #input: id_client - idul unui client
        #output: -
        #raises: ValidError
        erori = ""
        if int(id_client) < 0:
            erori += "id invalid\n"
        if len(erori) > 0:
            raise ValidError(erori)

    def validare_nume(self, nume_client):
        #functie care valideaza numele unui client
        #input: nume_client - numele unui client
        #output: -
        #raises: ValidError
        if nume_client == "":
            raise ValidError("Nume invalid")

    def validare_cnp(self, cnp_client):
        #functie care valideaza cnpul unui client
        #input: cnp_client - cnpul unui client
        #output: -
        #raises: ValidError
        if int(cnp_client) < 1000000000000 or int(cnp_client) > 9999999999999:
            raise ValidError("CNP invalid!")
class ValidInchirieri:
    pass