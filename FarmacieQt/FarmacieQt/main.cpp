#include "repo.h"
#include "validator.h"
#include "service.h"
#include "console.h"
#include "ProductGUI.h"

void testAll() {
    testValidator();
    testRepoAdauga();
    testRepoSterge();
    testRepoModifica();
    testServiceAdauga();
    testServiceSterge();
    testServiceModifica();
    testServiceFiltru();
    testServiceSortare();
    testServiceReteta();
    testServiceSuma();
    testFileRepo();
    testUndo();
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    Repo repo;
    FileRepo fileRepo("farmacie.txt");
    Validator validator;
    Service service{ fileRepo, validator };
    ProductGUI gui{service};
    //Console ui{ service };

    //testAll();
    gui.show();
    //ui.start();
	return a.exec();
}


