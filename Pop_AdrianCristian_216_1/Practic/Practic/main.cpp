#include "GUI.h"

void teste()
{
   testRepo();
   testValidator();
   testService();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepo fileRepo("produse.txt");
    Validator validator;
    Service service{ fileRepo, validator };
    GUI gui{ service };
    gui.show();
    //teste();
    return a.exec();
}
