// src.cpp: 定义应用程序的入口点。
//

#include "Collection.h"
#include <iostream>

using namespace std;

int main()
{
    Collection* c = new Collection;
    c->printBasicInfo();

    int pos;
    while (scanf("%d", &pos)) c->printBlockInfo(pos);

    c->printBlockInfoAll();
    /*
    c->printBlockInfoAll();
    c->input(LINKED_LIST);
    c->printBlockInfoAll();
    c->show(LINKED_LIST, 0);
    c->printBlockInfoAll();
    c->show(LINKED_LIST, 1);
    */

    delete c;
	cout << "Hello CMake." << endl;
	return 0;
}
