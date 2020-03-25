#include<iostream>
#include<algorithm>
using namespace std;
int check_hang[10][10];
int check_lie[10][10];
int check_gong[10][10];
int gong[10][10]={/*用于判断是否在同一宫内*/
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,2,2,2,3,3,3},
    {0,1,1,1,2,2,2,3,3,3},
    {0,1,1,1,2,2,2,3,3,3},
    {0,4,4,4,5,5,5,6,6,6},
    {0,4,4,4,5,5,5,6,6,6},
    {0,4,4,4,5,5,5,6,6,6},
    {0,7,7,7,8,8,8,9,9,9},
    {0,7,7,7,8,8,8,9,9,9},
    {0,7,7,7,8,8,8,9,9,9},
};
int _map[10][10];
struct node{/*记录当前行的序号以及填入的数字个数，先从个数最多的行开始，有利于提高算法的速度*/
    int num_hang;
    int sum_hang;
}n[10];
bool cmp(node A,node B){/*判断条件*/
    if(A.sum_hang>B.sum_hang){
        return 1;
    }
    else{
        return 0;
    }
}
void dfs(int hang,int lie){/*回溯法填数独*/
    if(hang==10){/*结束条件*/
        cout<<endl;
        for(int i=1;i<10;i++){
            for(int j=1;j<10;j++){
                cout<<_map[i][j]<<' ';
            }
            cout<<endl;
        }
        return;
    }
    if(lie==10){/*搜索完某一行的最后一列后，进行下一行的搜索*/
        dfs(hang+1,1);
        return;
    }
    if(_map[n[hang].num_hang][lie]){/*如果这个位置已经填入了数字，就搜索下一个位置*/
        dfs(hang,lie+1);
    }
    else{
        for(int i=1;i<10;i++){/*i作为要填入的数字*/
            if(!check_hang[n[hang].num_hang][i]&&!check_lie[lie][i]&&!check_gong[gong[n[hang].num_hang][lie]][i]){/*检查i是否在当前位置的行、列、宫中出现*/
                _map[n[hang].num_hang][lie]=i;/*填入*/
                check_hang[n[hang].num_hang][i]=1;/*标记已经使用*/
                check_lie[lie][i]=1;/*标记已经使用*/
                check_gong[gong[n[hang].num_hang][lie]][i]=1;/*标记已经使用*/
                dfs(hang,lie+1);/*搜索下一个位置*/
                /*回溯法的核心*/
                _map[n[hang].num_hang][lie]=0;/*删除*/
                check_hang[n[hang].num_hang][i]=0;/*撤销标记*/
                check_lie[lie][i]=0;/*撤销标记*/
                check_gong[gong[n[hang].num_hang][lie]][i]=0;/*撤销标记*/
            }
        }
    }
    return;
}
int main(){
    for(int i=1;i<10;i++){/*为结构体填入数据*/
        n[i].num_hang=i;
        n[i].sum_hang=0;
    }
    for(int i=1;i<10;i++){
        for(int j=1;j<10;j++){
            cin>>_map[i][j];
            if(_map[i][j]){
                check_hang[i][_map[i][j]]=1;/*记录该数字已经在该行使用过*/
                check_lie[j][_map[i][j]]=1;/*记录该数字已经在该列使用过*/
                check_gong[gong[i][j]][_map[i][j]]=1;/*记录该数字已经在该宫使用过*/
                n[i].sum_hang++;/*统计行内个数*/
            }
        }
    }
    sort(n+1,n+10,cmp);
    dfs(1,1);/*将填入的数字个数最多的行作为第一行*/
    return 0;
}
