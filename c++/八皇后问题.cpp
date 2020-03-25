#include<iostream>
using namespace std;
int y[20];
int n;
int sum;
void queen(int x){
    if(x>=n){//递归的结束条件
        ++sum;
        return;
    }
    for(int i=0;i<n;i++){//在某一行中的所有位置均进行尝试
        y[x]=i;//记录皇后在第x行的第几个位置
        int check=1;//检查点
        for(int j=0;j<x;j++){//查找在x行之前的皇后攻击情况，注意这里不等于x
            if(y[x]==y[j]||x+y[x]==j+y[j]||x-y[x]==j-y[j]){//正上方，斜左上，斜右上
                check=0;
                break;
            }
        }
        if(check){
            queen(x+1);
        }
    }
}
int main(){
    cin>>n;
    queen(0);
    cout<<sum;
    return 0;
}
