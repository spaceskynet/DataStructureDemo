/*********************************************************************
 * \file   FileIO.h
 * \brief  
 * 
 * \author SpaceSkyNet
 * \date   June 2022
 *********************************************************************/
#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define F_OK 0
#define DATA_FILE_PATH "./mem.dat"
#define DATA_FILE_HEADER "BIT\xAC"
#define DEFAULT_BLOCK_SIZE 4 //单位字节
#define MEM_ALLOC_ALG FF

const int BLOCK_TOTAL_SIZE = 100 * 1024 * 1024;
const unsigned int INF = ~0U;

enum MEMORY_ALLOCATION_ALGORITHM { FF, BF, WF }; // 内存分配算法
enum DS_CLASS { NOT_USED, USED, LINKED_LIST }; //数据结构类型

typedef struct BLOCK
{
	DS_CLASS type;
	unsigned int pos, size;
	BLOCK* prior, * next;
	BLOCK(unsigned int pos, unsigned int size) :type(NOT_USED), pos(pos), size(size), prior(nullptr), next(nullptr) {}
	bool is_free();
}* block;

typedef struct BLOCK_LINKED_LIST
{
	block head;
	int len;

	BLOCK_LINKED_LIST();
	~BLOCK_LINKED_LIST();
	block newNode(DS_CLASS, unsigned int, unsigned int);
	void clearList();
	void del(int);
	void del(block);
	block tailInsert(block, block);
	void traverseList(FILE*, size_t(*write)(const void*, size_t, size_t, FILE*));
	block locateElem(unsigned int);
}* list;

typedef struct FILE_HEADER
{
	char header[4];
	unsigned int block_size;
	FILE_HEADER() { setDefault(); }
	void setDefault();
}*header;

class PartitionIO
{
private:
	header head;
	list block_info;
	char* partition;
public:
	PartitionIO();
	~PartitionIO();
	void readFile();
	void writeFile();
	void clear();
	void mergeBlock(block);
	void splitBlock(block, unsigned int);

	block memAlloc(unsigned int); //内存分配算法选择
	block firstFit(unsigned int); //首次适应算法
	block bestFit(unsigned int); //最佳适应算法
	block worstFit(unsigned int); //最差适应算法

	unsigned int getBlockSize();
	void* calcRealAddress(block);
	unsigned int calcPos(void*);
	block findBlock(unsigned int);
};

void* newMalloc(PartitionIO*, DS_CLASS, size_t); // 自实现内存分配函数
void newFree(PartitionIO*, void*); // 自实现内存回收函数 
