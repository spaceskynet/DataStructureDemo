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
#define DEFAULT_BLOCK_SIZE 4 //��λ�ֽ�
#define MEM_ALLOC_ALG FF

const int BLOCK_TOTAL_SIZE = 100 * 1024 * 1024;
const unsigned int INF = ~0U;

enum MEMORY_ALLOCATION_ALGORITHM { FF, BF, WF }; // �ڴ�����㷨
enum DS_CLASS { NOT_USED, USED, LINKED_LIST }; //���ݽṹ����

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

	block memAlloc(unsigned int); //�ڴ�����㷨ѡ��
	block firstFit(unsigned int); //�״���Ӧ�㷨
	block bestFit(unsigned int); //�����Ӧ�㷨
	block worstFit(unsigned int); //�����Ӧ�㷨

	unsigned int getBlockSize();
	void* calcRealAddress(block);
	unsigned int calcPos(void*);
	block findBlock(unsigned int);
};

void* newMalloc(PartitionIO*, DS_CLASS, size_t); // ��ʵ���ڴ���亯��
void newFree(PartitionIO*, void*); // ��ʵ���ڴ���պ��� 
