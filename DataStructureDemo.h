/**
 * @file DataStructureDemo.h
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief �������ݽṹ�ļ��ϵĲ����������
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "FileIO.h"
#include "DataStructure/LinkedList.h"

/**
 * @brief �������ݽṹ�ļ���
 * 
 */
class Collection
{
private:
	PartitionIO* part; // �ڴ������ղ�����

	vector<linkedList*> linked_list; // ��ͷ�ڵ�ĵ�������

public:
	Collection();
	~Collection();
	void rebuild(); // ���ڴ����ؽ��ļ�ģ���ڴ��е����ݽṹ
	void singleRebuild(DS_CLASS, void *, signed_size_t); // ���ض������ݽṹ�ؽ�
	void show(DS_CLASS, int); // չʾ�ض������ݽṹ
	void input(DS_CLASS); // �����ض������ݽṹ
	void del(DS_CLASS, int); // ɾ���ض������ݽṹ

	void printBasicInfo();
	void printBlockInfo(unsigned int);
	void printBlockInfoAll();
};
