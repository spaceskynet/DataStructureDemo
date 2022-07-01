/**
 * @file Heap.cpp
 * @author cytotropism SpaceSkyNet
 * @brief 堆的实现
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Heap.h"

PartitionIO *myHeap::part = nullptr;
void *myHeap::_malloc(size_t Size)
{
	if (part == nullptr)
		return nullptr;
	return newMalloc(part, HEAP, Size);
}

void myHeap::_free(void *Pos)
{
	if (part == nullptr)
		return;
	newFree(part, Pos);
}

int myHeap::_printf(const char *format, ...)
{
	va_list aptr;
	int ret;

	va_start(aptr, format);
	ret = qprintf(part, format, aptr);
	va_end(aptr);
	return ret;
}

void myHeap::recovery(signed_size_t offset)
{
	addOffset(pHeap, offset);
	addOffset(pHeap->a, offset);
}

void myHeap::Swap(int *px, int *py)
{
	int tmp = *px;
	*px = *py;
	*py = tmp;
}

// 条件：左右子树都是小堆/大堆
void myHeap::AdjustDown(int *a, int n, int parent)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		// 选出左右孩子中小 or 大的那个
		if (child + 1 < n && a[child + 1] < a[child])
		{
			++child;
		}

		// 1、如果小 or 大的孩子比父亲小 or 大，则交换，继续往下调整
		// 2、如果小 or 大 的孩子比父亲大 or 小，则结束调整
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void myHeap::AdjustUp(int *a, int child)
{
	int parent = (child - 1) / 2;
	// while (parent >= 0)  不对的 parent不会小于0
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void myHeap::Init(bool use_default)
{
	pHeap = (Heap *)Mymalloc(sizeof(Heap));
	if (pHeap == NULL)
	{
		Myprintf("Init: malloc fail\n");
		return;
	}
	Myprintf("堆的对象内存分配成功\n");
	if (use_default)
		HeapInit();
}

void myHeap::HeapInit()
{
	pHeap->a = (HPDataTpye *)Mymalloc(sizeof(HPDataTpye) * HEAP_INIT_SIZE);
	if (pHeap->a == NULL)
	{
		Myprintf("malloc fail\n");
		return;
	}
	pHeap->capacity = HEAP_INIT_SIZE;
	pHeap->size = 0;
	Myprintf("堆的内存分配成功\n");
}

void myHeap::HeapInit(HPDataTpye *a, int n)
{
	pHeap->a = (HPDataTpye *)Mymalloc(sizeof(HPDataTpye) * n);
	if (pHeap->a == NULL)
	{
		Myprintf("malloc fail\n");
		return;
	}
	//转移数据
	memcpy(pHeap->a, a, sizeof(HPDataTpye) * n);
	//建堆排序
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		AdjustDown(pHeap->a, n, i);
	}
	pHeap->capacity = n;
	pHeap->size = n;
	Myprintf("堆的内存分配成功\n");
}

// 插入x，保持它继续是堆
void myHeap::HeapPush(HPDataTpye x)
{
	if (pHeap->capacity <= pHeap->size)
	{
		HPDataTpye *tempt = (HPDataTpye *)Mymalloc(2 * pHeap->capacity * sizeof(HPDataTpye));
		if (tempt == NULL)
		{
			Myprintf("HeapPush: realloc fail\n");
			return;
		}
		memcpy(tempt, pHeap->a, pHeap->size * sizeof(HPDataTpye));
		Myfree(pHeap->a);
		pHeap->a = tempt;

		pHeap->capacity *= 2;
	}
	pHeap->a[pHeap->size] = x;
	pHeap->size++;

	AdjustUp(pHeap->a, pHeap->size - 1);
	Myprintf("成功将元素 %d 插入堆\n", x);
}

bool myHeap::HeapEmpty()
{
	if (pHeap->size == 0)
	{
		Myprintf("堆为空\n");
	}
	else
	{
		Myprintf("堆不为空\n");
	}
	return pHeap->size == 0;
}

// 删除堆顶数据，删除后保持他继续是堆
void myHeap::HeapPop()
{
	if (HeapEmpty())
		return;
	Swap(&pHeap->a[0], &pHeap->a[pHeap->size - 1]);
	pHeap->size--;
	AdjustDown(pHeap->a, pHeap->size, 0);
	Myprintf("已删除堆顶数据\n");
}

// 获取堆顶的数据，也就是最值
HPDataTpye myHeap::HeapTop()
{
	if (HeapEmpty())
		return -1;
	Myprintf("堆顶的数据为%d\n", pHeap->a[0]);
	return pHeap->a[0];
}

int myHeap::HeapSize()
{
	Myprintf("堆的大小为%d, 容量为 %d\n", pHeap->size, pHeap->capacity);
	return pHeap->size;
}

void myHeap::HeapPrint()
{
	if (HeapEmpty())
		return;
	Myprintf("堆当前所有元素为：\n");
	for (int i = 0; i < pHeap->size; i++)
	{
		Myprintf("%d ", pHeap->a[i]);
		if (((i + 2) & (i + 1)) == 0)
			Myprintf("\n");
	}
	Myprintf("\n");
}

void myHeap::HeapClear()
{
	pHeap->size = 0;
	Myprintf("堆已清空\n");
}

void myHeap::HeapDestroy()
{
	Myfree(pHeap->a);
	pHeap->a = NULL;
	pHeap->capacity = pHeap->size = 0;
	Myfree(pHeap);
	Myprintf("堆已销毁\n");
}

//以下用于测试
void myHeap::Input()
{
	int a[] = {27, 37, 28, 18, 19, 34, 65, 4, 25, 49, 15};
	Init(false);
	if(pHeap == NULL) return;
	HeapInit(a, sizeof(a) / sizeof(int));
	if(pHeap->a == NULL) return;
	HeapPrint();
	Myprintf("\n");
}

void myHeap::Show()
{
	HeapPop();
	HeapPrint();
	HeapPush(5);
	HeapPrint();
	HeapSize();
	HeapTop();
}

/*
int main()
{
	myHeap* s=new myHeap;
  s->Input();
	s->Show();
  delete s;
  return 0;
}*/
