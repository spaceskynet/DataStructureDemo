/**
 * @file UndiG.cpp
 * @author believable
 * @brief 无向图的实现
 * @version 0.1
 * @date 2022-06-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "UndiG.h"

const double Inf = 1e200;
const double Infbound = 1e190;
PartitionIO *undirectionGraph::part = nullptr;

void undirectionGraph::init_graph(int vertexnum_, int edgenum_, int *start, int *end, double *weight_)
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
    startlong = nullptr;
    endlong = nullptr;
    indexlong = nullptr;

    if (vertexNum == 0)
        MYprintf("Successfully initilize an empty undirected graph!\n");
    else
        MYprintf("Successfully initilize an undirected graph! Vertex number = %d, edge number = %d\n", vertexnum_, edgenum_);
}

void undirectionGraph::add_vertex(int num_)
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

void undirectionGraph::add_edge(int start, int end, double value)
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
    startinput[edgeNum] = start;
    endinput[edgeNum] = end;
    weightinput[edgeNum++] = value;
    isready = false;
    MYprintf("Add edge (start:%d end:%d weight:%f) to the graph!\n", start, end, value);
}

void undirectionGraph::reassign_weight(int start, int end, double value)
{
    bool found = false;
    bool ready = false;
    for (int i = 0; i < edgeNum; i++)
    {
        if ((startinput[i] == start && endinput[i] == end) ||
            (startinput[i] == end && endinput[i] == start))
        {
            found = true;
            weightinput[i] = value;
            break;
        }
    }
    if (!found)
    {
        MYprintf("You can not reassign to edges that does not exist.\n");
    }
    MYprintf("Reset edge weight (start:%d end:%d weight:%f) in the graph!\n", start, end, value);
}

void undirectionGraph::getready()
{
    if (!isinit)
    {
        MYprintf("Please initialize the graph first!\n");
        return;
    }
    if (isready)
        return;

    if (weight != nullptr)
        MYfree(weight);
    if (result != nullptr)
        MYfree(result);
    if (visited != nullptr)
        MYfree(visited);
    if (before != nullptr)
        MYfree(before);
    if (distance != nullptr)
        MYfree(distance);
    if (distancelong != nullptr)
        MYfree(distancelong);
    if (path != nullptr)
        MYfree(path);
    if (branch != nullptr)
        MYfree(branch);
    if (startlong != nullptr)
        MYfree(startlong);
    if (endlong != nullptr)
        MYfree(endlong);
    if (indexlong != nullptr)
        MYfree(indexlong);
    weight = (double *)MYmalloc(vertexNum * vertexNum * sizeof(double));
    result = (int *)MYmalloc(vertexNum * sizeof(int));
    branch = (int *)MYmalloc(vertexNum * sizeof(int));
    visited = (bool *)MYmalloc(vertexNum * sizeof(bool));
    before = (int *)MYmalloc(vertexNum * sizeof(int));
    distance = (double *)MYmalloc(vertexNum * sizeof(double));
    distancelong = (double *)MYmalloc(vertexNum * vertexNum * sizeof(double));
    path = (int *)MYmalloc(vertexNum * vertexNum * sizeof(int));
    startlong = (int *)MYmalloc(vertexNum * vertexNum * sizeof(int));
    endlong = (int *)MYmalloc(vertexNum * vertexNum * sizeof(int));
    indexlong = (int *)MYmalloc(vertexNum * vertexNum * sizeof(int));

    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
        {
            weight[i * vertexNum + j] = Inf;
        }
    for (int k = 0; k < edgeNum; k++)
    {
        weight[startinput[k] * vertexNum + endinput[k]] = weight[endinput[k] * vertexNum + startinput[k]] =
            weightinput[k] > 0 ? weightinput[k] : Inf;
    }
    for (int i = 0; i < vertexNum; i++)
    {
        weight[i * vertexNum + i] = 0;
    }
    isready = true;
}

// void undirectionGraph::global_DFS()
// {
//     MYprintf("Global deep first search result:\n");
//     for (int i=0;i<vertexNum;i++)
//     {
//         if (!visited[i]) DFS(i);
//     }
// }

void undirectionGraph::DFS(int inode)
{
    // if (!isready)
    // {
    //     MYprintf("Please make the graph ready first!\n");
    //     return;
    // }
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

void undirectionGraph::subDFS(int inode)
{
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

// void undirectionGraph::global_BFS()
// {
//     MYprintf("Global breadth first search result:\n");
//     for (int i=0;i<vertexNum;i++)
//     {
//         if (!visited[i]) BFS(i);
//     }
// }

void undirectionGraph::BFS(int inode)
{
    // if (!isready)
    // {
    //     MYprintf("Please make the graph ready first!\n");
    //     return;
    // }
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

void undirectionGraph::subBFS()
{
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

void undirectionGraph::dijkstra(int inode)
{
    // if (!isready)
    // {
    //     MYprintf("Please make the graph ready first!\n");
    //     return;
    // }
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
            before[i] = i;
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
            if (before[j] == -1)
            {
                connect = false;
                break;
            }
            if (before[j] == j)
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
            MYprintf("Sum of weight:%f.\n", distance[i]);
        }
        else
            MYprintf("No path from %d to %d.\n", inode, i);
    }
}

void undirectionGraph::floyd()
{
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

void undirectionGraph::findpath(int inode, int jnode)
{
    int midpoint = path[inode * vertexNum + jnode];
    // MYprintf("\n* %d %d %d *\n", inode+1, midpoint+1, jnode+1);
    if (weight[inode * vertexNum + midpoint] > Infbound)
        findpath(inode, midpoint);
    MYprintf("%d->", midpoint);
    if (weight[midpoint * vertexNum + jnode] > Infbound)
        findpath(midpoint, jnode);
}

void undirectionGraph::prim()
{
    // if (!isready)
    // {
    //     MYprintf("Please make the graph ready first!\n");
    //     return;
    // }
    if (!isready)
        getready();
    double *lowcost = distance;
    int *mst = result;
    /*
        lowcost[i]记录以i为终点的边的最小权值，当lowcost[i]=0时表示终点i加入生成树
        mst[i]记录对应lowcost[i]的起点，当mst[i]=-1时表示终点i加入生成树
    */

    for (int i = 1; i < vertexNum; i++)
    {
        lowcost[i] = weight[i] < Infbound ? weight[i] : Inf;
        mst[i] = weight[i] < Infbound ? 0 : -1;
    }

    double sum = 0;
    for (int i = 1; i < vertexNum; i++)
    {
        double mincost = Inf;
        int minid = -1;
        for (int j = 1; j < vertexNum; j++)
        {
            if (lowcost[j] < mincost && lowcost[j] > 1e-8 && lowcost[j] < Infbound)
            {
                mincost = lowcost[j];
                minid = j;
            }
        }

        if (minid == -1)
        {
            MYprintf("Prim minimum spanning tree result:\n The graph is not connected, the minimum spanning tree does not exist!\n");
            return;
        }

        sum += mincost;
        lowcost[minid] = 0;

        for (int j = 1; j < vertexNum; j++)
        {
            if (lowcost[j] > 1e-8 && weight[minid * vertexNum + j] < lowcost[j] && weight[minid * vertexNum + j] < Infbound)
            {
                lowcost[j] = weight[minid * vertexNum + j];
                mst[j] = minid;
            }
        }
    }

    MYprintf("Prim minimum spanning tree result:\n");
    for (int i = 1; i < vertexNum; i++)
    {
        // if (i == inode) continue;
        if (lowcost[i] <= 1e-8 && lowcost[i] >= -1e-8)
            MYprintf("(%d,%d) ", mst[i], i);
    }
    MYprintf("\n");
    MYprintf("Sum of weight:%f\n", sum);
}

void undirectionGraph::kruskal()
{
    // if (!isready)
    // {
    //     MYprintf("Please make the graph ready first!\n");
    //     return;
    // }
    if (!isready)
        getready();
    int *head = branch;
    int *start = startlong;
    int *end = endlong;
    int *index = indexlong;

    countT = 0;
    for (int i = 0; i < vertexNum; i++)
    {
        head[i] = i;
        for (int j = i + 1; j < vertexNum; j++)
        {
            if (weight[i * vertexNum + j] < Infbound)
            {
                distancelong[countT] = weight[i * vertexNum + j];
                start[countT] = i;
                end[countT] = j;
                index[countT++] = -1;
            }
        }
    }

    // sort
    for (int i = 0; i < countT; i++)
    {
        int minindex = -1;
        double mindist = Infbound;
        for (int j = 0; j < countT; j++)
        {
            if (distancelong[j] < mindist)
            {
                mindist = distancelong[j];
                minindex = j;
            }
        }
        index[i] = minindex;
        distancelong[minindex] = Inf;
    }

    MYprintf("Kruskal result:\n");
    countB = 0;
    for (int i = 0; i < countT; i++)
    {
        int h1 = findhead(head, start[index[i]]);
        int h2 = findhead(head, end[index[i]]);
        if (h1 != h2)
        {
            // MYprintf("(%d, %d) ", start[index[i]], end[index[i]]);
            head[start[index[i]]] = h1;
            head[end[index[i]]] = h1;
            head[h2] = h1;
            result[countB++] = i;
        }
    }
    if (countB != vertexNum - 1)
    {
        MYprintf("Not enough edges to form a minimum spanning tree.\n");
    }
    else
    {
        double sum = 0;
        for (int i = 0; i < countB; i++)
        {
            sum += weight[start[index[result[i]]] * vertexNum + end[index[result[i]]]];
            MYprintf("(%d,%d) ", start[index[result[i]]], end[index[result[i]]]);
        }
        MYprintf("\nSum of weight:%f\n", sum);
    }
}

int undirectionGraph::findhead(int *head, int inode)
{
    while (inode != head[inode])
        inode = head[inode];
    return inode;
}

void *undirectionGraph::_malloc(size_t Size)
{
    if (part == nullptr)
        return nullptr;
    return newMalloc(part, UNDIRECTED_GRAPH, Size);
}

void undirectionGraph::_free(void *Pos)
{
    if (part == nullptr)
        return;
    newFree(part, Pos);
}

int undirectionGraph::_printf(const char *format, ...)
{
    va_list aptr;
    int ret;

    va_start(aptr, format);
    ret = qprintf(part, format, aptr);
    va_end(aptr);
    return ret;
}

void undirectionGraph::recovery(signed_size_t offset)
{
    addOffset(weight, offset);
    addOffset(distancelong, offset);
    addOffset(startlong, offset);
    addOffset(endlong, offset);
    addOffset(indexlong, offset);
    addOffset(path, offset);

    addOffset(result, offset);
    addOffset(branch, offset);
    addOffset(visited, offset);
    addOffset(before, offset);
    addOffset(distance, offset);
}

void undirectionGraph::destroy_graph()
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
    if (startlong != nullptr)
    {
        MYfree(startlong);
        startlong = nullptr;
    }
    if (endlong != nullptr)
    {
        MYfree(endlong);
        endlong = nullptr;
    }
    if (indexlong != nullptr)
    {
        MYfree(indexlong);
        indexlong = nullptr;
    }
    MYprintf("The undirected graph is destroyed!\n");
}

void undirectionGraph::displayinfo()
{
    MYprintf("Graph Information: Vertex number:%d. Edge number:%d\n", vertexNum, edgeNum);
    MYprintf("Edges:\n");
    for (int i = 0; i < edgeNum; ++i)
    {
        MYprintf("%d<->%d %llf\n", startinput[i], endinput[i], weightinput[i]);
    }
}

void undirectionGraph::load_default()
{
    MYprintf("Load default test data......\n");
    int vexnum = 10;
    int edgenum = 11;
    int start[] = {0, 1, 2, 3, 5, 9, 8, 1, 6, 7, 5};
    int end[] = {1, 2, 3, 5, 9, 8, 1, 6, 7, 5, 4};
    double value[] = {1, 2, 3, 5, 3, 2, 1, 6, 0.2, 0.1, 1};
    init_graph(vexnum, edgenum, &start[0], &end[0], &value[0]);
    add_edge(6, 5, 3);
    add_vertex(3);
    add_edge(10, 11, 2);
    add_edge(9, 10, 1);
    add_edge(10, 7, 0.1);
    MYprintf("Done.\n");
    displayinfo();
};

void undirectionGraph::show_default()
{
    MYprintf("Display default test data......\n");
    for (int i = 0; i < vertexNum; i++)
    {
        MYprintf("Starting from vertex %d:\n", i);
        DFS(i);
        BFS(i);
        dijkstra(i);
    }
    prim();
    kruskal();
    floyd();
    MYprintf("Done.\n");
};