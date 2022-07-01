/**
 * @file Tree.cpp
 * @author Louis0612 SpaceSkyNet
 * @brief 树的实现
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Tree.h"

PartitionIO* myTree::part = nullptr;
void* myTree::_malloc(size_t Size)
{
    if (part == nullptr) return nullptr;
    return newMalloc(part, TREE, Size);
}

void myTree::_free(void* Pos)
{
    if (part == nullptr) return;
    newFree(part, Pos);
}

int myTree::_printf(const char* format, ...)
{
    va_list aptr;
    int ret;

    va_start(aptr, format);
    ret = qprintf(part, format, aptr);
    va_end(aptr);
    return ret;
}

LinkList *myTree::LinkList_Create()
{
    TLinkList *mlinklist = (TLinkList *)MY_malloc(sizeof(TLinkList));
    if (mlinklist != NULL)
    {
        mlinklist->length = 0;
        mlinklist->header = (LinkListNode *)MY_malloc(sizeof(LinkListNode));
    }
    return mlinklist;
}

void myTree::LinkList_Destroy(LinkList *list)
{
    TLinkList *mlinklist = (TLinkList *)list;
    if (mlinklist != NULL)
    {
        mlinklist->header = NULL;
		mlinklist = NULL;
    }
    return;
}

void myTree::LinkList_Clear(LinkList *list)
{
    TLinkList *mlinklist = (TLinkList *)list;
    if (mlinklist != NULL)
    {
        mlinklist->length = 0;
        MY_free(mlinklist->header);
        MY_free(mlinklist);
    }
    return;
}

int myTree::LinkList_Insert(LinkList *list, int pos, TTreeNode *node)
{
    int insert = 1;
    int i = 0;
    int ret = -1;

    TLinkList *mlinklist = (TLinkList *)list;
    insert = insert && (mlinklist != NULL) && (pos <= mlinklist->length) && (node != NULL);
    LinkListNode *mnode = (LinkListNode *)MY_malloc(sizeof(LinkListNode));
    insert = insert && (mnode != NULL);
    if (insert)
    {
        if (mlinklist->length == 0)
        {
            mnode->value = node;
            mnode->next = NULL;
            mlinklist->header->next = mnode;
            mlinklist->length++;
        }
        else
        {
            LinkListNode *current = mlinklist->header;
            for (i = 0; i < pos && current->next != NULL; i++)
            {
                current = current->next;
            }
            mnode->value = node;
            mnode->next = current->next;
            current->next = mnode;
            mlinklist->length++;
        }
        ret = 0;
    }
    return ret;
}

int myTree::LinkList_Delete(LinkList *list, int pos)
{
    // bool delete = true;
    int i = 0;
    int Ret = -1;

    TLinkList *mlinklist = (TLinkList *)list;
    // delete = delete && (mlinklist != NULL) && (pos <= mlinklist->length) && (mlinklist->length != 0);
    LinkListNode *ret = NULL;

    if ((mlinklist != NULL) && (pos <= mlinklist->length) && (mlinklist->length != 0))
    {
        LinkListNode *current = mlinklist->header;
        for (i = 0; i < pos && current->next != NULL; i++)
        {
            current = current->next;
        }
        if (mlinklist->length == 1)
        {
            MY_free(current->next);
            current->next = NULL;
            mlinklist->length = 0;
        }
        else
        {
            ret = current->next;
            current->next = ret->next;
            MY_free(ret);
            ret = NULL;
            mlinklist->length--;
        }
        Ret = 0;
    }
    return Ret;
}
TTreeNode *myTree::LinkList_Get(LinkList *list, int pos)
{
    int get = 1;
    int i = 0;
    TLinkList *mlinklist = (TLinkList *)list;
    get = get && (mlinklist != NULL) && (pos <= mlinklist->length) && (mlinklist->length != 0);
    TLinkListNode *ret = NULL;
    if (get)
    {
        LinkListNode *current = mlinklist->header;
        for (i = 0; i < pos && current->next != NULL; i++)
        {
            current = current->next;
        }
        ret = current->next->value;
    }
    return ret;
}

int myTree::LinkList_Length(LinkList *list)
{
    int ret = -1;
    TLinkList *mlinklist = (TLinkList *)list;
    if (mlinklist != NULL)
        ret = mlinklist->length;
    return ret;
}
void myTree::create()
{
    MY_printf("创建成功！\n");
    tree = LinkList_Create();
}
void myTree::destroy()
{
    if (tree != NULL)
    {
        clear();
        LinkList_Clear(tree);
        LinkList_Destroy(tree);
        MY_printf("销毁成功!\n");
    }
    return;
}
void myTree::clear()
{
    deletenode(0);
    return;
}
void myTree::insert(char node, int pos)
{
    TTreeNode *mnode = NULL;

    if (tree != NULL && node != NULL && pos < LinkList_Length(tree))
    {
        mnode = (TTreeNode *)MY_malloc(sizeof(TTreeNode));
        if (mnode != NULL)
        {
            mnode->data = node;
            mnode->parent = (TTreeNode *)LinkList_Get(tree, pos);
            mnode->child = LinkList_Create();
            LinkList_Insert(tree, LinkList_Length(tree), mnode); //在树对应的链表添加

            if (mnode->parent != NULL)
            {
                LinkList_Insert(mnode->parent->child, LinkList_Length(mnode->parent->child), mnode); //在child对应链表添加
            }
            MY_printf("插入%c成功\n", node);
        }
        else
        {
            MY_free(mnode);
            MY_printf("插入失败\n");
        }
    }
    else
    {
        MY_printf("插入失败\n");
    }
}
void myTree::recursive_Delete(TTreeNode *node)
{
    int i = 0;

    if (node != NULL && tree != NULL)
    {
        for (i = 0; i < LinkList_Length(tree); i++)
        {
            TTreeNode *LinkListTreeNode = (TTreeNode *)LinkList_Get(tree, i);
            if (LinkListTreeNode == node)
            {
                LinkList_Delete(tree, i);
                break;
            }
        }

        if (node->parent != NULL)
        {
            for (i = 0; i < LinkList_Length(node->parent->child); i++)
            {
                TTreeNode *PTreeNode = (TTreeNode *)LinkList_Get(node->parent->child, i);
                if (PTreeNode == node)
                {
                    LinkList_Delete(node->parent->child, i);
                    break;
                }
            }
        }
        if (node->child != NULL)
        {
            while (LinkList_Length(node->child) > 0)
            {
                TTreeNode *CTreeNode = (TTreeNode *)LinkList_Get(node->child, 0);
                recursive_Delete(CTreeNode);
            }
        }
        LinkList_Clear(node->child);
        LinkList_Destroy(node->child);
        MY_free(node);
    }
}
TreeNode myTree::deletenode(int pos)
{
    TTreeNode *mnode = NULL;
    TreeNode ret = NULL;
    mnode = (TTreeNode *)LinkList_Get(tree, pos);
    if (mnode != NULL)
    {
        ret = mnode->data;
        recursive_Delete(mnode); //利用递归删除子节点
    }
    MY_printf("已删除节点%c\n", ret);
    return ret;
}
TreeNode myTree::get(int Pos)
{
    TTreeNode *mnode = NULL;
    TreeNode ret = NULL;
    mnode = (TTreeNode *)LinkList_Get(tree, Pos);
    if (mnode != NULL) {
        ret = mnode->data;
        MY_printf("编号为 %d 节点为 %c\n", Pos, ret);
    }
    else {
        MY_printf("编号为 %d 非法\n", Pos);
    }
    return ret;
}
TreeNode myTree::root()
{
    TTreeNode *mnode = NULL;
    TreeNode ret = NULL;
    mnode = (TTreeNode *)LinkList_Get(tree, 0);
    if (mnode != NULL)
        ret = mnode->data;
    MY_printf("树的根节点为 %c\n", ret);
    return ret;
}
int myTree::recursive_height(TTreeNode *node)
{
    int i = 0;
    int subNodeheight = 0;
    int ret = 0;

    if (node != NULL)
    {
        for (i = 0; i < LinkList_Length(node->child); i++)
        {
            TTreeNode *CTreeNode = (TTreeNode *)LinkList_Get(node->child, i);
            subNodeheight = recursive_height(CTreeNode);
            if (ret < subNodeheight)
                ret = subNodeheight;
        }
        ret = ret + 1;
    }

    return ret;
}
int myTree::height()
{
    TTreeNode *mnode = NULL;
    int ret = 0;
    mnode = (TTreeNode *)LinkList_Get(tree, 0);
    if (mnode != NULL)
        ret = recursive_height(mnode); //递归
    MY_printf("高度: %d\n", ret);
    return ret;
}
int myTree::count()
{
    int ret = LinkList_Length(tree);
    MY_printf("节点数: %d\n", ret);
    return 0;
}
int myTree::recursive_degree(TTreeNode *node)
{
    int i = 0;
    int subNodeDegree = 0;
    int ret = 0;

    if (node != NULL)
    {
        ret = LinkList_Length(node->child);
        for (i = 0; i < LinkList_Length(node->child); i++)
        {
            TTreeNode *CTreeNode = (TTreeNode *)LinkList_Get(node->child, i);
            subNodeDegree = recursive_degree(CTreeNode);
            if (ret < subNodeDegree)
                ret = subNodeDegree;
        }
    }
    return ret;
}
int myTree::max_degree()
{
    TTreeNode *mnode = NULL;
    int ret = 0;
    mnode = (TTreeNode *)LinkList_Get(tree, 0);
    if (mnode != NULL)
        ret = recursive_degree(mnode);
    MY_printf("最大度: %d\n", ret);
    return ret;
}
void myTree::tree_display(char data)
{
    MY_printf("%c\n", data);
}
void myTree::recursive_display(TTreeNode *node, int count)
{
    int i = 0;
    if (node != NULL)
    {
        for (i = 0; i < count; i++)
            MY_printf("  ");
        tree_display(node->data);
        for (i = 0; i < LinkList_Length(node->child); i++)
        {
            recursive_display((TTreeNode *)LinkList_Get(node->child, i), count + 2);
        }
    }
    return;
}
void myTree::display()
{
    TTreeNode *mnode = NULL;
    mnode = (TTreeNode *)LinkList_Get(tree, 0);
    if (mnode != NULL)
    {
        MY_printf("树（横向）: \n");
        recursive_display(mnode, 0);
    }
    else MY_printf("树为空\n");
}

void myTree::input() 
{
    create();
    insert('1', -1);
    insert('B', 0);
    insert('C', 0);
    insert('D', 0);
    insert('E', 1);
    insert('F', 1);
    insert('H', 3);
    insert('I', 3);
    insert('J', 3);
}

void myTree::show()
{
    display();
    height();
    max_degree();
    count();
    MY_printf("删除节点1: \n");
    deletenode(1);
    display();
}

void myTree::recovery(signed_size_t offset)
{
    addOffset(tree, offset);
    addOffset(tree->header, offset);
    LinkListNode* p = tree->header;
    while (p != nullptr)
    {
        if (p->next != nullptr) addOffset(p->next, offset);
        if (p->value != nullptr) {
            addOffset(p->value, offset);
            TTreeNode* q = p->value;
            if (q->parent != nullptr) addOffset(q->parent, offset);
            if (q->child != nullptr) {
                addOffset(q->child, offset);
                addOffset(q->child->header, offset);
                LinkListNode* r = q->child->header;
                while (r != nullptr)
                {
                    if(r->next != nullptr) addOffset(r->next, offset);
                    if(r->value != nullptr) addOffset(r->value, offset);
                    r = r->next;
                }
            }
        }
        p = p->next;
    }
}

/*
int main()
{

    return 0;
}
*/
