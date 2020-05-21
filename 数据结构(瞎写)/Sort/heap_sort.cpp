#include<iostream>
using namespace std;
void heap(int *array,int len,int i){//划分堆(模拟二叉树)
    int _max=i;
    int left=2*i+1;//左子树
    int right=2*i+2;//右子树
    if(left<len&&array[left]>array[_max]){//构建最大堆
        _max=left;
    }
    if(right<len&&array[right]>array[_max]){//构建最大堆
        _max=right;
    }
    if(_max!=i){
        swap(array[_max],array[i]);
        heap(array,len,_max);
    }
    return;
}
void heap_sort(int *array,int len){//堆排序
    for(int i=len/2-1;i>=0;--i){//当建立最大堆完毕,第0个元素必定为最大值
        heap(array,len,i);
    }
    for(int i=len-1;i>=0;--i){//将第零个元素(最大值)与最后一个元素替换,并划分为有序堆和无序堆,无序堆继续划分,并修改无序堆的长度
        swap(array[0],array[i]);
        heap(array,i,0);
    }
    return;
}
void print(int *array,int len){
    for(int i=0;i<len;++i){
        cout<<array[i]<<' ';
    }
    cout<<endl;
    return;
}
int main(){
    int array[]={1321,5649,98,41,518,9,41};
    int len=sizeof(array)/sizeof(array[0]);
    heap_sort(array,len);
    print(array,len);
    return 0;
}