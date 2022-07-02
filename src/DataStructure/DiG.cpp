/**
 * @file DiG.cpp
 * @author believable SpaceSkyNet
 * @brief 有向图的实现
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "DiG.h"

const double Inf = 1e200;
const double Infbound = 1e190;
PartitionIO *directionGraph::part = nullptr;

void directionGraph::init_graph(int vertexnum_, int edgenum_, int *start, int *end, double *weight_)
{
    if (isinit)
    {
        MYprintf("Can not initilze the graph again!\n");
    }
    vertexNum = vertexnum_;
    edgeNum = edgenum_;
    for (int i = 0; i < edgenum_; i++)
    {
        startinput[i] = start[i];
        endinput[i] = end[i];
        weightinput[i] = weight_[i];
    }

    isinit = true;
    isready = false;
    weight = nullptr;
    result = nullptr;
    branch = nullptr;
    visited = nullptr;
    before = nullptr;
    distance = nullptr;
    distancelong = nullptr;
    path = nullptr;

    if (vertexNum == 0)
        MYprintf("Successfully initilize an empty directed graph!\n");
    else
        MYprintf("Successfully initilize a directed graph! Vertex number = %d, edge number = %d\n", vertexnum_, edgenum_);
}

void directionGraph::add_vertex(int num_)
{
    if (!isinit)
    {
        MYprintf("Please initialize the graph first!\n");
        return;
    }
    vertexNum += num_;
    isready = false;
    MYprintf("Add new %d vertices to the graph!\n", num_);
}

void directionGraph::add_edge(int start, int end, double value)
{
    if (!isinit)
    {
        MYprintf("Please initialize the graph first!\n");
        return;
    }
    if (edgeNum + 1 >= 100)
    {
        MYprintf("The maximum supported number of edge is 100.\n");
        return;
    }
    if (start >= vertexNum) {
        MYprintf("Illegal start %d. Please use existing vertices only.\n", start);
        return;
    }
    if (end >= vertexNum) {
        MYprintf("Illegal end %d. Please use existing vertices only.\n", end);
        return;
    }
    if (start == end) {
        MYprintf("Don't support loop.\n");
        return;
    }
    startinput[edgeNum] = start;
    endinput[edgeNum] = end;
    weightinput[edgeNum++] = value;
    isready = false;
    MYprintf("Add edge (start:%d end:%d weight:%f) to the graph!\n", start, end, value);
}

void directionGraph::reassign_weight(int start, int end, double value)
{
    bool found = false;
    bool ready = false;
    for (int i = 0; i < edgeNum; i++)
    {
        if (startinput[i] == start && endinput[i] == end)
        {
            found = true;
            weightinput[i] = value;
        }
    }
    if (!found)
    {
        MYprintf("You can not reassign to edges that does not exist.\n");
        return;
    }
    MYprintf("Reset edge weight (start:%d end:%d weight:%f) in the graph!\n", start, end, value);
}

void directionGraph::getready()
{
    if (!isinit)
    {
        MYprintf("Please initialize the graph first!\n");
        return;
    }
    if (isready)
        return;
    if (weight != nullptr)
    {
        MYfree(weight);
        weight = nullptr;
    }
    if (result != nullptr)
    {
        MYfree(result);
        result = nullptr;
    }
    if (visited != nullptr)
    {
        MYfree(result);
        visited = nullptr;
    }
    if (before != nullptr)
    {
        MYfree(result);
        before = nullptr;
    }
    if (distance != nullptr)
    {
        MYfree(result);
        distance = nullptr;
    }
    if (distancelong != nullptr)
    {
        MYfree(result);
        distancelong = nullptr;
    }
    if (path != nullptr)
    {
        MYfree(result);
        path = nullptr;
    }
    if (branch != nullptr)
    {
        MYfree(result);
        branch = nullptr;
    }
    weight = (double *)MYmalloc(vertexNum * vertexNum * sizeof(double));
    result = (int *)MYmalloc(vertexNum * sizeof(int));
    branch = (int *)MYmalloc(vertexNum * sizeof(int));
    visited = (bool *)MYmalloc(vertexNum * sizeof(bool));
    before = (int *)MYmalloc(vertexNum * sizeof(int));
    distance = (double *)MYmalloc(vertexNum * sizeof(double));
    distancelong = (double *)MYmalloc(vertexNum * vertexNum * sizeof(double));
    path = (int *)MYmalloc(vertexNum * vertexNum * sizeof(int));
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
        {
            weight[i * vertexNum + j] = Inf;
        }
    for (int k = 0; k < edgeNum; k++)
    {
        weight[startinput[k] * vertexNum + endinput[k]] = weightinput[k] > 0 ? weightinput[k] : Inf;
    }
    for (int i = 0; i < vertexNum; i++)
    {
        weight[i * vertexNum + i] = 0;
    }
    isready = true;
}

void directionGraph::DFS(int inode)
{
    if (inode >= vertexNum) {
        MYprintf("Illegal node %d\n", inode);
        return;
    }
    if (!isready)
        getready();
    for (int i = 0; i < vertexNum; i++)
    {
        result[i] = 0;
        visited[i] = 0;
        branch[i] = 0;
    }

    countR = 0;
    visited[inode] = true;
    result[countR++] = inode;
    subDFS(inode);

    MYprintf("Deep first search from %d:\n", inode);
    for (int i = 0; i < countR; i++)
    {
        if (i != countR - 1)
            MYprintf("%d->", result[i]);
        else
            MYprintf("%d\n", result[i]);
    }
}

void directionGraph::subDFS(int inode)
{
    if (!isready)
        getready();
    for (int i = vertexNum * inode; i < vertexNum * (inode + 1); i++)
    {
        int jnode = i - vertexNum * inode;
        if (!visited[jnode] && weight[i] < Infbound)
        {
            visited[jnode] = true;
            result[countR++] = jnode;
            subDFS(jnode);
        }
    }
}

void directionGraph::BFS(int inode)
{
    if (inode >= vertexNum) {
        MYprintf("Illegal node %d\n", inode);
        return;
    }
    if (!isready)
        getready();
    for (int i = 0; i < vertexNum; i++)
    {
        result[i] = 0;
        visited[i] = 0;
        branch[i] = 0;
    }

    countR = 0;
    visited[inode] = true;
    result[countR++] = inode;
    subBFS();

    MYprintf("Breadth first search from %d:\n", inode);
    for (int i = 0; i < countR; i++)
    {
        if (i != countR - 1)
            MYprintf("%d->", result[i]);
        else
            MYprintf("%d\n", result[i]);
    }
}

void directionGraph::subBFS()
{
    if (!isready)
        getready();
    int start = 0, add = 0, end = 0;
    while (1)
    {
        start = countR - add - 1;
        end = countR;
        add = 0;
        for (int count2 = start; count2 < end; count2++)
        {
            int inode = result[count2];
            for (int jnode = 0; jnode < vertexNum; jnode++)
            {
                if (!visited[jnode] && weight[inode * vertexNum + jnode] < Infbound)
                {
                    visited[jnode] = true;
                    result[countR++] = jnode;
                    add++;
                }
            }
        }
        if (add == 0)
            break;
    }
}

void directionGraph::dijkstra(int inode)
{
    if (inode >= vertexNum) {
        MYprintf("Illegal node %d\n", inode);
        return;
    }
    if (!isready)
        getready();
    for (int i = 0; i < vertexNum; i++)
    {
        visited[i] = 0;
        before[i] = weight[inode * vertexNum + i] < Infbound ? inode : -1;
        distance[i] = weight[inode * vertexNum + i] < Infbound ? weight[inode * vertexNum + i] : Inf;
        if (i == inode)
        {
            distance[i] = 0;
            visited[i] = 1;
            before[i] = -1;
        }
    }

    for (int i = 0; i < vertexNum; i++)
    {
        double mindist = Inf;
        int minj = -1;
        for (int j = 0; j < vertexNum; j++)
        {
            if (!visited[j] && j != inode && distance[j] < mindist)
            {
                mindist = distance[j];
                minj = j;
            }
        }
        if (minj == -1)
            break;
        else
        {
            distance[minj] = mindist;
            visited[minj] = true;
        }
        for (int k = 0; k < vertexNum; k++)
        {
            if (!visited[k] && weight[minj * vertexNum + k] < Infbound && distance[k] > weight[minj * vertexNum + k] + mindist)
            {
                distance[k] = weight[minj * vertexNum + k] + mindist;
                before[k] = minj;
            }
        }
    }

    MYprintf("Dijkstra shortest path result:\n");
    for (int i = 0; i < vertexNum; i++)
    {
        if (i == inode)
            continue;
        bool connect = true;
        countB = 0;
        int j = i;
        branch[countB++] = j;
        while (1)
        {
            if (before[j] == -1 && j != inode)
            {
                connect = false;
                break;
            }
            if (before[j] == j || j == inode)
                break;
            else
                branch[countB++] = before[j];
            j = before[j];
        }
        if (connect)
        {
            MYprintf("Shortest path from %d to %d is: ", inode, i);
            for (int k = countB - 1; k >= 0; k--)
            {
                if (k != 0)
                    MYprintf("%d->", branch[k]);
                else
                    MYprintf("%d, ", branch[k]);
            }
            MYprintf(" Sum of weight:%f.\n", distance[i]);
        }
        else
            MYprintf("No path from %d to %d.\n", inode, i);
    }
}

void directionGraph::floyd()
{
    if (isempty()) return;
    if (!isready)
        getready();
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            distancelong[i * vertexNum + j] = weight[i * vertexNum + j] < Infbound ? weight[i * vertexNum + j] : Inf;
            path[i * vertexNum + j] = distancelong[i * vertexNum + j] < Infbound ? i : -1; // path from i to j, j's preceed.
        }
    }

    for (int k = 0; k < vertexNum; k++) //拿出每个顶点作为遍历条件
        for (int i = 0; i < vertexNum; i++)
            for (int j = 0; j < vertexNum; j++)
            {
                if ((distancelong[i * vertexNum + j] > distancelong[i * vertexNum + k] + distancelong[k * vertexNum + j]) && distancelong[i * vertexNum + k] < Infbound && distancelong[k * vertexNum + j] < Infbound)
                {
                    distancelong[i * vertexNum + j] = distancelong[i * vertexNum + k] + distancelong[k * vertexNum + j];
                    path[i * vertexNum + j] = k;
                }
            }

    MYprintf("Floyd shortest path result:\n");
    for (int i = 0; i < vertexNum; i++)
    {
        branch[i] = -1;
    }
    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
        {
            bool connect = true;
            if (i == j)
                continue;
            countB = 0;
            branch[countB++] = j;
            int preceed = path[i * vertexNum + j];
            while (preceed != i)
            {
                if (preceed == -1)
                {
                    connect = false;
                    break;
                }
                branch[countB++] = preceed;
                preceed = path[i * vertexNum + preceed];
            }
            if (connect)
            {
                branch[countB] = i;
                MYprintf("Shortest path from %d to %d is: ", i, j);
                MYprintf("%d->", i);
                if (path[i * vertexNum + j] != i)
                    findpath(i, j);
                MYprintf("%d, ", j);
                MYprintf("Sum of weight: %f\n", distancelong[i * vertexNum + j]);
            }
            else
                MYprintf("No path from %d to %d.\n", i, j);
        }
}

void directionGraph::findpath(int inode, int jnode)
{
    if (!isready)
        getready();
    int midpoint = path[inode * vertexNum + jnode];
    // MYprintf("\n* %d %d %d *\n", inode+1, midpoint+1, jnode+1);
    if (weight[inode * vertexNum + midpoint] > Infbound)
        findpath(inode, midpoint);
    MYprintf("%d->", midpoint);
    if (weight[midpoint * vertexNum + jnode] > Infbound)
        findpath(midpoint, jnode);
}

void directionGraph::toposort()
{
    if (isempty()) return;
    if (!isready)
        getready();
    int *in_deg = branch;
    for (int i = 0; i < vertexNum; i++)
    {
        in_deg[i] = 0;
    }
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            if ((i != j) && weight[i * vertexNum + j] < Infbound)
            {
                in_deg[j]++;
            }
        }
    }

    // for (int ii=0;ii<vertexNum;ii++)
    // {
    //     MYprintf("%d ",in_deg[ii]);
    // }
    // MYprintf("\n");

    countR = 0;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            if (in_deg[j] == 0)
            {
                result[countR++] = j;
                in_deg[j] = -1;
                for (int k = 0; k < vertexNum; k++)
                {
                    if ((j != k) && weight[j * vertexNum + k] < Infbound)
                    {
                        in_deg[k]--;
                    }
                }
            }
        }
    }

    MYprintf("Topology-sort result:\n");
    for (int i = 0; i < countR; i++)
    {
        if (i == countR - 1)
            MYprintf("%d\n", result[i]);
        else
            MYprintf("%d->", result[i]);
    }
}

void *directionGraph::_malloc(size_t Size)
{
    if (part == nullptr)
        return nullptr;
    return newMalloc(part, DIRECTED_GRAPH, Size);
}

void directionGraph::_free(void *Pos)
{
    if (part == nullptr)
        return;
    newFree(part, Pos);
}

int directionGraph::_printf(const char *format, ...)
{
    va_list aptr;
    int ret;

    va_start(aptr, format);
    ret = qprintf(part, format, aptr);
    va_end(aptr);
    return ret;
}

void directionGraph::recovery(signed_size_t offset)
{
    addOffset(weight, offset);
    addOffset(distancelong, offset);
    addOffset(path, offset);

    addOffset(result, offset);
    addOffset(branch, offset);
    addOffset(visited, offset);
    addOffset(before, offset);
    addOffset(distance, offset);
}

void directionGraph::destroy_graph()
{
    if (!isready)
        getready();
    if (weight != nullptr)
    {
        MYfree(weight);
        weight = nullptr;
    }
    if (result != nullptr)
    {
        MYfree(result);
        result = nullptr;
    }
    if (visited != nullptr)
    {
        MYfree(visited);
        visited = nullptr;
    }
    if (before != nullptr)
    {
        MYfree(before);
        before = nullptr;
    }
    if (distance != nullptr)
    {
        MYfree(distance);
        distance = nullptr;
    }
    if (distancelong != nullptr)
    {
        MYfree(distancelong);
        distancelong = nullptr;
    }
    if (path != nullptr)
    {
        MYfree(path);
        path = nullptr;
    }
    if (branch != nullptr)
    {
        MYfree(branch);
        branch = nullptr;
    }
    MYprintf("The directed graph is destroyed!\n");
}

void directionGraph::displayinfo()
{
    MYprintf("Graph Information: Vertex number:%d. Edge number:%d\n", vertexNum, edgeNum);
    MYprintf("Edges:\n");
    for (int i = 0; i < edgeNum; ++i)
    {
        MYprintf("%d->%d %llf\n", startinput[i], endinput[i], weightinput[i]);
    }
}

void directionGraph::load_default()
{
    MYprintf("Load default test data......\n");
    int vexnum = 10;
    int edgenum = 11;
    int start[] = {0, 1, 2, 3, 5, 9, 8, 1, 6, 7, 5};
    int end[] = {1, 2, 3, 5, 9, 8, 1, 6, 7, 5, 4};
    double value[] = {1, 2, 3, 5, 3, 2, 1, 6, 0.2, 0.1, 1};
    init_graph(vexnum, edgenum, &start[0], &end[0], &value[0]);
    add_edge(6, 5, 3);
    add_vertex(2);
    add_edge(10, 11, 2);
    add_edge(9, 10, 1);
    add_edge(10, 7, 0.1);
    MYprintf("Done.\n");
    displayinfo();
};

void directionGraph::show_default()
{
    MYprintf("Display default test data......\n");
    for (int i = 0; i < vertexNum; i++)
    {
        MYprintf("Starting from vertex %d:\n", i);
        DFS(i);
        BFS(i);
        dijkstra(i);
    }
    floyd();
    toposort();
    MYprintf("Done.\n");
};