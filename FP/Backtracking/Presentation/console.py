
class Consola:

    def __init__(self, backIter, backRec):
        self.__backIter = backIter
        self.__backRec = backRec

    def run(self):
        lista = input("Introduceti elementele listei separate printr-un spatiu: ")
        lista.strip()
        lista = lista.split()
        for i in range(len(lista)):
            lista[i] = int(lista[i])
        n = int(input("Introduceti un numar: "))
        self.__backIter.backIter(n, lista)
