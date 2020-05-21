#include<iostream>
#include<vector>
using namespace std;
int get_max(int *array,int len){
    int _max=array[0];
    for(int i=1;i<len;++i){
        _max=max(_max,array[i]);
    }
    return _max;
}
int get_min(int *array,int len){
    int _min=array[0];
    for(int i=1;i<len;++i){
        _min=min(_min,array[i]);
    }
    return _min;
}
void insert_sort(vector<int> &bucket){//插入排序
    int i,j;
    for(i=1;i<bucket.size();++i){//从第二个元素开始遍历,不用管第一个,因为在插入阶段会遍历到第一个元素
        int temp=bucket[i];
        for(j=i;j>0&&temp<bucket[j-1];j--){//temp<bucket[j-1]保证了可以插入到第一个元素前
            bucket[j]=bucket[j-1];//将元素后移
        }
        bucket[j]=temp;//将元素填入空位
    }
}
void bucket_sort(int *array,int len,int bucket_num,vector<int> *&bucket){
    int _min=get_min(array,len),_max=get_max(array,len);
    int bucket_size=(_max-_min)/bucket_num+1;//桶中数字的取值范围
    for(int i=0;i<bucket_num;++i){
        bucket[i].clear();//清空
    }
    for(int i=0;i<len;++i){//将不同的数划分到不同的桶中(垃圾分类doge
        bucket[(array[i]-_min)/bucket_size].push_back(array[i]);
    }
    int k=0;
    for(int i=0;i<bucket_num;++i){
        insert_sort(bucket[i]);
        for(int j=0;j<bucket[i].size();++j){
            array[k++]=bucket[i][j];
        }
    }
    return;
}
int main(){
    int array[]={1321,5649,98,41,518,9,41};
    int bucket_num=3,len=sizeof(array)/sizeof(array[0]);
    vector<int> *bucket=new vector<int>[bucket_num];
    bucket_sort(array,len,bucket_num,bucket);
    for(int i=0;i<len;++i){
        cout<<array[i]<<" ";
    }
    delete []bucket;
    return 0;
}