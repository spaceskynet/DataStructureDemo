#include "utils.h"
#include "gui.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication App(argc, argv);
    auto window = std::make_unique<MainWindow>(&App);
    window->show();
    return App.exec();
}
