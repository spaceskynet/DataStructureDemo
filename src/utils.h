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

public:
	Collection();
	~Collection();
	void rebuild(); // 在内存中重建文件模拟内存中的数据结构
	void singleRebuild(DS_CLASS, void *, signed_size_t); // 对特定的数据结构重建
	void show(DS_CLASS, int); // 展示特定的数据结构
	void init(DS_CLASS, bool); // 建立特定的数据结构
	void del(DS_CLASS, int); // 删除特定的数据结构

	void clearAll();

	void printBasicInfo();
	void printBlockInfo(unsigned int);
	void printBlockInfoAll();
};

bool isNumber(const string& s);