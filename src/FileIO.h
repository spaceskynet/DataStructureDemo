/**
 * @file FileIO.h
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief 对数据文件的读写操作，模拟内存的分配与回收，以及对文件中模拟内存在实际内存中结构的重建
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Widgets/ui_MainWindow.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <utility>
#include <vector>
#define F_OK 0
#define DAT_FILE_PATH "./mem.dat"
#define DAT_MAGIC_NUMBER "BIT\xAC"
#define DEFAULT_UNIT_SIZE 4 // 自定义分区划分的单元的默认大小，单位为字节
#define MEM_ALLOC_ALG FF // 内存分配算法类型选择
#define Q_FRINTF_BUFFER_SIZE 1000

const unsigned int PARTITION_TOTAL_SIZE = 100 * 1024 * 1024; // 自定义分区 100 M
const unsigned int INF = ~0U;

typedef long long int signed_size_t;

using std::pair;
using std::make_pair;
using std::vector;

/**
 * @brief 内存分配算法类型
 * 首次适应、最佳适应、最差适应
 */
enum MEMORY_ALLOCATION_ALGORITHM { FF, BF, WF };

/**
 * @brief 数据结构类型
 * 存储在分区信息区，同时是分区块是否空闲的标志
 * (增加新的数据结构需要在这里增加新标志)
 */
enum DS_CLASS { 
	NOT_USED, 
	USED, 
	LINKED_LIST,
	ARRAY,
	STACK,
	HEAP,
	TREE,
	UNDIRECTED_GRAPH,
	DIRECTED_GRAPH,
	// more
};

typedef pair<DS_CLASS, void*> dsPair; // 数据结构类型, 对应类型结构体对象的实际地址

/**
 * @brief 文件头信息，包括文件署名域 、 自定义分区划分的块的大小和内存分配算法
 * 
 */
typedef struct FILE_HEADER
{
	char magic_number[4]; // 文件署名域
	unsigned int unit_size; // 自定义分区划分单元的大小
	MEMORY_ALLOCATION_ALGORITHM alg; // 内存分配算法类型选择
	FILE_HEADER() { setDefault(true); }
	void setDefault(bool);
}*header;


/**
 * @brief 自定义分区的某块的空闲情况
 * 注意连续的空闲单元和非空闲单元默认为一个 BLOCK（后面的操作也会维护这个性质）
 * 这里的 pos 和 size 均是将自定义分区按照 unit_size 分单元后从 0 开始顺序标号得到的
 */
typedef struct BLOCK
{
	DS_CLASS type;
	unsigned int pos, size;	
	BLOCK* prior, * next;
	BLOCK(unsigned int pos, unsigned int size) :type(NOT_USED), pos(pos), size(size), prior(nullptr), next(nullptr) {}
	bool is_free();
}* block;

/**
 * @brief BLOCK 的空闲情况链表（带头结点）
 * 链表的逻辑顺序与 BLOCK 间的顺序一样（这个性质也被维护）
 */
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
	int locateElemIndex(unsigned int);
	void print(block);
	void printAll();
}* plist;

/**
 * @brief 数据结构的结构体对象在自定义分区中的位置
 * 存储这个的目的是为了还原自定义分区里已经建立好的数据结构在内存中的结构
 * 如果数据结构建立后，不销毁就写入文件关闭程序，再次运行时会丢失结构体对象的指针（结构体的成员可以靠对象指针来寻址，故存储结构体对象的指针即可）
 * 也不用实际存储结构体对象的指针，存储结构体对象在自定义分区中块的标号即可
 */
typedef struct DS_STRUCT_POS_BLOCK
{
	DS_CLASS type;
	unsigned int pos;
	DS_STRUCT_POS_BLOCK* prior, * next;
	DS_STRUCT_POS_BLOCK(unsigned int pos):type(NOT_USED), pos(pos), prior(nullptr), next(nullptr) {}
}* dsBlock;


/**
 * @brief 数据结构的结构体对象的标号链表（带头结点）
 * 自然存储上次程序运行时 partition 在内存中的地址
 * 便于计算自定义分区首地址相对上次运行的偏移（用于修正数据结构中的指针变量）
 */
typedef struct DS_STRUCT_POS_LIST
{
	dsBlock head, tail;
	int len;
	char* prev_part; // 上次程序运行时 partition 在内存中的地址

	DS_STRUCT_POS_LIST();
	~DS_STRUCT_POS_LIST();

	dsBlock newNode(DS_CLASS, unsigned int);
	void clearList();
	void del(int);
	void del(dsBlock);
	dsBlock locateElem(unsigned int); // 按照在自定义分区中的标号 pos 来定位 dsBlock
	void insert(int, dsBlock);
	void headInsert(dsBlock);
	void tailInsert(dsBlock);
	void traverseList(FILE*, size_t(*write)(const void*, size_t, size_t, FILE*));
}* dsList;

/**
 * @brief 内存分配回收操作类
 * 完成对内存的分配与回收操作
 */
class PartitionIO
{
private:
	header head;
	plist block_info;
	dsList dsBlock_info;
	char* partition;
	Ui::MainWindow* mainWindow;

public:
	PartitionIO();
	~PartitionIO();

	//初始化结构
	void clear();

	//数据文件的读写操作
	void readFile();
	void writeFile();
	
	// 在内存中重建文件模拟内存中的数据结构
	vector<dsPair> dsBlockRealAddressList();
	void dsBlockInsert(DS_CLASS, unsigned int);
	void dsBlockDelete(unsigned int);

	// 分区信息查询修改相关
	void printBasicInfo();
	void printBlockInfo(unsigned int);
	int getBlockIndex(unsigned int);
	void printBlockInfoAll();
	unsigned int getUnitSize();
	void changeUnitSize(unsigned int);
	unsigned int getFreeUnitSum();
	MEMORY_ALLOCATION_ALGORITHM getMemoryAllocationAlgorithm();
	void changeMemoryAllocationAlgorithm(MEMORY_ALLOCATION_ALGORITHM);


	// 内存分配回收算法相关
	void mergeBlock(block);
	void splitBlock(block, unsigned int);
	block memAlloc(unsigned int); //内存分配算法选择
	block firstFit(unsigned int); //首次适应算法
	block bestFit(unsigned int); //最佳适应算法
	block worstFit(unsigned int); //最差适应算法

	// 地址、标号获取和计算相关
	void* calcRealAddress(block);
	void* calcRealAddress(unsigned int);
	unsigned int calcPos(void*);
	signed_size_t calcOffset();
	block findBlock(unsigned int);

	void setMainWindow(Ui::MainWindow*);
	void updateBlockFreeInfoMainWindow();
	void sendOutput(char*);
	void sendOutput(QString);
};

void* newMalloc(PartitionIO*, DS_CLASS, size_t); // 自实现内存分配函数
void newFree(PartitionIO*, void*); // 自实现内存回收函数
QListWidgetItem* newBlock(char*, DS_CLASS);
int _qprintf(PartitionIO*, const char*, ...);
int qprintf(PartitionIO*, const char*, va_list);
