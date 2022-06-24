#include "FileIO.h"
#include "DataStructure/LinkedList.h"
#include <iostream>

int main()
{
	PartitionIO *part = new PartitionIO;
	linkedList::part = part;	
	part->readFile();

    linkedList* list = new linkedList;
    int n;
    scanf("%d", &n);
    pNode tail = list->head;
    printf("List is init!\nList is %sempty!\n", list->isEmpty() ? "" : "not ");
    for (int i = 1; i <= n; i++)
    {
        elemType x;
        scanf("%d", &x);
        tail = list->tailInsert(tail, list->newNode(x));
    }
    printf("All input is accepted!\nNow list is %sempty!\n", list->isEmpty() ? "" : "not ");
    printf("List length is %d.\n", list->listLength());
    printf("List data: "), list->traverseList(list->print), putchar(0xA);

    int pos = 0;
    scanf("%d", &pos);
    pNode elem = list->getElem(pos);
    if (elem != NULL)
    {
        printf("Pos %d is %d.\n", pos, elem->data);
        pNode pre = list->elemPre(elem), next = list->elemNext(elem);
        if (pre != NULL) printf("Pre is %d.\n", pre->data);
        if (next != NULL) printf("Next is %d.\n", next->data);
    }
    else
        printf("Pos %d is illegal!\n", pos);

    int val = 0;
    scanf("%d", &val);
    int valPos = list->locateElem(val, list->cmp);
    if (~valPos)
        printf("The first elem whose val is %d is in Pos %d.\n", val, valPos);
    else
        printf("No such val %d in the list!\n", val);

    scanf("%d", &pos);
    elemType data = list->del(pos);
    if (~data)
        printf("Pos %d is deleted! The value is %d.\n", pos, data);
    else
        printf("Pos %d is illegal!\n", pos);

    printf("Now list is %sempty!\n", list->isEmpty() ? "" : "not ");
    printf("List length is %d.\n", list->listLength());
    printf("List data: "), list->traverseList(list->print), putchar(0xA);

    list->destoryList();
    //part->writeFile();
    delete part;
	return 0;
}
