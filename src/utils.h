/**
 * @file utils.h
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief 各种数据结构的集合类的声明
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "FileIO.h"
#include "DataStructure/LinkedList.h"
#include "DataStructure/Array.h"
#include "DataStructure/Stack.h"
#include "DataStructure/Heap.h"
#include "DataStructure/Tree.h"
#include "DataStructure/UndiG.h"
#include "DataStructure/DiG.h"
#include <string>
#include <memory>

using std::string;


 /**
 * @brief 各种数据结构的集合
 * 
 */
class Collection
{
public:
	PartitionIO* part; // 内存分配回收操作类

	vector<linkedList*> linked_list; // 带头节点的单向链表
	vector<myArray*> my_array; // 数组
	vector<myStack*> my_stack; // 栈
	vector<myHeap*> my_heap; // 堆
	vector<myTree*> my_tree; // 树
	vector<undirectionGraph*> undirection_graph; // 无向图
	vector<directionGraph*> direction_graph; // 有向图
	// more

public:
	Collection();
	~Collection();
	void rebuild(); // 在内存中重建文件模拟内存中的数据结构
	void singleRebuild(DS_CLASS, void *, signed_size_t); // 对特定的数据结构重建
	void init(DS_CLASS, bool); // 建立特定的数据结构
	void del(DS_CLASS, int); // 删除特定的数据结构

	void clearAll();

	void printBasicInfo();
	void printBlockInfo(unsigned int);
	void printBlockInfoAll();
};