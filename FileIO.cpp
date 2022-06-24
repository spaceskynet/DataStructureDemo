/*********************************************************************
 * \file   FileIO.cpp
 * \brief  
 * 
 * \author SpaceSkyNet
 * \date   June 2022
 *********************************************************************/
#include "FileIO.h"
#include <assert.h>
#include <io.h>

PartitionIO::PartitionIO()
{
	head = new FILE_HEADER;
	block_info = new BLOCK_LINKED_LIST;
	dsBlock_info = new DS_STRUCT_POS_LIST;
	partition = (char *)malloc(BLOCK_TOTAL_SIZE);
}

PartitionIO::~PartitionIO()
{
	delete head;
	delete block_info;
	delete dsBlock_info;
	free(partition);
}

void PartitionIO::readFile()
{
	if (_access(DATA_FILE_PATH, F_OK)) 
	{
		clear();
		return;
	}

	FILE* fp = fopen(DATA_FILE_PATH, "rb");
	if (fp == nullptr)
	{
		perror("Cannot open data file!");
		exit(-1);
	}

	// Read Header
	fread(head, sizeof(FILE_HEADER), 1, fp);
	if (!strcmp(head->header, DATA_FILE_HEADER))
	{
		perror("Data file header error!");
		exit(-1);
	}

	// Read & Rebuild `Block Info` Structure
	int block_len = 0;
	fread(&block_len, sizeof(int), 1, fp);
	DS_CLASS type;
	unsigned int pos, size;
	block tail = block_info->head;
	for (int i = 0; i < block_len; ++i)
	{
		fread(&type, sizeof(DS_CLASS), 1, fp);
		fread(&pos, sizeof(unsigned int), 1, fp);
		fread(&size, sizeof(unsigned int), 1, fp);
		tail = block_info->tailInsert(tail, block_info->newNode(type, pos, size));
	}
	assert(block_len == block_info->len);

	// Read & Rebuild `Data Structure Pos Block` Structure
	fread(&block_len, sizeof(int), 1, fp);
	fread(&dsBlock_info->prev_part, sizeof(char*), 1, fp);
	for (int i = 0; i < block_len; ++i)
	{
		fread(&type, sizeof(DS_CLASS), 1, fp);
		fread(&pos, sizeof(unsigned int), 1, fp);
		dsBlock_info->headInsert(dsBlock_info->newNode(type, pos));
	}
	assert(block_len == dsBlock_info->len);

	// Read Partition
	fread(partition, BLOCK_TOTAL_SIZE, 1, fp);
}

void PartitionIO::writeFile()
{
	FILE* fp = fopen(DATA_FILE_PATH, "wb");
	if (fp == nullptr)
	{
		perror("Cannot open data file!");
		exit(-1);
	}

	// Write Header
	fwrite(head, sizeof(FILE_HEADER), 1, fp);
	
	// Write `Block Info` Structure
	fwrite(&block_info->len, sizeof(int), 1, fp);
	block_info->traverseList(fp, fwrite);

	// Write `Data Structure Pos Block` Structure
	fwrite(&dsBlock_info->len, sizeof(int), 1, fp);
	fwrite(&partition, sizeof(char*), 1, fp);
	dsBlock_info->traverseList(fp, fwrite);

	// Write Partition
	fwrite(partition, BLOCK_TOTAL_SIZE, 1, fp);
}

vector<dsPair> PartitionIO::dsBlockRealAddressList()
{
	vector<dsPair> ds_list;
	if (dsBlock_info->len == 0) return ds_list; // ���ݽṹ�Ľṹ��������Զ�������е�λ���б�Ϊ�գ�˵��ģ���ڴ��������ݽṹ
	dsBlock p = dsBlock_info->head;
	while (p->next != nullptr)
	{
		p = p->next;
		ds_list.push_back(make_pair(p->type, calcRealAddress(p->pos)));
	}
	return ds_list;
}

void PartitionIO::dsBlockInsert(DS_CLASS type, unsigned int pos)
{
	dsBlock_info->headInsert(dsBlock_info->newNode(type, pos));
}

void PartitionIO::dsBlockDelete(unsigned int pos)
{
	dsBlock_info->del(dsBlock_info->locateElem(pos));
}

void PartitionIO::clear()
{
	head->setDefault();
	block_info->clearList();
	block_info->tailInsert(block_info->head, block_info->newNode(NOT_USED, 0, BLOCK_TOTAL_SIZE / DEFAULT_BLOCK_SIZE));
	dsBlock_info->clearList();
	memset(partition, 0, BLOCK_TOTAL_SIZE);
}

block PartitionIO::memAlloc(unsigned int size)
{
	switch (MEM_ALLOC_ALG)
	{
		case FF: return firstFit(size);
		case BF: return bestFit(size);
		case WF: return worstFit(size);
		default: return firstFit(size);
	}
}

block PartitionIO::firstFit(unsigned int size)
{
	block p = block_info->head->next;
	while (p != nullptr && !(p->size >= size && p->is_free())) p = p->next;
	
	return p; // ��� p Ϊ nullptr����˵��û�ҵ������� nullptr�����ҵ���p ��Ϊ���ң��򷵻� p. �ɺϲ�
}

block PartitionIO::bestFit(unsigned int size)
{
	block p = block_info->head->next, best = nullptr;
	unsigned int best_size = INF;
	while (p != nullptr)
	{
		if (p->size >= size && p->size < best_size && p->is_free())
		{
			best_size = p->size, best = p;
		}
		p = p->next;
	}

	return best; // ͬ��ɺϲ�
}

block PartitionIO::worstFit(unsigned int size)
{
	block p = block_info->head->next, worst = nullptr;
	unsigned int worst_size = 0;
	while (p != nullptr)
	{
		if (p->size >= size && p->size > worst_size && p->is_free())
		{
			worst_size = p->size, worst = p;
		}
		p = p->next;
	}

	return worst; // ͬ��ɺϲ�
}

unsigned int PartitionIO::getBlockSize()
{
	return this->head->block_size;
}

unsigned int PartitionIO::calcPos(void* Pos)
{
	return ((char*)Pos - this->partition) / head->block_size;
}

signed_size_t PartitionIO::calcOffset()
{
	return (partition - (char*)dsBlock_info->prev_part);
}

block PartitionIO::findBlock(unsigned int pos)
{
	return this->block_info->locateElem(pos);
}

void* PartitionIO::calcRealAddress(block elem)
{
	return (void*)(this->partition + elem->pos * head->block_size);
}

void* PartitionIO::calcRealAddress(unsigned int pos)
{
	return (void*)(this->partition + pos * head->block_size);
}

void PartitionIO::mergeBlock(block elem)
{
	assert(elem != block_info->head);

	block p = elem->prior, tmp = nullptr;
	unsigned int increment = 0, new_pos = elem->pos; // ���пռ�����
	while (p->is_free()) 
	{
		increment += p->size, new_pos = p->pos;
		p = p->prior;
		block_info->del(p->next);
	}

	p = elem->next;
	while (p != nullptr && p->is_free())
	{
		increment += p->size;
		tmp = p, p = p->next;
		block_info->del(tmp);
	}
	
	elem->pos = new_pos;
	elem->size += increment;
}

void PartitionIO::splitBlock(block elem, unsigned int size)
{
	block p = block_info->newNode(NOT_USED, elem->pos + size, elem->size - size);

	p->prior = elem, p->next = elem->next;
	if(elem->next != nullptr) elem->next->prior = p;
	elem->next = p;

	elem->size = size;
	++block_info->len;
}

void* newMalloc(PartitionIO* part, DS_CLASS type, size_t Size)
{
	unsigned int block_size = part->getBlockSize();
	unsigned int size = (Size + block_size - 1) / block_size;
	block elem = part->memAlloc(size);

	if (elem == nullptr) return nullptr; // �����ڷ��ϴ�С���������ÿ��пռ�

	assert(elem->size >= size);
	if (elem->size > size) part->splitBlock(elem, size);
	
	elem->type = type;
	return part->calcRealAddress(elem);
}

void newFree(PartitionIO* part, void* Pos)
{
	unsigned int pos = part->calcPos(Pos);
	block elem = part->findBlock(pos);

	if (elem == nullptr)
	{
		perror("Cannot find the correct block info!");
		return;
	}

	part->mergeBlock(elem);
	elem->type = NOT_USED;
}

BLOCK_LINKED_LIST::BLOCK_LINKED_LIST()
{
	head = newNode(USED, 0, 0); // ͷָ�� is_free ����Ϊ�ǿգ��ںϲ���ʱ����ǰ������һ���ǿտ�ʱ�ɼ����ж�
	len = 0;
}

BLOCK_LINKED_LIST::~BLOCK_LINKED_LIST()
{
	clearList();
	delete head;
}

void BLOCK_LINKED_LIST::clearList()
{
	while (head->next != nullptr) del(1);
	assert(len == 0);
}

block BLOCK_LINKED_LIST::newNode(DS_CLASS type, unsigned int pos, unsigned int size)
{
	block elem = new BLOCK(pos, size);
	if (elem == nullptr) exit(-1);
	elem->type = type;
	return elem;
}

void BLOCK_LINKED_LIST::del(int pos)
{
	block p = head;
	for (int i = 1; i <= pos && p != nullptr; ++i) p = p->next;
	if (p == nullptr) return;

	p->prior->next = p->next;
	if (p->next != nullptr) p->next->prior = p->prior;

	--len;
	delete p;
}

void BLOCK_LINKED_LIST::del(block elem)
{
	block p = elem;

	p->prior->next = p->next;
	if (p->next != nullptr) p->next->prior = p->prior;

	--len;
	delete p;
}

block BLOCK_LINKED_LIST::tailInsert(block tail, block elem)
{
	tail->next = elem;
	elem->prior = tail;

	++len;
	return elem;
}

void BLOCK_LINKED_LIST::traverseList(FILE *fp, size_t(*write)(const void*, size_t, size_t, FILE*))
{
	block p = head;
	while (p->next != nullptr)
	{
		p = p->next;
		write(&p->type, sizeof(DS_CLASS), 1, fp);
		write(&p->pos, sizeof(unsigned int), 1, fp);
		write(&p->size, sizeof(unsigned int), 1, fp);
	}
}

block BLOCK_LINKED_LIST::locateElem(unsigned int pos)
{
	block p = head;
	for (int i = 1; p->next != nullptr; ++i)
	{
		p = p->next;
		if (p->pos == pos) return p;
	}
	return nullptr;
}

void FILE_HEADER::setDefault()
{
	block_size = DEFAULT_BLOCK_SIZE, strncpy(header, DATA_FILE_HEADER, sizeof(header));
}

bool BLOCK::is_free()
{
	return this->type == NOT_USED;
}

DS_STRUCT_POS_LIST::DS_STRUCT_POS_LIST()
{
	head = newNode(USED, 0);
	len = 0;
	prev_part = nullptr;
}

DS_STRUCT_POS_LIST::~DS_STRUCT_POS_LIST()
{
	clearList();
	delete head;
}

dsBlock DS_STRUCT_POS_LIST::newNode(DS_CLASS type, unsigned int pos)
{
	dsBlock elem = new DS_STRUCT_POS_BLOCK(pos);
	if (elem == nullptr) exit(-1);
	elem->type = type;
	return elem;
}

void DS_STRUCT_POS_LIST::clearList()
{
	while (head->next != nullptr) del(1);
	assert(len == 0);
}

void DS_STRUCT_POS_LIST::del(int pos)
{
	dsBlock p = head;
	for (int i = 1; i <= pos && p != nullptr; ++i) p = p->next;
	if (p == nullptr) return;

	p->prior->next = p->next;
	if (p->next != nullptr) p->next->prior = p->prior;

	--len;
	delete p;
}

void DS_STRUCT_POS_LIST::del(dsBlock elem)
{
	dsBlock p = elem;

	p->prior->next = p->next;
	if (p->next != nullptr) p->next->prior = p->prior;

	--len;
	delete p;
}

dsBlock DS_STRUCT_POS_LIST::locateElem(unsigned int pos)
{
	dsBlock p = head;
	for (int i = 1; p->next != nullptr; ++i)
	{
		p = p->next;
		if (p->pos == pos) return p;
	}
	return nullptr;
}

void DS_STRUCT_POS_LIST::insert(int pos, dsBlock elem)
{
	if (pos <= 0) return;
	dsBlock p = head;
	for (int i = 1; i < pos && p != nullptr; i++) p = p->next;
	if (p == nullptr) return;

	elem->next = p->next, elem->prior = p;
	if (p->next != nullptr) p->next->prior = elem;
	p->next = elem;
	
	++len;
}

void DS_STRUCT_POS_LIST::headInsert(dsBlock elem)
{
	insert(1, elem);
}

void DS_STRUCT_POS_LIST::traverseList(FILE* fp, size_t(*write)(const void*, size_t, size_t, FILE*))
{
	dsBlock p = head;
	while (p->next != nullptr)
	{
		p = p->next;
		write(&p->type, sizeof(DS_CLASS), 1, fp);
		write(&p->pos, sizeof(unsigned int), 1, fp);
	}
}
