from Exceptii.exceptii import ValidError, RepoError

class Consola:

    def __init__(self, srvHouse):
        self.__srvHouse = srvHouse
        self.__comenzi = {
            "cauta" : self.__ui_cauta,
            "inchiriaza" : self.__ui_inchiriaza
        }


    def __ui_cauta(self, parametrii):
        if len(parametrii) != 2:
            raise ValueError("Numarul parametrilor invalid!")
        location = parametrii[0]
        capacity = int(parametrii[1])
        houses = self.__srvHouse.cauta(location, capacity)
        for house in houses:
            print(house)
            print("--------------------------")

    def __ui_inchiriaza(self, parametrii):
        if len(parametrii) != 2:
            raise ValueError("Numarul parametrilor invalid!")
        id = int(parametrii[0])
        zile = int(parametrii[1])
        inciriere =  self.__srvHouse.inchiriaza(id, zile)
        print(inciriere)
        print("--------------------------")

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