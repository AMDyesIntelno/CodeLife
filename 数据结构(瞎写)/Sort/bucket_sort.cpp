#include<iostream>
#include<algorithm>
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
void count_sort(vector<int> &bucket){
    if(bucket.size()){
        int _max=bucket[0];
        for(int i=0;i<bucket.size();++i){
            _max=max(_max,bucket[i]);
        }
        int *temp=new int[_max+1];
        fill(temp,temp+1+_max,0);
        for(int i=0;i<bucket.size();++i){
            temp[bucket[i]]++;
        }
        int j=0;
        for(int i=0;i<=_max;++i){
            if(temp[i]){
                bucket[j++]=i;
            }
        }
        delete []temp;
    }
    return;
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
        count_sort(bucket[i]);
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