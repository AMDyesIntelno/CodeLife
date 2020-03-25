#include<iostream>
using namespace std;
int main(){
    int m,s,t;
    cin>>m>>s>>t;
    int *f=new int[t+1];
    fill(f,f+t+1,0);
    /*将使用魔法进行闪现与跑步分别处理
      贪心原则在于能用闪现就用闪现，实在不行才跑步
      就像你有一个plan A和plan B一样
      你就是一个贪心的人
      这两个计划是同步进行的
      但你只取每一时刻的最大值*/
    for(int i=1;i<=t;++i){
        if(m>=10){
            f[i]=max(f[i],f[i-1]+60);
            m-=10;
        }
        else{
            f[i]=f[i-1];
            m+=4;
        }
    }
    for(int i=1;i<=t;++i){
        f[i]=max(f[i],f[i-1]+17);
    }
    if(f[t]>=s){
        cout<<"Yes"<<endl;
        for(int i=1;i<=t;++i){
            if(f[i]>=s){
                cout<<i;
                delete []f;
                return 0;
            }
        }
    }
    else{
        cout<<"No"<<endl<<f[t];
        delete []f;
        return 0;
    }
}
