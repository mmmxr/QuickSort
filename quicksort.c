#include <stdio.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "seqstack.h"
#define TEST_HEADER printf("\n=============%s=============\n",__FUNCTION__)
void Swap(int *pa,int *pb)
{
    int tmp=*pa;
    *pa=*pb;
    *pb=tmp;
}
/////////////////////////////////
//快速排序(递归版本)
//时间复杂度：
//          最坏：O（n^2）
//          平均：O（n*logn）
//空间复杂度：O（logn）
////////////////////////////////

/////////方法1.交换法////////////
int Partion(int arr[],size_t beg,size_t end)
{   
    //1）定义好区间的边界
    //2）取最后一个元素作为基准值
    //3）从左到右找到第一个大于基准值的元素
    //4）从右往左找到第一个小于基准值的元素
    //5）交换（left<right）
    int left=beg;
    int right=end-1;
    int key=arr[right];
    while(left<right)
    {
        while(left<right&&arr[left]<=key)
        {
            left++;    
        }
        while(left<right&&arr[right]>=key)
        {
            right--;
        }
        if(left<right)
        {
            Swap(&arr[left],&arr[right]);
        }
    }
    //此时将left指向的值和最后一个元素进行交换
    //此时left指向的值，一定大于基准值
    Swap(&arr[left],&arr[end]-1);
    return left;
}

/////////方法1.交换法////////////

int Partion2(int arr[],size_t beg,size_t end)
{
    //定义好区间边界
    int left=beg;
    int right=end-1;
    //取最后一个元素做基准值
    int key=arr[right]; 
    while(left<right)
    {
        while(left<right&&arr[left]<=key)
        {
            ++left;
        }
        if(left<right)
        {
            arr[right--]=arr[left];
        }
        while(left<right&&arr[right]>=key)
        {
            --right;
        }
        if(left<right)
        {
            arr[left++]=arr[right];
        }
    }
    arr[left]=key;
    return left;
}
void _QuickSort(int arr[],size_t beg,size_t end)
{   
    if(end-beg<=1)
    {
        return;
    }
    size_t mid=Partion(arr,beg,end);
    _QuickSort(arr,beg,mid);
    _QuickSort(arr,mid+1,end);

}
void QuickSort(int arr[],size_t size)
{
    if(arr==NULL||size<=0)
    {
        return;
    }
    _QuickSort(arr,0,size);
}

/////////////////////////////////
//快速排序(非递归版本)
////////////////////////////////
void QuickSortByLoop(int arr[],size_t size)
{
    if(arr==NULL||size<=0)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    int beg=0;
    int end=size;
    SeqStackPush(&stack,beg);
    SeqStackPush(&stack,end);
    while(stack.size>0)
    {
        SeqStackTop(&stack,&end);
        SeqStackPop(&stack);
        SeqStackTop(&stack,&beg);
        SeqStackPop(&stack);
        if(end-beg<=1)
        {
            continue;
        }
        int mid=Partion(arr,beg,end);
        SeqStackPush(&stack,beg);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,mid+1);
        SeqStackPush(&stack,end);
    }
}

//改进快速排序
//  1.三值取中确定基准值
//  2.当区间比较小时，使用插入排序直接对区间进行排序，从而有效地减少递归次数
//  3.递归达到一定程度之后，使用堆排序对剩余待排序区间进行排序即可

