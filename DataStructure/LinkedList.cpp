//By: SpaceSkyNet
#include "LinkedList.h"

PartitionIO* linkedList::part = nullptr;

pNode linkedList::initList()
{
    return newNode(-1);
}
pNode linkedList::newNode(elemType data)
{
    pNode elem = (pNode)_malloc(sizeof(Node));
    if(elem == nullptr) exit(-1);
    elem->data = data, elem->next = nullptr;
    return elem;
}
void linkedList::destoryList()
{
    clearList();
    _free(head);
}
void linkedList::clearList()
{
    while(head->next != nullptr) del(1);
}
bool linkedList::isEmpty()
{
    return head->next == nullptr;
}
int linkedList::listLength()
{
    pNode p = head;
    int cnt = 0;
    while(p->next != nullptr) ++cnt, p = p->next;
    return cnt;
}
pNode linkedList::getElem(int pos)
{
    pNode p = head;
    for(int i = 1; i <= pos && p != nullptr; i++) p = p->next;
    return p;
}
int linkedList::locateElem(elemType val, bool(*cmp)(elemType, elemType))
{
    pNode p = head;
    for(int i = 1; p->next != nullptr; i++)
    {
        p = p->next;
        if(cmp(p->data, val)) return i;
    }
    return -1;
}
pNode linkedList::elemPre(pNode elem)
{
    pNode p = head;
    while(p != nullptr && p->next != elem) p = p->next;
    if(p == nullptr || p == head) return nullptr;
    else return p;
}
pNode linkedList::elemNext(pNode elem)
{
    pNode p = head;
    while(p != nullptr && p != elem) p = p->next;
    // p->next == NULL can be merged to `else`
    if(p == nullptr || p->next == nullptr) return nullptr;
    else return p->next;    
}
void linkedList::insert(int pos, pNode elem)
{
    pNode p = head;
    for(int i = 1; i < pos && p != nullptr; i++) p = p->next;
    if(p == nullptr) return;

    elem->next = p->next;
    p->next = elem;
}
void linkedList::headInsert(pNode elem)
{
    insert(1, elem);
}
pNode linkedList::tailInsert(pNode tail, pNode elem)
{
    tail->next = elem;
    return elem;
}
elemType linkedList::del(int pos)
{
    pNode p = head;
    for(int i = 1; i < pos && p != nullptr; i++) p = p->next;
    if(p == nullptr || p->next == nullptr) return -1;
    pNode delNode = p->next;
    p->next = delNode->next;

    elemType data = delNode->data;
    _free(delNode);
    return data;
}
void linkedList::traverseList(void(*visit)(pNode))
{
    pNode p = head;
    while(p->next != nullptr)
    {
        p = p->next;
        visit(p);
    }
}

bool linkedList::cmp(elemType data, elemType val)
{
    return data == val;
}
void linkedList::print(pNode elem)
{   
    printf("%d ", elem->data);
}

void* linkedList::_malloc(size_t Size)
{
    if (part == nullptr) return nullptr;
    return newMalloc(part, LINKED_LIST, Size);
}

void linkedList::_free(void* Pos)
{
    if (part == nullptr) return;
    newFree(part, Pos);
}
