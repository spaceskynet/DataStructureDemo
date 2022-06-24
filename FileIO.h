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
#include <utility>
#include <vector>
#define F_OK 0
#define DATA_FILE_PATH "./mem.dat"
#define DATA_FILE_HEADER "BIT\xAC"
#define DEFAULT_BLOCK_SIZE 4 // 单位为字节
#define MEM_ALLOC_ALG FF // 内存分配算法类型选择

const int BLOCK_TOTAL_SIZE = 100 * 1024 * 1024;
const unsigned int INF = ~0U;

typedef long long int signed_size_t;

using std::pair;
using std::make_pair;
using std::vector;

enum MEMORY_ALLOCATION_ALGORITHM { FF, BF, WF }; // 内存分配算法类型
enum DS_CLASS { NOT_USED, USED, LINKED_LIST }; //数据结构类型

typedef pair<DS_CLASS, void*> dsPair;

typedef struct FILE_HEADER
{
	char header[4];
	unsigned int block_size;
	FILE_HEADER() { setDefault(); }
	void setDefault();
}*header;

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

// 数据结构的结构体对象在自定义分区中的位置
typedef struct DS_STRUCT_POS_BLOCK
{
	DS_CLASS type;
	unsigned int pos;
	DS_STRUCT_POS_BLOCK* prior, * next;
	DS_STRUCT_POS_BLOCK(unsigned int pos):type(NOT_USED), pos(pos), prior(nullptr), next(nullptr) {}
}* dsBlock;

typedef struct DS_STRUCT_POS_LIST
{
	dsBlock head;
	int len;
	char* prev_part; // 上次程序运行时 partition 在内存中的地址

	DS_STRUCT_POS_LIST();
	~DS_STRUCT_POS_LIST();

	dsBlock newNode(DS_CLASS, unsigned int);
	void clearList();
	void del(int);
	void del(dsBlock);
	dsBlock locateElem(unsigned int); // 按照在自定义分区中的位置 pos 来定位 dsBlock
	void insert(int, dsBlock);
	void headInsert(dsBlock);
	void traverseList(FILE*, size_t(*write)(const void*, size_t, size_t, FILE*));

}* dsList;

class PartitionIO
{
private:
	header head;
	list block_info;
	dsList dsBlock_info;
	char* partition;

public:
	PartitionIO();
	~PartitionIO();
	void readFile();
	void writeFile();
	void clear();
	void mergeBlock(block);
	void splitBlock(block, unsigned int);

	// 在内存中重建文件模拟内存中的数据结构
	vector<dsPair> dsBlockRealAddressList();
	void dsBlockInsert(DS_CLASS, unsigned int);
	void dsBlockDelete(unsigned int);

	block memAlloc(unsigned int); //内存分配算法选择
	block firstFit(unsigned int); //首次适应算法
	block bestFit(unsigned int); //最佳适应算法
	block worstFit(unsigned int); //最差适应算法

	unsigned int getBlockSize();
	void* calcRealAddress(block);
	void* calcRealAddress(unsigned int);
	unsigned int calcPos(void*);
	signed_size_t calcOffset();
	block findBlock(unsigned int);
};

void* newMalloc(PartitionIO*, DS_CLASS, size_t); // 自实现内存分配函数
void newFree(PartitionIO*, void*); // 自实现内存回收函数 
