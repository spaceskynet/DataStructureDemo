#pragma once

#include "../FileIO.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

#define Mymalloc _malloc
#define Myfree _free
#define Myprintf _printf

#define HEAP_INIT_SIZE 10

typedef int HPDataTpye;

struct Heap
{
	HPDataTpye* a;
	int size;
	int capacity;
};

struct myHeap
{

	Heap* pHeap;
	myHeap() { pHeap = nullptr; }
	~myHeap(){}

//堆元素的交换
void Swap(int* px, int* py);
//堆的向下调整
void AdjustDown(int* a, int n, int parent);
//堆的向上调整
void AdjustUp(int* a, int child);
//初始化,堆内存分配
void HeapInit(HPDataTpye* a, int n);
void HeapInit(); // 默认容量大小，空堆
// 插入x，保持他继续是堆
void HeapPush(HPDataTpye x);
//判空
bool HeapEmpty();
// 删除堆顶数据，删除后保持他继续是堆
void HeapPop();
// 获取堆顶的数据，也就是最值
HPDataTpye HeapTop();
//获取堆中元素个数
int HeapSize();
//打印
void HeapPrint();
//清空堆
void HeapClear();
//销毁堆
void HeapDestroy();
//堆的元素分配
void Init(bool);

void Show();

void Input();

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
