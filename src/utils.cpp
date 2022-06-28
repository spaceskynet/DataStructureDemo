/**
 * @file utils.cpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief 各种数据结构的集合类的实现
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utils.h"
#include <QDebug>

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
 * @brief 在内存中重建文件模拟内存中的数据结构
 * 
 */
void Collection::rebuild()
{
    auto ds_list = part->dsBlockRealAddressList();
    if (ds_list.empty()) return; // 如果为空，说明模拟内存中无数据结构
    qDebug("从模拟内存中检测到数据结构对象，正在重建\n");
    signed_size_t offset = part->calcOffset();
    for (auto ds : ds_list)
    {
        DS_CLASS type = ds.first;
        void * real_addr = ds.second;
        singleRebuild(type, real_addr, offset);
    }
    qDebug("重建数据结构对象完毕\n", linked_list.size());
}

/**
 * @brief 对特定的数据结构重建
 * 
 * @param type 数据结构类型
 * @param real_addr 当前数据结构结构体对象在内存中的真实地址
 * @param offset 总的分配空间首地址相对上次运行的偏移（用于修正数据结构中的指针变量）
 */
void Collection::singleRebuild(DS_CLASS type, void* real_addr, signed_size_t offset)
{
    if (type == LINKED_LIST)
    {
        qDebug("正在重建索引为 %d 的链表对象\n", linked_list.size());
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
        if(linked_list.size() > index) linked_list[index]->defaultShow();
    }

    // more data structure
}

void Collection::init(DS_CLASS type, bool use_default)
{
    if(type == LINKED_LIST)
    {
        _qprintf(part, "\n正在创建索引为 %d 的链表对象……\n", linked_list.size());
        linkedList* l = (linkedList*)newMalloc(part, type, sizeof(linkedList));
        linked_list.push_back(l);
        part->dsBlockInsert(type, part->calcPos(l));

        if (use_default) l->defaultInput();
        else l->initList();
    }

    // more data structure
}

void Collection::del(DS_CLASS type, int index)
{
    if (type == LINKED_LIST)
    {
        if (linked_list.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的链表对象……\n", index);

        linked_list[index]->destoryList();

        part->dsBlockDelete(part->calcPos(linked_list[index]));
        newFree(part, linked_list[index]);
        linked_list.erase(linked_list.begin() + index);
    }

    // more data structure
}

void Collection::clearAll()
{
    linked_list.clear();

    // more
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


bool isNumber(const string& s)
{
    if(s.empty()) return false;
    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}