/**
 * @file Stack.h
 * @author cytotropism SpaceSkyNet
 * @brief 栈的实现
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Stack.h"

PartitionIO *myStack::part = nullptr;
void *myStack::_malloc(size_t Size)
{
    if (part == nullptr)
        return nullptr;
    return newMalloc(part, STACK, Size);
}

void myStack::_free(void *Pos)
{
    if (part == nullptr)
        return;
    newFree(part, Pos);
}

int myStack::_printf(const char *format, ...)
{
    va_list aptr;
    int ret;

    va_start(aptr, format);
    ret = qprintf(part, format, aptr);
    va_end(aptr);
    return ret;
}

void myStack::recovery(signed_size_t offset)
{
    addOffset(pStack, offset);
    addOffset(pStack->base, offset);
    addOffset(pStack->top, offset);
}

Status myStack::Init()
{
    pStack = (SqStack *)Mymalloc(sizeof(SqStack));
    if (pStack == NULL)
    {
        Myprintf("Init: malloc fail\n");
        return ERROR;
    }
    Myprintf("栈的对象内存分配成功\n");
    return InitStack();
}

Status myStack::InitStack()
{
    //构造一个空栈S
    pStack->base = (SElemType *)Mymalloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (pStack->base == NULL)
    { //存储分配失败
        Myprintf("InitStack: malloc err\n");
        return ERROR;
    }
    pStack->top = pStack->base;
    pStack->stacksize = STACK_INIT_SIZE;
    Myprintf("InitStack: malloc 成功\n");
    return OK;
} // InitStack

Status myStack::DestroyStack()
{
    if (pStack->base == NULL)
    {
        Myprintf("DestroyStack: Stack does not exist\n");
        return ERROR;
    }
    //在调用malloc的时候，系统会记住你申请的这块连续空间的起始地址以及这块空间的大小，
    //释放free的时候，只要把这个起始地址告诉系统，系统自然就知道要释放多大的空间。
    Myfree(pStack->base);
    ClearStack();
    Myfree(pStack);
    Myprintf("DestroyStack: Stack 销毁成功\n");
    return OK;
} // DestroyStack

Status myStack::ClearStack()
{
    if (pStack->base == NULL)
    {
        Myprintf("ClearStack: Stack does not exist\n");
        return ERROR;
    }
    pStack->top = pStack->base;
    Myprintf("ClearStack: Stack Clear 成功\n");
    return OK;
} // ClearStack

Status myStack::StackEmpty()
{
    if (pStack->top == pStack->base)
    {
        Myprintf("栈为空\n");
        return TRUE;
    }
    else
    {
        Myprintf("栈不为空\n");
        return FALSE;
    }
} // StackEmpty

int myStack::StackLength()
{
    Myprintf("栈的长度为%d，容量为%d\n", pStack->top - pStack->base, pStack->stacksize);
    return pStack->top - pStack->base;
} // StackLength

Status myStack::GetTop()
{
    ////若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
    if (pStack->top == pStack->base)
    {
        Myprintf("GetTop: Stack is empty\n");
        return ERROR;
    }
    Myprintf("栈顶元素为%d\n", *(pStack->top - 1));
    return OK;
} // GetTop

Status myStack::Push(SElemType e)
{
    //插入元素e为新的栈顶元素
    if (pStack->top - pStack->base >= pStack->stacksize)
    { //栈满，追加存储空间
        SElemType *tempt = (SElemType *)Mymalloc((pStack->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (tempt == NULL)
        {
            Myprintf("Push: realloc error\n");
            return ERROR;
        }
        memcpy(tempt, pStack->base, pStack->stacksize * sizeof(SElemType));
        Myfree(pStack->base);
        pStack->base = tempt;

        pStack->top = pStack->base + pStack->stacksize;
        pStack->stacksize += STACKINCREMENT;
    }
    *pStack->top++ = e; //*S.top = e; S.top++;
    Myprintf("插入元素 %d 成功\n", e);
    return OK;
} // Push

Status myStack::Pop()
{
    //若栈不空，则删除S的栈顶元素，用e返回新栈顶的值，并返回OK，否则返回ERROR;
    if (pStack->top == pStack->base)
    {
        Myprintf("Pop: Stack is empty\n");
        return ERROR;
    }
    Myprintf("弹出的栈顶元素 e=%d\n", *--pStack->top);
    return OK;
} // Pop

Status myStack::StackTraverse(Status (*visit)(SElemType))
{
    SElemType *p = pStack->base;
    Myprintf("栈中的元素依次为（栈底->栈顶）：");
    while (pStack->top > p)
    {
        visit(*p++);
    }
    Myprintf("\n");
    return OK;
} // StackTraverse

Status myStack::PrintAllElem()
{
    if (pStack->top == pStack->base)
    {
        Myprintf("PrintAllElem: Stack is empty\n");
        return ERROR;
    }
    return StackTraverse(visit);
}

Status myStack::visit(SElemType e)
{
    Myprintf("%d ", e);
    return OK;
} // visit

void myStack::Input()
{
    SElemType j;
    if (Init() == OK)
        for (j = 1; j <= 12; j++)
        {
            Push(j);
        }
}
void myStack::Show()
{
    StackTraverse(visit);
    Pop();
    StackTraverse(visit);
    GetTop();
    Push(5);
    StackTraverse(visit);
    StackLength();
} // TestMyStack

//主函数
/*
int main(){
  myStack* s=new myStack;
  s->Input();
  s->Show();
  delete s;
  return 0;
}
*/
