//By: SpaceSkyNet
#pragma once
#include "../FileIO.h"
#include <cstdio>
#include <cstdlib>

typedef int elemType;
typedef struct linkedListNode Node;
typedef Node* pNode;
struct linkedListNode
{
    elemType data;
    pNode next;
};

struct linkedList 
{
    pNode head;

    linkedList(){}
    ~linkedList(){}

    void initList();
    void destoryList();
    void clearList();
    bool isEmpty();
    int listLength();
    pNode getElem(int);
    int locateElem(elemType, bool(*)(elemType, elemType));
    pNode elemPre(pNode);
    pNode elemNext(pNode);
    void insert(int, pNode);
    elemType del(int);
    void traverseList(void(*)(pNode));
    pNode newNode(elemType data);
    void headInsert(pNode);
    pNode tailInsert(pNode, pNode);

    static bool cmp(elemType, elemType);
    static void print(pNode);

    // ��ʵ���ڴ�������ʱ�����ݽṹ�ṹ����Ҫ������ӵĲ���
    static PartitionIO* part;

    static void* _malloc(size_t);
    static void _free(void*);

    void recovery(signed_size_t); //��ԭ���ݽṹ������ָ��������� offset
    template<typename T>void addOffset(T& var, signed_size_t offset) {
        var = (T)((char*)var + offset);
    }

    void show();
    void initInput();
};