#include<iostream>
using namespace std;
void shell_sort(int *array,int len){//希尔排序
    for(int shell=len/2;shell>0;shell/=2){//切片
        for(int i=shell;i<len;++i){//片后递增
            int j;
            int temp=array[i];
            for(j=i;j>=shell&&array[j-shell]>temp;j-=shell){//修改为部分片段有序
                array[j]=array[j-shell];
            }
            array[j]=temp;
        }
    }
    return;
    /*
    例子
    87654321
    第一次切片 8765 | 4321
    修改为部分片段有序 4321 | 8765
    第二次切片 43 | 21 | 87 | 65
    修改为部分片段有序
    1.比较21的片段和43的片段并尝试替换
    21 | 43 | 87 | 65
    2.比较21,43的片段和87的片段并尝试替换
    21 | 43 | 87 | 65
    3.比较21,43,87的片段和65的片段并尝试替换
    21 | 43 | 65 | 87   
    第三次切片 2 | 1 | 4 | 3 | 6 | 5 | 8 | 7
    修改为部分片段有序
    1.比较2和1并尝试替换
    1 | 2 | 4 | 3 | 6 | 5 | 8 | 7
    2.比较1,2和4并尝试替换
    1 | 2 | 4 | 3 | 6 | 5 | 8 | 7
    3.比较1,2,4和3并尝试替换
    1 | 2 | 3 | 4 | 6 | 5 | 8 | 7
    4.比较1,2,3,4和6并尝试替换
    1 | 2 | 3 | 4 | 6 | 5 | 8 | 7
    5.比较1,2,3,4,6和5并尝试替换
    1 | 2 | 3 | 4 | 5 | 6 | 8 | 7
    6.比较1,2,3,4,5,6和8并尝试替换
    1 | 2 | 3 | 4 | 5 | 6 | 8 | 7
    7.比较1,2,3,4,5,6,8和7并尝试替换
    1 | 2 | 3 | 4 | 5 | 6 | 7 | 8
    */
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
    shell_sort(array,len);
    print(array,len);
    return 0;
}