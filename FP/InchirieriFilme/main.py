from Teste.teste import Teste
from Infrastructura.repos import RepoClienti, RepoFilme, RepoInchirieri
from Infrastructura.fileRepos import RepoFilmeFromFile, RepoClientiFromFile, RepoInchirieriFromFile
from Validare.validatoare import ValidFilme, ValidClienti, ValidInchirieri
from Business.services import ServiceFilme, ServiceClienti, ServiceInchirieri
from Presentation.console import Consola


repoFilme = RepoFilmeFromFile("filme")
repoClienti = RepoClientiFromFile("clienti")
repoInchirieri = RepoInchirieriFromFile("inchirieri", repoClienti, repoFilme)
validFilme = ValidFilme()
validClienti = ValidClienti()
validInchirieri = ValidInchirieri()
srvFilme = ServiceFilme(repoFilme, validFilme)
srvClienti = ServiceClienti(repoClienti, validClienti)
srvInchirieri = ServiceInchirieri(repoInchirieri, validInchirieri, repoClienti, repoFilme)
ui = Consola(srvClienti, srvFilme, srvInchirieri)
teste = Teste()

def main():
    teste.run_all_tests()
    ui.run()


main()
