#include<iostream>
#include<algorithm>
using namespace std;
void count_sort(int *array,int len){//计数排序(桶排序低配版,也可以作为桶排序的辅助排序函数),小范围数据神器,大范围数据没卵用
    int _max=array[0];
    for(int i=0;i<len;++i){
        _max=max(array[i],_max);
    }
    int *temp=new int[_max+1];
    fill(temp,temp+1+_max,0);
    for(int i=0;i<len;++i){
        temp[array[i]]++;
    }
    int j=0;
    for(int i=0;i<=_max;++i){
        if(temp[i]){
            array[j++]=i;
        }
    }
    delete []temp;
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
    count_sort(array,len);
    print(array,len);
    return 0;
}