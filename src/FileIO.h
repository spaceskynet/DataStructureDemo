/**
 * @file FileIO.h
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief �������ļ��Ķ�д�������Լ����ļ���ģ���ڴ���ʵ���ڴ��нṹ���ؽ�
 * @version 0.1
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#define F_OK 0
#define DATA_FILE_PATH "./mem.dat"
#define DATA_FILE_HEADER "BIT\xAC"
#define DEFAULT_BLOCK_SIZE 4 // �Զ���������ֵĿ��Ĭ�ϴ�С����λΪ�ֽ�
#define MEM_ALLOC_ALG FF // �ڴ�����㷨����ѡ��

const int BLOCK_TOTAL_SIZE = 100 * 1024 * 1024; // �Զ������ 100 M
const unsigned int INF = ~0U;

typedef long long int signed_size_t;

using std::pair;
using std::make_pair;
using std::vector;

/**
 * @brief �ڴ�����㷨����
 * �״���Ӧ�������Ӧ�������Ӧ
 */
enum MEMORY_ALLOCATION_ALGORITHM { FF, BF, WF };

/**
 * @brief ���ݽṹ����
 * �洢�ڷ�����Ϣ����ͬʱ�Ƿ������Ƿ���еı�־
 * (�����µ����ݽṹ��Ҫ�����������±�־)
 */
enum DS_CLASS { NOT_USED, USED, LINKED_LIST };

typedef pair<DS_CLASS, void*> dsPair; // ���ݽṹ����, ��Ӧ���ͽṹ������ʵ�ʵ�ַ

/**
 * @brief �ļ�ͷ��Ϣ�������� ID �� �Զ���������ֵĿ�Ĵ�С
 * 
 */
typedef struct FILE_HEADER
{
	char chunk_id[4]; // �� ID
	unsigned int block_size; // �Զ���������ֵĿ�Ĵ�С
	FILE_HEADER() { setDefault(); }
	void setDefault();
}*header;


/**
 * @brief �Զ��������ĳ��Ŀ������
 * ע�������Ŀ��п�ͷǿ��п�Ĭ��Ϊһ�� BLOCK������Ĳ���Ҳ��ά��������ʣ�
 * ����� pos �� size ���ǽ��Զ���������� block_size �ֿ��� 0 ��ʼ˳���ŵõ���
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
 * @brief BLOCK �Ŀ������������ͷ��㣩
 * ������߼�˳���� BLOCK ���˳��һ�����������Ҳ��ά����
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
	void print(block);
	void printAll();
}* list;

/**
 * @brief ���ݽṹ�Ľṹ��������Զ�������е�λ��
 * �洢�����Ŀ����Ϊ�˻�ԭ�Զ���������Ѿ������õ����ݽṹ���ڴ��еĽṹ
 * ������ݽṹ�����󣬲����پ�д���ļ��رճ����ٴ�����ʱ�ᶪʧ�ṹ������ָ�루�ṹ��ĳ�Ա���Կ�����ָ����Ѱַ���ʴ洢�ṹ������ָ�뼴�ɣ�
 * Ҳ����ʵ�ʴ洢�ṹ������ָ�룬�洢�ṹ��������Զ�������п�ı�ż���
 */
typedef struct DS_STRUCT_POS_BLOCK
{
	DS_CLASS type;
	unsigned int pos;
	DS_STRUCT_POS_BLOCK* prior, * next;
	DS_STRUCT_POS_BLOCK(unsigned int pos):type(NOT_USED), pos(pos), prior(nullptr), next(nullptr) {}
}* dsBlock;


/**
 * @brief ���ݽṹ�Ľṹ�����ı��������ͷ��㣩
 * ��Ȼ�洢�ϴγ�������ʱ partition ���ڴ��еĵ�ַ
 * ���ڼ����Զ�������׵�ַ����ϴ����е�ƫ�ƣ������������ݽṹ�е�ָ�������
 */
typedef struct DS_STRUCT_POS_LIST
{
	dsBlock head, tail;
	int len;
	char* prev_part; // �ϴγ�������ʱ partition ���ڴ��еĵ�ַ

	DS_STRUCT_POS_LIST();
	~DS_STRUCT_POS_LIST();

	dsBlock newNode(DS_CLASS, unsigned int);
	void clearList();
	void del(int);
	void del(dsBlock);
	dsBlock locateElem(unsigned int); // �������Զ�������еı�� pos ����λ dsBlock
	void insert(int, dsBlock);
	void headInsert(dsBlock);
	void tailInsert(dsBlock);
	void traverseList(FILE*, size_t(*write)(const void*, size_t, size_t, FILE*));

}* dsList;

/**
 * @brief �ڴ������ղ�����
 * ��ɶ��ڴ�ķ�������ղ���
 */
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

	//��ʼ���ṹ
	void clear();

	//�����ļ��Ķ�д����
	void readFile();
	void writeFile();
	
	// ���ڴ����ؽ��ļ�ģ���ڴ��е����ݽṹ
	vector<dsPair> dsBlockRealAddressList();
	void dsBlockInsert(DS_CLASS, unsigned int);
	void dsBlockDelete(unsigned int);

	// ������Ϣ��ѯ���
	void printBasicInfo();
	void printBlockInfo(unsigned int);
	void printBlockInfoAll();

	// �ڴ��������㷨���
	void mergeBlock(block);
	void splitBlock(block, unsigned int);
	block memAlloc(unsigned int); //�ڴ�����㷨ѡ��
	block firstFit(unsigned int); //�״���Ӧ�㷨
	block bestFit(unsigned int); //�����Ӧ�㷨
	block worstFit(unsigned int); //�����Ӧ�㷨

	// ��ַ����Ż�ȡ�ͼ������
	unsigned int getBlockSize();
	void* calcRealAddress(block);
	void* calcRealAddress(unsigned int);
	unsigned int calcPos(void*);
	signed_size_t calcOffset();
	block findBlock(unsigned int);
};

void* newMalloc(PartitionIO*, DS_CLASS, size_t); // ��ʵ���ڴ���亯��
void newFree(PartitionIO*, void*); // ��ʵ���ڴ���պ��� 
