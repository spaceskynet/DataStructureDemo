#include "utils.h"
#include <iostream>

using namespace std;

int main()
{
	Collection* c = new Collection();
	c->printBasicInfo();

    int pos;
    while (scanf("%d", &pos)) c->printBlockInfo(pos);

    c->printBlockInfoAll();
    
    c->input(LINKED_LIST);
    c->printBlockInfoAll();
    c->show(LINKED_LIST, 0);
    c->printBlockInfoAll();
    c->show(LINKED_LIST, 1);
    

    delete c;
	return EXIT_SUCCESS;
}
