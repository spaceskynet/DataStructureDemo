/**
 * @file main.cpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief 程序入口点
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "gui.h"

int main(int argc, char* argv[])
{
    QApplication App(argc, argv);
    auto window = std::make_unique<MainWindow>(&App);
    window->show();
    return App.exec();
}
