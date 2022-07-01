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
    myArray::part = part;
    myStack::part = part;
    myHeap::part = part;
    myTree::part = part;
    undirectionGraph::part = part;
    directionGraph::part = part;
    // more data structure

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
    for (auto &ds : ds_list)
    {
        DS_CLASS type = ds.first;
        void * real_addr = ds.second;
        singleRebuild(type, real_addr, offset);
    }
    qDebug("重建数据结构对象完毕\n");
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
    if (type == ARRAY)
    {
        qDebug("正在重建索引为 %d 的数组对象\n", my_array.size());
        myArray* arr = (myArray*)real_addr;
        my_array.push_back(arr);
        arr->recovery(offset);
    }
    if (type == STACK)
    {
        qDebug("正在重建索引为 %d 的栈对象\n", my_stack.size());
        myStack* s = (myStack*)real_addr;
        my_stack.push_back(s);
        s->recovery(offset);
    }
    if (type == HEAP)
    {
        qDebug("正在重建索引为 %d 的堆对象\n", my_heap.size());
        myHeap* h = (myHeap*)real_addr;
        my_heap.push_back(h);
        h->recovery(offset);
    }
    if (type == TREE)
    {
        qDebug("正在重建索引为 %d 的树对象\n", my_tree.size());
        myTree* t = (myTree*)real_addr;
        my_tree.push_back(t);
        t->recovery(offset);
    }
    if (type == UNDIRECTED_GRAPH)
    {
        qDebug("正在重建索引为 %d 的无向图对象\n", undirection_graph.size());
        undirectionGraph* ug = (undirectionGraph*)real_addr;
        undirection_graph.push_back(ug);
        ug->recovery(offset);
    }
    if (type == DIRECTED_GRAPH)
    {
        qDebug("正在重建索引为 %d 的有向图对象\n", direction_graph.size());
        directionGraph* dg = (directionGraph*)real_addr;
        direction_graph.push_back(dg);
        dg->recovery(offset);
    }
    // more data structure
}

/**
 * @brief 初始化特定的数据结构
 * 
 * @param type 
 * @param use_default 是否使用默认的测试数据初始化
 */
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

    if (type == ARRAY)
    {
        _qprintf(part, "\n正在创建索引为 %d 的数组对象……\n", my_array.size());
        myArray* arr = (myArray*)newMalloc(part, type, sizeof(myArray));
        my_array.push_back(arr);
        part->dsBlockInsert(type, part->calcPos(arr));

        if (use_default) arr->input();
        else arr->init();
    }

    if (type == STACK)
    {
        _qprintf(part, "\n正在创建索引为 %d 的栈对象……\n", my_stack.size());
        myStack* s = (myStack*)newMalloc(part, type, sizeof(myStack));
        my_stack.push_back(s);
        part->dsBlockInsert(type, part->calcPos(s));

        if (use_default) s->Input();
        else s->Init();
    }

    if (type == HEAP)
    {
        _qprintf(part, "\n正在创建索引为 %d 的堆对象……\n", my_heap.size());
        myHeap* h = (myHeap*)newMalloc(part, type, sizeof(myHeap));
        my_heap.push_back(h);
        part->dsBlockInsert(type, part->calcPos(h));

        if (use_default) h->Input();
        else h->Init(true);
    }
    
    if (type == TREE)
    {
        _qprintf(part, "\n正在创建索引为 %d 的树对象……\n", my_tree.size());
        myTree* t = (myTree*)newMalloc(part, type, sizeof(myTree));
        my_tree.push_back(t);
        part->dsBlockInsert(type, part->calcPos(t));

        if (use_default) t->input();
        else t->create();
    }

    if (type == UNDIRECTED_GRAPH)
    {
        _qprintf(part, "\n正在创建索引为 %d 的无向图对象……\n", undirection_graph.size());
        undirectionGraph* ug = (undirectionGraph*)newMalloc(part, type, sizeof(undirectionGraph));
        undirection_graph.push_back(ug);
        part->dsBlockInsert(type, part->calcPos(ug));

        if (use_default) ug->load_default();
        else ug->init_graph();
    }

    if (type == DIRECTED_GRAPH)
    {
        _qprintf(part, "\n正在创建索引为 %d 的有向图对象……\n", direction_graph.size());
        directionGraph* dg = (directionGraph*)newMalloc(part, type, sizeof(directionGraph));
        direction_graph.push_back(dg);
        part->dsBlockInsert(type, part->calcPos(dg));

        if (use_default) dg->load_default();
        else dg->init_graph();
    }
    // more data structure
}

/**
 * @brief 销毁特定的数据结构
 * 
 * @param type 
 * @param index 数据结构对象的索引
 */
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
    if (type == ARRAY)
    {
        if (my_array.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的数组对象……\n", index);

        my_array[index]->destroy();

        part->dsBlockDelete(part->calcPos(my_array[index]));
        newFree(part, my_array[index]);
        my_array.erase(my_array.begin() + index);
    }
    if (type == STACK)
    {
        if (my_stack.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的栈对象……\n", index);

        my_stack[index]->DestroyStack();

        part->dsBlockDelete(part->calcPos(my_stack[index]));
        newFree(part, my_stack[index]);
        my_stack.erase(my_stack.begin() + index);
    }
    if (type == HEAP)
    {
        if (my_heap.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的堆对象……\n", index);

        my_heap[index]->HeapDestroy();

        part->dsBlockDelete(part->calcPos(my_heap[index]));
        newFree(part, my_heap[index]);
        my_heap.erase(my_heap.begin() + index);
    }
    if (type == TREE)
    {
        if (my_tree.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的树对象……\n", index);

        my_tree[index]->destroy();

        part->dsBlockDelete(part->calcPos(my_tree[index]));
        newFree(part, my_tree[index]);
        my_tree.erase(my_tree.begin() + index);
    }
    if (type == UNDIRECTED_GRAPH)
    {
        if (undirection_graph.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的无向图对象……\n", index);

        undirection_graph[index]->destroy_graph();

        part->dsBlockDelete(part->calcPos(undirection_graph[index]));
        newFree(part, undirection_graph[index]);
        undirection_graph.erase(undirection_graph.begin() + index);
    }
    if (type == DIRECTED_GRAPH)
    {
        if (direction_graph.size() <= index) return;
        _qprintf(part, "\n正在销毁索引为 %d 的有向图对象……\n", index);

        direction_graph[index]->destroy_graph();

        part->dsBlockDelete(part->calcPos(direction_graph[index]));
        newFree(part, direction_graph[index]);
        direction_graph.erase(direction_graph.begin() + index);
    }
    // more data structure
}

/**
 * @brief 清空所有数据结构对象的指针
 * 
 */
void Collection::clearAll()
{
    linked_list.clear();
    my_array.clear();
    my_stack.clear();
    my_heap.clear();
    my_tree.clear();
    undirection_graph.clear();
    direction_graph.clear();

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
