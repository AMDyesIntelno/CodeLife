#include<iostream>
using namespace std;
void insert_sort(int *array,int len){//插入排序
    int i,j;
    for(i=1;i<len;++i){//从第二个元素开始遍历,不用管第一个,因为在插入阶段会遍历到第一个元素
        int temp=array[i];
        for(j=i;j>0&&temp<array[j-1];j--){//temp<a[j-1]保证了可以插入到第一个元素前
            array[j]=array[j-1];//将元素后移
        }
        array[j]=temp;//将元素填入空位
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
    insert_sort(array,len);
    print(array,len);
    return 0;
}