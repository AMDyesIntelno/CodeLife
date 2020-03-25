#include<iostream>
#include<algorithm>
using namespace std;
bool check_hang[10][10]={0};
bool check_lie[10][10]={0};
bool check_gong[10][10]={0};
int m[10][10]={0};
int point[10][10]={
    {0,0,0,0,0,0,0,0,0,0},
    {0,6,6,6,6,6,6,6,6,6},
    {0,6,7,7,7,7,7,7,7,6},
    {0,6,7,8,8,8,8,8,7,6},
    {0,6,7,8,9,9,9,8,7,6},
    {0,6,7,8,9,10,9,8,7,6},
    {0,6,7,8,9,9,9,8,7,6},
    {0,6,7,8,8,8,8,8,7,6},
    {0,6,7,7,7,7,7,7,7,6},
    {0,6,6,6,6,6,6,6,6,6}
};
int g[10][10]={
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,2,2,2,3,3,3},
    {0,1,1,1,2,2,2,3,3,3},
    {0,1,1,1,2,2,2,3,3,3},
    {0,4,4,4,5,5,5,6,6,6},
    {0,4,4,4,5,5,5,6,6,6},
    {0,4,4,4,5,5,5,6,6,6},
    {0,7,7,7,8,8,8,9,9,9},
    {0,7,7,7,8,8,8,9,9,9},
    {0,7,7,7,8,8,8,9,9,9}
}; 
int _max=0;
struct r
{
    int order;
    int num;
}a[10];
bool pd(r a,r b){
    if(a.num>b.num){
        return 1;
    }
    else{
        return 0;
    }
}
void dfs(int r,int c){
    if(r==10){
        int temp=0;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                temp+=m[i][j]*point[i][j];
            }
        }
        if(temp>_max){
            _max=temp;
        }
        return;
    }
    if(c==10){
        dfs(r+1,1);
        return;
    }
    if(m[a[r].order][c]!=0){
        dfs(r,c+1);
    }
    else{
        for(int i=1;i<=9;i++){
            if(!check_hang[a[r].order][i]&&!check_lie[c][i]&&!check_gong[g[a[r].order][c]][i]){
                m[a[r].order][c]=i;
                check_hang[a[r].order][i]=1;
                check_lie[c][i]=1;
                check_gong[g[a[r].order][c]][i]=1;
                dfs(r,c+1);
                m[a[r].order][c]=0;
                check_hang[a[r].order][i]=0;
                check_lie[c][i]=0;
                check_gong[g[a[r].order][c]][i]=0;
            }
        }
    }
}
int main(){
    int temp;
    for(int i=1;i<=9;i++){
        a[i].order=i;
        a[i].num=0;
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            cin>>temp;
            m[i][j]=temp;
            if(temp!=0){
                check_hang[i][temp]=1;
                check_lie[j][temp]=1;
                check_gong[g[i][j]][temp]=1;
                a[i].num++;
            }
        }
    }
    sort(a+1,a+10,pd);
    dfs(1,1);
    if(!_max){
        cout<<-1;
    }
    else{
        cout<<_max;
    }
    return 0;
}
