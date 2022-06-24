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
	partition = (char *)malloc(BLOCK_TOTAL_SIZE);
}

PartitionIO::~PartitionIO()
{
	delete head;
	delete block_info;
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

	// Read & Rebuild Block Info Structure
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
	
	// Write Block Info Structure
	fwrite(&block_info->len, sizeof(int), 1, fp);
	block_info->traverseList(fp, fwrite);

	// Write Partition
	fwrite(partition, BLOCK_TOTAL_SIZE, 1, fp);
}

void PartitionIO::clear()
{
	head->setDefault();
	block_info->clearList();
	block_info->tailInsert(block_info->head, block_info->newNode(NOT_USED, 0, BLOCK_TOTAL_SIZE / DEFAULT_BLOCK_SIZE));
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
	
	return p; // 如果 p 为 nullptr，则说明没找到，返回 nullptr；若找到，p 即为所找，则返回 p. 可合并
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

	return best; // 同理可合并
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

	return worst; // 同理可合并
}

unsigned int PartitionIO::getBlockSize()
{
	return this->head->block_size;
}

unsigned int PartitionIO::calcPos(void* Pos)
{
	return ((char*)Pos - this->partition) / head->block_size;
}

block PartitionIO::findBlock(unsigned int pos)
{
	return this->block_info->locateElem(pos);
}

void* PartitionIO::calcRealAddress(block elem)
{
	return (void*)(this->partition + elem->pos * head->block_size);
}

void PartitionIO::mergeBlock(block elem)
{
	assert(elem != block_info->head);

	block p = elem->prior, tmp = nullptr;
	unsigned int increment = 0, new_pos = elem->pos; // 空闲空间增量
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

	if (elem == nullptr) return nullptr; // 不存在符合大小的连续可用空闲空间

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
	head = newNode(USED, 0, 0); // 头指针 is_free 设置为非空，在合并块时，向前搜索第一个非空块时可减少判断
	len = 0;
}

BLOCK_LINKED_LIST::~BLOCK_LINKED_LIST()
{
	clearList();
	free(head);
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
	while (p->next != NULL)
	{
		p = p->next;
		write(&p->type, sizeof(bool), 1, fp);
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
	return block();
}

void FILE_HEADER::setDefault()
{
	block_size = DEFAULT_BLOCK_SIZE, strncpy(header, DATA_FILE_HEADER, sizeof(header));
}

bool BLOCK::is_free()
{
	return this->type == NOT_USED;
}
