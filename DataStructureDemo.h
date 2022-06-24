#pragma once
#include "FileIO.h"
#include "DataStructure/LinkedList.h"
#include <iostream>
#include <vector>

using std::vector;
class Collection
{
private:
	PartitionIO* part;
	vector<linkedList*> linked_list;

public:
	Collection();
	~Collection();
	void rebuild();
	void singleRebuild(DS_CLASS, void *, signed_size_t);
	void show(DS_CLASS, int);
	void input(DS_CLASS);
	void del(DS_CLASS, int);
};
