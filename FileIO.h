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
#define DEFAULT_BLOCK_SIZE 4 // ��λΪ�ֽ�
#define MEM_ALLOC_ALG FF // �ڴ�����㷨����ѡ��

const int BLOCK_TOTAL_SIZE = 100 * 1024 * 1024;
const unsigned int INF = ~0U;

typedef long long int signed_size_t;

using std::pair;
using std::make_pair;
using std::vector;

enum MEMORY_ALLOCATION_ALGORITHM { FF, BF, WF }; // �ڴ�����㷨����
enum DS_CLASS { NOT_USED, USED, LINKED_LIST }; //���ݽṹ����

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

// ���ݽṹ�Ľṹ��������Զ�������е�λ��
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
	char* prev_part; // �ϴγ�������ʱ partition ���ڴ��еĵ�ַ

	DS_STRUCT_POS_LIST();
	~DS_STRUCT_POS_LIST();

	dsBlock newNode(DS_CLASS, unsigned int);
	void clearList();
	void del(int);
	void del(dsBlock);
	dsBlock locateElem(unsigned int); // �������Զ�������е�λ�� pos ����λ dsBlock
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

	// ���ڴ����ؽ��ļ�ģ���ڴ��е����ݽṹ
	vector<dsPair> dsBlockRealAddressList();
	void dsBlockInsert(DS_CLASS, unsigned int);
	void dsBlockDelete(unsigned int);

	block memAlloc(unsigned int); //�ڴ�����㷨ѡ��
	block firstFit(unsigned int); //�״���Ӧ�㷨
	block bestFit(unsigned int); //�����Ӧ�㷨
	block worstFit(unsigned int); //�����Ӧ�㷨

	unsigned int getBlockSize();
	void* calcRealAddress(block);
	void* calcRealAddress(unsigned int);
	unsigned int calcPos(void*);
	signed_size_t calcOffset();
	block findBlock(unsigned int);
};

void* newMalloc(PartitionIO*, DS_CLASS, size_t); // ��ʵ���ڴ���亯��
void newFree(PartitionIO*, void*); // ��ʵ���ڴ���պ��� 
