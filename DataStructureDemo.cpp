/**
 * @file DataStructureDemo.cpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief �������ݽṹ�ļ��ϵĲ������ʵ��
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "DataStructureDemo.h"

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
    part->writeFile();
    delete part;
}

/**
 * @brief ���ڴ����ؽ��ļ�ģ���ڴ��е����ݽṹ
 * 
 */
void Collection::rebuild()
{
    auto ds_list = part->dsBlockRealAddressList();
    if (ds_list.empty()) return; // ���Ϊ�գ�˵��ģ���ڴ��������ݽṹ
    signed_size_t offset = part->calcOffset();
    for (auto ds : ds_list)
    {
        DS_CLASS type = ds.first;
        void * real_addr = ds.second;
        singleRebuild(type, real_addr, offset);
    }
}

/**
 * @brief ���ض������ݽṹ�ؽ�
 * 
 * @param type ���ݽṹ����
 * @param real_addr ��ǰ���ݽṹ�ṹ��������ڴ��е���ʵ��ַ
 * @param offset �ܵķ���ռ��׵�ַ����ϴ����е�ƫ�ƣ������������ݽṹ�е�ָ�������
 */
void Collection::singleRebuild(DS_CLASS type, void* real_addr, signed_size_t offset)
{
    if (type == LINKED_LIST)
    {
        linkedList* l = (linkedList*)real_addr;
        linked_list.push_back(l);
        l->recovery(offset);
    }

    // more data structure
}

void Collection::show(DS_CLASS type, int index)
{
    if (type == LINKED_LIST)
    {
        if(linked_list.size() > index) linked_list[index]->show();
    }

    // more data structure
}

void Collection::input(DS_CLASS type)
{
    if(type == LINKED_LIST)
    {
        linkedList* l = (linkedList*)newMalloc(part, type, sizeof(linkedList));
        linked_list.push_back(l);
        part->dsBlockInsert(type, part->calcPos(l));

        l->init();
    }

    // more data structure
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

    // more data structure
}

void Collection::printBasicInfo()
{
    part->printBasicInfo();
}

void Collection::printBlockInfo(unsigned int pos)
{
    part->printBlockInfo(pos);
}

void Collection::printBlockInfoAll()
{
    part->printBlockInfoAll();
}
