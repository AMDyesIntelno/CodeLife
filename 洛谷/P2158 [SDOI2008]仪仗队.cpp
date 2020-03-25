/*欧拉函数*/
#include<iostream>
using namespace std;
long long phi[1000001];
void phi_table(int n){/*求解欧拉函数*/
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(!phi[i]){
            for(int j=i;j<=n;j+=i){
                if(!phi[j]){
                    phi[j]=j;
                }
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    /*求有多少不同的斜率，即构建直角坐标系
      求在0,1,2...n-1这(0，n)的范围内有多少对x，y互质*/
    if(n==1){/*看不见自己 >-< */
        cout<<0;
        return 0;
    }
    phi_table(n);
    long long sum=3;
    /*特判n=2的情况
     1 1
     0 1
     总共3种情况*/
    for(int i=2;i<n;++i){
        sum+=phi[i]*2;/*沿对角线对称要乘2*/
    }
    cout<<sum;
    return 0;
}
