#pragma once
#include "../FileIO.h"
#include <cstdio>
#include <cstdlib>

#define MYmalloc _malloc
#define MYfree _free
#define MYprintf _printf

class directionGraph
{
    public:

    int vertexNum;
    int edgeNum;

    int startinput[100];
    int endinput[100];
    double weightinput[100];

    bool isinit=false;
    bool isready=false;

    double* weight;
    bool* visited;
    int* result;
    int* branch;
    double* distance;
    double* distancelong;
    int* before;
    int* path;
    int countT;
    int countB;
    int countR;    

    void init_graph(int vertexnum_ = 0, int edgenum_ = 0, int* start = nullptr, int* end = nullptr, double* weight_ = nullptr);
    void isempty()
    {
        if (vertexNum == 0) MYprintf("The graph is empty!\n");
        else displayinfo();
    };
    void add_vertex(int num_);
    void add_edge(int start, int end, double value);
    void reassign_weight(int start, int end, double value);
    void getready();
    void DFS(int inode);
    void BFS(int inode);
    void dijkstra(int inode);
    void floyd();
    void toposort();
    void destroy_graph();
    
    // 自实现内存分配回收时，数据结构结构体需要额外添加的部分
    static PartitionIO* part;

    static void* _malloc(size_t);
    static void _free(void*);
    static int _printf(const char*, ...);

    void recovery(signed_size_t); //将原数据结构中所有指针变量加上 offset
    template<typename T>void addOffset(T& var, signed_size_t offset) {
        var = (T)((char*)var + offset);
    }


    void displayinfo();
    void load_default();
    void show_default();

    private:

    void subDFS(int inode);
    void subBFS();
    void findpath(int inode, int jnode);
};

