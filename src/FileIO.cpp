/**
 * @file FileIO.cpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-06-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "FileIO.h"
#include <assert.h>
#include <QFileInfo>

/**
 * @brief 数据结构中文名称
 * 
 */
const char* DS_CLASS_STR[] = { 
	"空闲", 
	"已使用", 
	"链表",
	"数组",
	"栈",
	"堆",
	"树",
	"无向图",
	"有向图",
	// more data structure
};

/**
 * @brief 分区空闲情况 UI 显示颜色
 * 
 */
const QColor DS_COLORS[] = {
	QColor(0, 255, 0, 255), // 空闲，Green
	QColor(255, 0, 0, 255), // 已使用，Red
	QColor(255, 138, 217),	// 链表
	QColor(152, 255, 237),	// 数组
	QColor(183, 185, 255),	// 栈
	QColor(220, 255, 108),	// 堆
	QColor(255, 81, 94),	// 树
	QColor(255, 168, 117),	// 无向图
	QColor(255, 240, 53),	// 有向图
	// more data structure					
};

PartitionIO::PartitionIO()
{
	head = new FILE_HEADER;
	block_info = new BLOCK_LINKED_LIST;
	dsBlock_info = new DS_STRUCT_POS_LIST;
	partition = new char[PARTITION_TOTAL_SIZE];
	mainWindow = nullptr;
}

PartitionIO::~PartitionIO()
{
	delete head;
	delete block_info;
	delete dsBlock_info;
	delete[] partition;
}

/**
 * @brief 从数据文件中读取分区信息和自定义分区的数据
 *
 */
void PartitionIO::readFile()
{
	// 如果不存在数据文件，说明首次运行，初始化结构
	QFileInfo fi(DAT_FILE_PATH);
	if (!fi.isFile())
	{
		clear();
		return;
	}

	// 否则从数据文件中读取
	FILE* fp = fopen(DAT_FILE_PATH, "rb");
	if (fp == nullptr)
	{
		perror("Cannot open data file!");
		exit(-1);
	}

	// 读取 Header 和 block_size
	fread(head, sizeof(FILE_HEADER), 1, fp);
	if (!strcmp(head->magic_number, DAT_MAGIC_NUMBER))
	{
		perror("Dat file magic number error!");
		exit(-1);
	}
	// 如果单元大小非法，则重置，并清空分区
	if (head->unit_size <= 0 || head->unit_size > MAX_UNIT_SIZE)
	{
		head->unit_size = DEFAULT_UNIT_SIZE;
		clear();
		return;
	}

	// 读取并重建 BLOCK 的空闲情况链表的结构
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

	// 读取并重建 数据结构的结构体对象的标号链表 的结构
	fread(&block_len, sizeof(int), 1, fp);
	fread(&dsBlock_info->prev_part, sizeof(char*), 1, fp);
	for (int i = 0; i < block_len; ++i)
	{
		fread(&type, sizeof(DS_CLASS), 1, fp);
		fread(&pos, sizeof(unsigned int), 1, fp);
		dsBlock_info->tailInsert(dsBlock_info->newNode(type, pos));
	}
	assert(block_len == dsBlock_info->len);

	// 读取自定义分区的数据
	fread(partition, PARTITION_TOTAL_SIZE, 1, fp);
}

/**
 * @brief 将分区信息写入数据文件
 * 
 */
void PartitionIO::writeFile()
{
	FILE* fp = fopen(DAT_FILE_PATH, "wb");
	if (fp == nullptr)
	{
		perror("Cannot open data file!");
		exit(-1);
	}

	// 写入 Header 和 block_size
	fwrite(head, sizeof(FILE_HEADER), 1, fp);

	// 写入 BLOCK 的空闲情况链表的结构
	fwrite(&block_info->len, sizeof(int), 1, fp);
	block_info->traverseList(fp, fwrite);

	// 写入 数据结构的结构体对象的标号链表 的结构
	fwrite(&dsBlock_info->len, sizeof(int), 1, fp);
	fwrite(&partition, sizeof(char*), 1, fp);
	dsBlock_info->traverseList(fp, fwrite);

	// 写入自定义分区的数据
	fwrite(partition, PARTITION_TOTAL_SIZE, 1, fp);
}

/**
 * @brief 将数据结构的结构体对象的标号链表 转化为 vector<数据结构类型, 对应类型结构体对象的实际地址>，便于重建数据结构
 *
 * @return vector<dsPair>
 */
vector<dsPair> PartitionIO::dsBlockRealAddressList()
{
	vector<dsPair> ds_list;
	if (dsBlock_info->len == 0) return ds_list; // 数据结构的结构体对象在自定义分区中的位置列表为空，说明模拟内存中无数据结构
	dsBlock p = dsBlock_info->head;
	while (p->next != nullptr)
	{
		p = p->next;
		ds_list.push_back(make_pair(p->type, calcRealAddress(p->pos)));
	}
	return ds_list;
}

/**
 * @brief 将新建立的数据结构结构体对象插入数据结构的结构体对象的标号链表
 *
 * @param type 数据结构类型
 * @param pos 数据结构结构体对象在自定义分区中的标号
 */
void PartitionIO::dsBlockInsert(DS_CLASS type, unsigned int pos)
{
	dsBlock_info->tailInsert(dsBlock_info->newNode(type, pos));
}

/**
 * @brief 销毁数据结构结构体对象时，从数据结构的结构体对象的标号链表中删除
 *
 * @param pos 数据结构结构体对象在自定义分区中的标号
 */
void PartitionIO::dsBlockDelete(unsigned int pos)
{
	dsBlock_info->del(dsBlock_info->locateElem(pos));
}

void PartitionIO::printBasicInfo()
{
	printf("Block size: %d byte\n", head->unit_size);
	printf("Number of blocks: %d\n", PARTITION_TOTAL_SIZE / head->unit_size);
}

void PartitionIO::printBlockInfo(unsigned int pos)
{
	block elem = block_info->locateElem(pos);
	if (elem != nullptr) block_info->print(elem);
	else printf("Illegal pos!\n");
}

void PartitionIO::printPartitionAddress()
{
	_qprintf(this, "本次分区首地址为：0x%p\n", partition);
}

int PartitionIO::getBlockIndex(unsigned int pos)
{
	int index = block_info->locateElemIndex(pos);
	return index;
}

void PartitionIO::printBlockInfoAll()
{
	block_info->printAll();
}

void PartitionIO::changeUnitSize(unsigned int new_size)
{
	if (new_size <= 0 || new_size > MAX_UNIT_SIZE) return;
	head->unit_size = new_size;
	this->clear();
}

unsigned int PartitionIO::getFreeUnitSum()
{
	block p = block_info->head;
	unsigned int free_unit_sum = 0;
	while (p->next != nullptr)
	{
		p = p->next;
		free_unit_sum += p->is_free() ? p->size : 0;
	}
	return free_unit_sum;
}

MEMORY_ALLOCATION_ALGORITHM PartitionIO::getMemoryAllocationAlgorithm()
{
	return head->alg;
}

void PartitionIO::changeMemoryAllocationAlgorithm(MEMORY_ALLOCATION_ALGORITHM alg)
{
	head->alg = alg;
}

/**
 * @brief 初始化分区信息
 * 在没有数据文件或者改变了 block_size 时调用
 */
void PartitionIO::clear()
{
	head->setDefault(false); // 这里不重置 unit_size 为 default
	block_info->clearList();
	block_info->tailInsert(block_info->head, block_info->newNode(NOT_USED, 0, PARTITION_TOTAL_SIZE / head->unit_size));
	dsBlock_info->clearList();
	memset(partition, 0, PARTITION_TOTAL_SIZE);
}

/**
 * @brief 选择内存分配算法
 *
 * @param size 需要的连续块大小
 * @return block 满足要求的 BLOCK 的指针
 */
block PartitionIO::memAlloc(unsigned int size)
{
	switch (head->alg)
	{
		case FF: return firstFit(size);
		case BF: return bestFit(size);
		case WF: return worstFit(size);
		default: return firstFit(size);
	}
}

/**
 * @brief 首次适应算法 (FirstFit)
 *
 * @param size
 * @return block
 */
block PartitionIO::firstFit(unsigned int size)
{
	block p = block_info->head->next;
	while (p != nullptr && !(p->size >= size && p->is_free())) p = p->next;

	return p; // 如果 p 为 nullptr，则说明没找到，返回 nullptr；若找到，p 即为所找，则返回 p. 可合并
}

/**
 * @brief 最佳适应算法 (BestFit)
 *
 * @param size
 * @return block
 */
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

/**
 * @brief 最差适应算法 (WorstFit)
 *
 * @param size
 * @return block
 */
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

unsigned int PartitionIO::getUnitSize()
{
	return this->head->unit_size;
}

/**
 * @brief 根据实际地址计算在自定义分区中的标号
 *
 * @param ptr
 * @return unsigned int
 */
unsigned int PartitionIO::calcPos(void* ptr)
{
	return ((char*)ptr - this->partition) / head->unit_size;
}

/**
 * @brief 自定义分区首地址相对上次运行的偏移（用于修正数据结构中的指针变量）
 * new - old
 * @return signed_size_t
 */
signed_size_t PartitionIO::calcOffset()
{
	return (partition - (char*)dsBlock_info->prev_part);
}

/**
 * @brief 根据在自定义分区中的标号唯一确定 BLOCK
 * 一个块不可能被多个 BLOCK 包含
 * @param pos
 * @return block
 */
block PartitionIO::findBlock(unsigned int pos)
{
	return this->block_info->locateElem(pos);
}

void PartitionIO::setMainWindow(Ui::MainWindow* mainWindow)
{
	this->mainWindow = mainWindow;
}

/**
 * @brief 更新 UI 界面空闲块信息
 * 
 */
void PartitionIO::updateBlockFreeInfoMainWindow()
{
	// 更新空闲单元块列表
	mainWindow->blockFreeInfoListWidget->clear(); // 先清空

	block p = block_info->head;
	char addr_range[30];
	while (p->next != nullptr)
	{
		p = p->next;
		sprintf(addr_range, "%09d - %09d", p->pos, p->pos + p->size);
		mainWindow->blockFreeInfoListWidget->addItem(newBlock(addr_range, p->type));
	}

	// 空闲单元总数
	unsigned int free_unit_sum = this->getFreeUnitSum();
	mainWindow->freeUnitSumSpinBox->setValue(free_unit_sum);
}

/**
 * @brief 重定向输出到 UI 界面的输出窗口
 * 
 * @param output 
 */
void PartitionIO::sendOutput(char* output)
{
	this->sendOutput(QString::fromUtf8(output));
}

void PartitionIO::sendOutput(QString output)
{
	QTextCursor tc = mainWindow->outputInfoTextEdit->textCursor();
	tc.movePosition(QTextCursor::End);
	tc.insertText(output);
	mainWindow->outputInfoTextEdit->moveCursor(QTextCursor::End);
}

/**
 * @brief 通过在自定义分区中的标号计算实际地址
 *
 * @param elem
 * @return void*
 */
void* PartitionIO::calcRealAddress(block elem)
{
	return (void*)(this->partition + elem->pos * head->unit_size);
}
void* PartitionIO::calcRealAddress(unsigned int pos)
{
	return (void*)(this->partition + pos * head->unit_size);
}

/**
 * @brief 回收空间时合并 BLOCK，向前后两个方向搜索
 * 当回收空间时，可能导致原本不相邻的空闲 BLOCK 通过这个回收的空闲 BLOCK 相邻，故需要合并操作维护性质
 * @param elem
 */
void PartitionIO::mergeBlock(block elem)
{
	assert(elem != block_info->head);

	block p = elem->prior, tmp = nullptr;
	unsigned int increment = 0, new_pos = elem->pos; // 空闲空间增量
	if (p->is_free())
	{
		increment += p->size, new_pos = p->pos;
		p = p->prior;
		block_info->del(p->next);
	}

	p = elem->next;
	if (p != nullptr && p->is_free())
	{
		increment += p->size;
		tmp = p, p = p->next;
		block_info->del(tmp);
	}

	elem->pos = new_pos;
	elem->size += increment;
}

/**
 * @brief 分配空间时，分裂 BLOCK，得到基于 block_size 的最小满足条件的块和剩余部分
 *
 * @param elem
 * @param size
 */
void PartitionIO::splitBlock(block elem, unsigned int size)
{
	block p = block_info->newNode(NOT_USED, elem->pos + size, elem->size - size);

	p->prior = elem, p->next = elem->next;
	if (elem->next != nullptr) elem->next->prior = p;
	elem->next = p;

	elem->size = size;
	++block_info->len;
}

/**
 * @brief 自实现内存分配函数
 *
 * @param part
 * @param type
 * @param Size
 * @return void*
 */
void* newMalloc(PartitionIO* part, DS_CLASS type, size_t Size)
{
	if (Size <= 0) return nullptr;
	unsigned int block_size = part->getUnitSize();
	unsigned int size = (Size + block_size - 1) / block_size;
	block elem = part->memAlloc(size);

	if (elem == nullptr) {
		_qprintf(part, "空闲空间不足，无法完成分配!\n");
		return nullptr; // 不存在符合大小的连续可用空闲空间
	}

	assert(elem->size >= size);

	if (elem->size > size) part->splitBlock(elem, size);

	elem->type = type;
	void* real_addr = part->calcRealAddress(elem);

	part->updateBlockFreeInfoMainWindow();

	_qprintf(part, "%s申请了 %d 字节的空间，使用了 %d 个单元，第一个单元标号为 %d，实际首地址为 0x%p.\n", DS_CLASS_STR[type], Size, size, elem->pos, real_addr);

	return real_addr;
}

/**
 * @brief 自实现内存回收函数
 *
 * @param part
 * @param Pos
 */
void newFree(PartitionIO* part, void* ptr)
{
	if (ptr == nullptr) return;
	unsigned int pos = part->calcPos(ptr);
	block elem = part->findBlock(pos);

	if (elem == nullptr)
	{
		perror("Cannot find the correct block info!");
		_qprintf(part, "无法找到对应的非空闲块!\n");
		return;
	}

	memset(ptr, 0, 1ll * elem->size * part->getUnitSize());
	_qprintf(part, "%s释放了 %d 个单元，第一个单元标号为 %d，实际首地址为 0x%p.\n", DS_CLASS_STR[elem->type], elem->size, pos, ptr);

	part->mergeBlock(elem);
	elem->type = NOT_USED;

	part->updateBlockFreeInfoMainWindow();
}
/**
 * @brief UI 界面分区空闲情况新 Block 创建
 * 
 * @param addr_range 块所包含的单元的范围，左闭右开
 * @param type 
 * @return QListWidgetItem* 
 */
QListWidgetItem* newBlock(char* addr_range, DS_CLASS type)
{
	QBrush COLOR(DS_COLORS[type]);
	COLOR.setStyle(Qt::Dense1Pattern);

	QListWidgetItem* __qlistwidgetitem = new QListWidgetItem();
	__qlistwidgetitem->setText(QString::fromUtf8(addr_range));
	if(type == NOT_USED) 
		__qlistwidgetitem->setToolTip(QString::fromUtf8(DS_CLASS_STR[type]));
	else
		__qlistwidgetitem->setToolTip(QString::fromUtf8(DS_CLASS_STR[type]) + QString::fromUtf8("已使用"));
	__qlistwidgetitem->setTextAlignment(Qt::AlignCenter);
	__qlistwidgetitem->setBackground(COLOR);
	return __qlistwidgetitem;
}

/**
 * @brief 重新实现 printf，使得输出重定向到 UI 界面的输出窗口
 * 
 * @param part 
 * @param format 
 * @param ... 
 * @return int 
 */
int _qprintf(PartitionIO* part, const char* format, ...)
{
	va_list aptr;
	int ret;

	va_start(aptr, format);
	ret = qprintf(part, format, aptr);
	va_end(aptr);
	return ret;
}

int qprintf(PartitionIO* part, const char* format, va_list aptr)
{
	char* buffer = new char[Q_FRINTF_BUFFER_SIZE];
	int ret;

	ret = vsprintf(buffer, format, aptr);

	part->sendOutput(buffer);
	delete[] buffer;
	return ret;
}


BLOCK_LINKED_LIST::BLOCK_LINKED_LIST()
{
	head = newNode(USED, 0, 0); // 头指针 is_free 设置为非空，在合并块时，向前搜索第一个非空块时可减少判断
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

void BLOCK_LINKED_LIST::traverseList(FILE* fp, size_t(*write)(const void*, size_t, size_t, FILE*))
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
		if (p->pos <= pos && p->pos + p->size > pos) return p;
	}
	return nullptr;
}

int BLOCK_LINKED_LIST::locateElemIndex(unsigned int pos)
{
	block p = head;
	for (int i = 1; p->next != nullptr; ++i)
	{
		p = p->next;
		if (p->pos <= pos && p->pos + p->size > pos) return i - 1;
	}
	return -1;
}

void BLOCK_LINKED_LIST::print(block elem)
{
	printf("%08d - %08d:\t", elem->pos, elem->pos + elem->size);
	if (elem->is_free()) printf("free");
	else printf("used by %s", DS_CLASS_STR[elem->type]);
	putchar('\n');
}

void BLOCK_LINKED_LIST::printAll()
{
	block p = head;
	while (p->next != nullptr)
	{
		p = p->next;
		print(p);
	}
}


void FILE_HEADER::setDefault(bool is_set_default)
{
	if (is_set_default) {
		unit_size = DEFAULT_UNIT_SIZE;
		alg = MEM_ALLOC_ALG;
	}
	strncpy(magic_number, DAT_MAGIC_NUMBER, sizeof(magic_number));
}

bool BLOCK::is_free()
{
	return this->type == NOT_USED;
}

DS_STRUCT_POS_LIST::DS_STRUCT_POS_LIST()
{
	head = newNode(USED, 0);
	tail = head;
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
	assert(head == tail);
}

void DS_STRUCT_POS_LIST::del(int pos)
{
	dsBlock p = head;
	for (int i = 1; i <= pos && p != nullptr; ++i) p = p->next;
	if (p == nullptr) return;

	p->prior->next = p->next;
	if (p != tail) p->next->prior = p->prior;
	else tail = p->prior;

	--len;
	delete p;
}

void DS_STRUCT_POS_LIST::del(dsBlock elem)
{
	dsBlock p = elem;

	p->prior->next = p->next;
	if (p != tail) p->next->prior = p->prior;
	else tail = p->prior;

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
	if (p != tail) p->next->prior = elem;
	else tail = elem;
	p->next = elem;

	++len;
}

void DS_STRUCT_POS_LIST::headInsert(dsBlock elem)
{
	insert(1, elem);
}

void DS_STRUCT_POS_LIST::tailInsert(dsBlock elem)
{
	elem->prior = tail;
	tail->next = elem;
	tail = elem;

	++len;
	return;
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

