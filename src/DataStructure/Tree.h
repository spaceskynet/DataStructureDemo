/**
 * @file Tree.h
 * @author Louis0612 SpaceSkyNet
 * @brief 树的声明
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "../FileIO.h"
#include <cstdio>
#include <cstdlib>

#define MY_malloc _malloc
#define MY_free _free
#define MY_printf _printf

typedef struct _tagLinkListNode LinkListNode;
typedef struct _tagheadernode
{
    int length;
    LinkListNode *header;
} TLinkList;
typedef char TreeNode;
typedef char TreeData;
typedef struct _tagTreeNode TTreeNode;
struct _tagLinkListNode
{
    TTreeNode *value;
    LinkListNode *next;
};
typedef TLinkList LinkList;
struct _tagTreeNode
{
    TreeData data;
    TTreeNode *parent;
    LinkList *child;
};
typedef TTreeNode TLinkListNode;
struct myTree
{
    TLinkList* tree;
    LinkList* LinkList_Create();
    void LinkList_Destroy(LinkList *list);
    void LinkList_Clear(LinkList *list);
    int LinkList_Insert(LinkList *list, int pos, TTreeNode *node);
    int LinkList_Delete(LinkList *list, int pos);
    TTreeNode* LinkList_Get(LinkList *list, int pos);
    int LinkList_Length(LinkList *list);
    void recursive_Delete(TTreeNode *node);
    int recursive_degree(TTreeNode *node);
    void tree_display(char data);
    void recursive_display(TTreeNode *node, int count);
    int recursive_height(TTreeNode *node);

    void create();
    void destroy();
    void clear();
    void insert(char, int);
    TreeNode deletenode(int);
    TreeNode get(int);
    TreeNode root();
    int height();
    int count();
    int max_degree();
    void display();

    void input();
    void show(); 

    //自实现内存分配回收时，数据结构结构体需要额外添加的部分
    static PartitionIO* part;

    static void* _malloc(size_t);
    static void _free(void*);
    static int _printf(const char*, ...);

    void recovery(signed_size_t); //将原数据结构中所有指针变量加上 offset
    template<typename T>void addOffset(T& var, signed_size_t offset) {
        if (var == nullptr) return;
        var = (T)((char*)var + offset);
    }

};
