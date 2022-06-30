#include "array.h"

PartitionIO* myArray::part = nullptr;
void* myArray::_malloc(size_t Size)
{
    if (part == nullptr) return nullptr;
    return newMalloc(part, ARRAY, Size);
}

void myArray::_free(void* Pos)
{
    if (part == nullptr) return;
    newFree(part, Pos);
}

int myArray::_printf(const char* format, ...)
{
    va_list aptr;
    int ret;

    va_start(aptr, format);
    ret = qprintf(part, format, aptr);
    va_end(aptr);
    return ret;
}

void myArray::recovery(signed_size_t offset)
{
    addOffset(pArr, offset);
    addOffset(pArr->base, offset);
}

void myArray::init(){
    pArr=(Arr*)my_malloc(sizeof(Arr));
}

void myArray::initArray(int len){//创建
    if(ready()) {
        my_printf("请勿重复申请数组空间\n");
        length();
        return;
    }
    pArr->base=(int*)my_malloc(sizeof(int)* len);
    if(NULL==pArr->base)
    {
        my_printf("内存分配失败\n");
        exit(-1);
    }
    else{
        pArr->len = len;
        my_printf("创建成功,数组容量为%d\n", len);
    }
    pArr->num=0;
    return;
}

void myArray::destroy(){ //回收数组
    clear();
    my_free(pArr);
    my_printf("回收数组成功\n");
}

void myArray::clear(){// 清空数组
    if(pArr->base){
        my_free(pArr->base);
        pArr->base=NULL;
        pArr->len=0;
        pArr->num=0;
        my_printf("清空数组成功\n");
    }
}
bool myArray::empty(){//判断是否为空
    if(pArr->num==0){
        my_printf("数组为空\n");
        return true;
    }
    else
    return false;
}
bool myArray::ready(){
    if(pArr->base == NULL){
        my_printf("请先申请数组空间\n");
        return false;
    }
    return true;
}
bool myArray::full(){//判断是否已满
    if (pArr->num==pArr->len){
        my_printf("数组已满\n");
        return true;
    }
    else return false;
}
bool myArray::append(int val){//在最后添加元素
    if(!ready())
    return false;
    if (full())
    return false;
    else{
        pArr->base[pArr->num]=val;
        (pArr->num)++;
        my_printf("在末端添加元素%d成功\n",val);
        return true;
    }
}
bool myArray::insert(int pos, int val){//插入元素
    if(!ready())
    return false;
    if (full())
    return false;
    if(pos<1||pos>pArr->num+1)
    return false;
    else{
        for (int i=pArr->num-1;i>=pos-1;i--){
            pArr->base[i+1]=pArr->base[i];
        }
        pArr->base[pos-1]=val;
        pArr->num++;
        my_printf("在位置%d插入元素%d成功\n",pos,val);
        return true;
    }
}
bool myArray::del(int pos){//删除元素
    if(!ready())
    return false;
    if (pos<1 || pos>pArr->num)
    {
        my_printf("位置%d非法\n", pos);
        return false;
    }
    else{
        int val=pArr->base[pos-1];
        for (int i=pos;i<pArr->num;i++){
            pArr->base[i-1]=pArr->base[i];
        }
    }
    pArr->num--;
    my_printf("删除位置%d元素成功\n",pos);
    return true;
}
bool myArray::get(int pos){//获得元素的值
    if(!ready())
    return false;
    if(full())
    return false;
    if (pos<1 || pos>pArr->num)
    {
        my_printf("位置%d非法\n", pos);
        return false;
    }
    else{
        int val = pArr->base[pos - 1];
        my_printf("位置%d元素的值为%d\n", pos, val);
	return true;
    }
}
bool myArray::locate(int val)
{
    if (!ready())
        return false;
    if (!empty()) {
        for (int i = 0; i < pArr->num; i++) {
            if (pArr->base[i] == val) {
                my_printf("第一个值为 %d 的元素在位置 %d\n", val, i + 1);
                return true;
            }
        }
        my_printf("不存在值为 %d 的元素\n", val);
    }
    return false;
}
int myArray::length()
{
    if (!ready())
        return 0;
    my_printf("数组长度为 %d，容量为 %d\n", pArr->num, pArr->len);
    return pArr->num;
}
void myArray::display(){//展示数组
    if(!ready())
    return;
    if(!empty()){
        my_printf("数组所有元素的值为: ");
        for(int i=0;i<pArr->num;i++){
            my_printf("%d ",pArr->base[i]);
        }
        my_printf("\n");
    }
}
void myArray::input(){
    int n = 5;
    init();
    initArray(n << 1);
    for(int i = 0; i < n; i++) {
        append(n - i);
    }
}
void myArray::show(){
    length();
    display();
    get(3);
    locate(5);
}
/*
int main()
{
    myArray* arr = new myArray;
    arr->input();
    arr->show();
    arr->insert(3, 6);
    arr->show();
    arr->del(2);
    arr->show();
    arr->destroy();
    delete arr;
    return 0;
}
*/