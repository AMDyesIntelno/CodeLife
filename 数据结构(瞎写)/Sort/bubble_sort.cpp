#include<iostream>
using namespace std;
void bubble_sort(int *array,int len){//冒泡排序
    for(int i=1;i<len;i++){//进行一次遍历将相邻的两个数修改为有序
        if(array[i]<array[i-1]){
            swap(array[i],array[i-1]);
        }
    }
    for(int i=1;i<len;i++){//进行一次遍历检查是否完全有序
        if(array[i]<array[i-1]){
            bubble_sort(array,len);
        }
        else{
            continue;
        }
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
    bubble_sort(array,len);
    print(array,len);
    return 0;
}