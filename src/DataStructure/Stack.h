#ifndef MYSTACK_H_
#define MYSTACK_H_

#include "../FileIO.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define Mymalloc _malloc
#define Myfree _free
#define Myprintf _printf
/*栈(Stack)是限定仅在表尾进行插入或删除操作的线性表
**栈顶(top)和栈底(bottom)相等，代表为空栈
**
*/
#define Status bool
//SElemType是某个确定的、将由用户自行定义的、含某个关系运算的数据对象
typedef int SElemType;

//函数结果状态代码
#define TRUE    1
#define FALSE    0
#define OK     1
#define ERROR    0
#define INFEASIBLE -1   //不可行
#define MY_OVERFLOW -2   //溢出

/**********栈的顺序存储表示**********/
#define STACK_INIT_SIZE 100   //存储空间初始分配量
#define STACKINCREMENT 10   //存储空间分配增量

typedef struct{
  SElemType *base;  //在栈构造之前和销毁之后，base的值为NULL
  SElemType *top;   //栈顶指针
  int stacksize;   //当前已分配
}SqStack;
/**********基本操作的函数原型说明**********/
struct myStack
{
  SqStack* pStack;
  myStack() { pStack = nullptr; }
  ~myStack(){}

//构造一个空栈S
Status InitStack();
//销毁栈S，S不再存在
Status DestroyStack();
//把S置为空栈
Status ClearStack();
//若栈S为空栈，则返回TURE，否则返回FALSE
Status StackEmpty();
//返回S的元素个数，即栈的长度
int StackLength();
//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status GetTop();
//插入元素e为新的栈顶元素
Status Push(SElemType e);
//若栈不空，则删除S的栈顶元素，用e新栈顶的值，并返回OK;否则返回ERROR;
Status Pop();
//从栈底到栈顶依次对栈中每个元素调用函数visit();一旦visit()失败，则操作失败
Status StackTraverse(Status(* visit)(SElemType));
//打印所有元素
Status PrintAllElem();
//visit()函数
static Status visit(SElemType e);
//栈的对象内存分配
Status Init();

void Input();

void Show();

//自实现内存分配回收时，数据结构结构体需要额外添加的部分
 static PartitionIO* part;

 static void* _malloc(size_t);
 static void _free(void*);
 static int _printf(const char*, ...);

 void recovery(signed_size_t); //将原数据结构中所有指针变量加上 offset
 template<typename T>void addOffset(T& var, signed_size_t offset) {
     var = (T)((char*)var + offset);
 }

};
#endif MYSTACK_H_
