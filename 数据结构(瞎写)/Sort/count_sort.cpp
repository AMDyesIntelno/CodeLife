#include<iostream>
using namespace std;
void count_sort(int *array,int len){//选择排序
    for(int i=0;i<len;++i){
        int posi=i;//记录每一次检索的最小值的位置
        for(int j=i+1;j<len;++j){
            if(array[j]<array[posi]){//更新最小值的位置
                posi=j;
            }
        }
        swap(array[posi],array[i]);
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
    count_sort(array,len);
    print(array,len);
    return 0;
}