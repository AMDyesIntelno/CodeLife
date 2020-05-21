#include<iostream>
using namespace std;
void merge(int *array,int start,int mid,int end,int *temp){//归并排序 治
    int left=start;
    int right=end;
    int mid_0=mid;
    int mid_1=mid+1;
    int k=0;
    while(left<=mid_0&&mid_1<=right){//两个片段进行比较,每次选出较小的一个数,写入temp数组中
        if(array[left]<array[mid_1]){//注意,这里left是与mid_1进行比较而非mid_0
            temp[k++]=array[left++];
        }
        else{
            temp[k++]=array[mid_1++];
        }
    }
    while(left<=mid_0){//对突出部分进行直接写入
        temp[k++]=array[left++];
    }
    while(mid_1<=right){
        temp[k++]=array[mid_1++];
    }
    for(left=0;left<k;++left){
        array[left+start]=temp[left];//重新写入原数组,注意这里要加上函数传入的起始位置
    }
    return;
}
void merge_sort(int *array,int start,int end,int *temp){//归并排序 分
    if(start<end){
        int mid=(start+end)/2;
        merge_sort(array,start,mid,temp);
        merge_sort(array,mid+1,end,temp);
        merge(array,start,mid,end,temp);
        return;
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
    fill(temp,temp+len,0);
    merge_sort(array,0,len-1,temp);
    print(array,len);
    return 0;
}