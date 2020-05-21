#include<iostream>
using namespace std;
int get_max(int *array,int len){//基数排序 返回数组中的最大值,用于确定数位
    int _max=array[0];
    for(int i=0;i<len;++i){
        _max=max(_max,array[i]);
    }
    return _max;
}
void radix_sort_core(int *array,int len,int exp,int *bucket,int *temp){//基数排序的核心(不需要进行比较操作)
    for(int i=0;i<len;++i){
        bucket[(array[i]/exp)%10]++;//统计各个数位的数一共有多少个,比如个位为1的有5个,为2的有3个...
    }
    for(int i=1;i<10;++i){
        bucket[i]+=bucket[i-1];//累加,确定各个位的数的开始位置
    }
    for(int i=len-1;i>=0;--i){//注意这里要倒序遍历
        temp[bucket[(array[i]/exp)%10]-1]=array[i];//从零开始存储,要减一
        /*将原数组的元素放入到临时数组中，但是两个个位相同但大小不同的数的相对位置不发生改变，
        例如 原本为141，81，1561 在放入后顺序并不会变化，仍为141，81，1561*/
        bucket[(array[i]/exp)%10]--;//完成后递减一次，防止不同元素放置在同一个位置
    }
    /*
    例子 21 31 23 12 34
    第一次进入radix_sort_core,exp=1,说明此时以个位的数值为判断标准
    bucket[1]=2,bucket[2]=2+1=3,bucket[3]=3+1=4,bucket[4]=4+1=5
    倒序遍历
    _ _ _ _ 34
    _ _ 12 _ 34
    _ _ 12 23 34
    _ 31 12 23 34
    21 31 12 23 34
    第二次进入radix_sort_core,exp=10,说明此时以十位的数值为判断标准
    bucket[1]=1,bucket[2]=2+1=3,bucket[3]=2+3=5
    倒序遍历
    _ _ _ _ 34
    _ _ 23 _ 34
    12 _ 23 _ 34
    12 _ 23 31 34
    12 21 23 31 34
    */
    for(int i=0;i<len;++i){
        array[i]=temp[i];//更新数组
    }
    for(int i=0;i<10;++i){
        bucket[i]=0;//清零
    }
}
void radix_sort(int *array,int len,int *bucket,int *temp){
    int _max=get_max(array,len);
    for(int exp=1;_max/exp>0;exp*=10){
        radix_sort_core(array,len,exp,bucket,temp);
    }
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
    int *temp=new int[len];
    int *bucket=new int[10];
    fill(temp,temp+len,0);
    fill(bucket,bucket+10,0);
    radix_sort(array,len,bucket,temp);
    print(array,len);
    return 0;
}