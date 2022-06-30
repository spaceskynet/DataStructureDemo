/**
 * @file LinkedList.cpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief 带头节点的单向链表的实现
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "LinkedList.h"

PartitionIO* linkedList::part = nullptr;

void linkedList::initList()
{
    head = newNode(-1);
    if(head != nullptr) _printf("链表初始化完成\n");
}
pNode linkedList::newNode(elemType data)
{
    pNode elem = (pNode)_malloc(sizeof(Node));
    if (elem == nullptr) {
        _printf("无法获取申请空间的指针，新建结点失败!\n");
        return nullptr;
    }
    elem->data = data, elem->next = nullptr;
    return elem;
}
void linkedList::destoryList()
{
    clearList();
    _free(head);
    _printf("链表已销毁\n");
}
void linkedList::clearList()
{
    while(head->next != nullptr) del(1);
    _printf("链表已清空\n");
}
bool linkedList::isEmpty()
{
    bool is_empty = head->next == nullptr;
    _printf("当前链表%s空\n", is_empty ? "为" : "非");
    return head->next == nullptr;
}
int linkedList::listLength()
{
    pNode p = head;
    int cnt = 0;
    while(p->next != nullptr) ++cnt, p = p->next;
    _printf("链表长度为 %d.\n", cnt);
    return cnt;
}
pNode linkedList::getElem(int pos)
{
    pNode p = head;
    for(int i = 1; i <= pos && p != nullptr; i++) p = p->next;

    if (p != nullptr)
    {
        _printf("位序为 %d 的元素是 %d.\n", pos, p->data);
        elemPre(p), elemNext(p);
    }
    else
        _printf("位序 %d 非法!\n", pos);

    return p;
}
int linkedList::locateElem(elemType val)
{
    return locateElem(val, cmp);
}
int linkedList::locateElem(elemType val, bool(*cmp)(elemType, elemType))
{
    pNode p = head;
    int valPos = -1;
    for(int i = 1; p->next != nullptr; i++)
    {
        p = p->next;
        if (cmp(p->data, val)) {
            valPos = i;
            break;
        }
    }
    if (~valPos)
        _printf("第一个值为 %d 的元素的位序为 %d.\n", val, valPos);
    else
        _printf("在链表中不存在值为 %d 的元素!\n", val);

    return valPos;
}
pNode linkedList::elemPre(pNode elem)
{
    pNode p = head, pre = nullptr;
    while(p != nullptr && p->next != elem) p = p->next;
    if(p != nullptr && p != head) pre = p;

    if (pre != nullptr) _printf("前驱为 %d.\n", pre->data);
    return pre;
}
pNode linkedList::elemNext(pNode elem)
{
    pNode p = head, next = nullptr;
    while(p != nullptr && p != elem) p = p->next;
    // p->next == NULL can be merged to `else`
    if(p != nullptr && p->next != nullptr) next = p->next;
    if (next != nullptr) _printf("后继为 %d.\n", next->data);
    return next;
}
void linkedList::insert(int pos, pNode elem)
{
    pNode p = head;
    for(int i = 1; i < pos && p != nullptr; i++) p = p->next;
    if (p == nullptr)
    {
        _printf("位序 %d 非法\n", pos);
        return;
    }

    elem->next = p->next;
    p->next = elem;
    _printf("在 %d 处插入了元素 %d.\n", pos, elem->data);
}

void linkedList::insert(int pos, elemType val)
{
    insert(pos, newNode(val));
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
    if (pos <= 0) {
        _printf("位序 %d 非法!\n", pos);
        return -1;
    }
    pNode p = head;
    for(int i = 1; i < pos && p != nullptr; i++) p = p->next;
    if(p == nullptr || p->next == nullptr) return -1;
    pNode delNode = p->next;
    p->next = delNode->next;

    elemType data = delNode->data;
    _free(delNode);

    if (~data)
        _printf("位序为 %d 的元素已删除! 该元素值为 %d.\n", pos, data);
    else
        _printf("位序 %d 非法!\n", pos);

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

void linkedList::printAllElem()
{
    _printf("链表的所有元素: "), traverseList(print), _printf("\n");
}

bool linkedList::cmp(elemType data, elemType val)
{
    return data == val;
}
void linkedList::print(pNode elem)
{   
    _printf("%d ", elem->data);
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

int linkedList::_printf(const char* format, ...)
{
    va_list aptr;
    int ret;

    va_start(aptr, format);
    ret = qprintf(part, format, aptr);
    va_end(aptr);
    return ret;
}

void linkedList::recovery(signed_size_t offset)
{
    addOffset(head, offset);
    pNode p = head;
    while (p->next != nullptr)
    {
        addOffset(p->next, offset);
        p = p->next;
    }
}

void linkedList::defaultShow()
{
    _printf("\n输出默认展示项\n");
    isEmpty();
    listLength();
    printAllElem();

    int pos = 4;
    getElem(pos);
    int val = 3;
    locateElem(val, cmp);
}

void linkedList::defaultInput()
{
    _printf("\n加载默认测试数据\n");
    int n = 5;
    initList();
    pNode tail = head;
    isEmpty();
    for (int i = 1; i <= n; i++)
    {
        elemType x = i;
        tail = tailInsert(tail, newNode(x));
        _printf("在链表尾部插入元素 %d.\n", x);
    }
    listLength();
    printAllElem();
}
