#include "DataStructureDemo.h"

int main()
{
    Collection* c = new Collection;
    
    c->input(LINKED_LIST);
    c->show(LINKED_LIST, 0);
    c->show(LINKED_LIST, 1);
    c->del(LINKED_LIST, 1);

    delete c;
	return 0;
}

Collection::Collection()
{
    part = new PartitionIO;

    linkedList::part = part;
    part->readFile();
    rebuild();
}

Collection::~Collection()
{
//    part->writeFile();
    delete part;
}

void Collection::rebuild()
{
    auto ds_list = part->dsBlockRealAddressList();
    if (ds_list.empty()) return;
    signed_size_t offset = part->calcOffset();
    for (auto ds : ds_list)
    {
        DS_CLASS type = ds.first;
        void * real_addr = ds.second;
        singleRebuild(type, real_addr, offset);
    }
}

void Collection::singleRebuild(DS_CLASS type, void* real_addr, signed_size_t offset)
{
    switch (type)
    {
    case LINKED_LIST:
        linkedList* l = (linkedList*)real_addr;
        linked_list.push_back(l);
        l->recovery(offset);
        break;
    }
}

void Collection::show(DS_CLASS type, int index)
{
    if (type == LINKED_LIST)
    {
        if(linked_list.size() > index) linked_list[index]->show();
    }
}

void Collection::input(DS_CLASS type)
{
    if(type == LINKED_LIST)
    {
        linkedList* l = (linkedList*)newMalloc(part, type, sizeof(linkedList));
        linked_list.push_back(l);
        part->dsBlockInsert(type, part->calcPos(l));

        l->initInput();
    }
}

void Collection::del(DS_CLASS type, int index)
{
    if (type == LINKED_LIST)
    {
        if (linked_list.size() <= index) return;
        linked_list[index]->destoryList();

        part->dsBlockDelete(part->calcPos(linked_list[index]));
        newFree(part, linked_list[index]);
        linked_list.erase(linked_list.begin() + index);
    }
}
