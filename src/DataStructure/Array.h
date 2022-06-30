#pragma once
#include "../FileIO.h"
#include <cstdio>
#include <cstdlib>

#define my_malloc _malloc
#define my_free _free
#define my_printf _printf

struct Arr{
    int *base;
    int len;
    int num;
};

struct myArray
{
    struct Arr *pArr;

    myArray() { pArr = nullptr; }
    ~myArray(){}

    void init();//初始化
    void initArray(int); // 根据数组长度申请空间
    void clear();//清空数组
    void destroy();//回收数组
    bool ready(); // 是否申请了空间
    bool empty();//判断是否为空 
    bool full();//判断是否满 
    bool append(int);//在末端添加元素 
    bool insert(int, int);//在位置x插入元素y 
    bool del(int);//删除位置x的元素 
    bool get(int);//获取位置x的元素 
    bool locate(int); // 查找第一个值为val的元素、
    int length(); // 获取数组长度
    void display();//展示数组
    
    void input();
    void show();

    // 自实现内存分配回收时，数据结构结构体需要额外添加的部分
    static PartitionIO* part;

    static void* _malloc(size_t);
    static void _free(void*);
    static int _printf(const char*, ...);

    void recovery(signed_size_t); //将原数据结构中所有指针变量加上 offset
    template<typename T>void addOffset(T& var, signed_size_t offset) {
        var = (T)((char*)var + offset);
    }
};
