```c++
#include<iostream>
#include<string>
#define INF INT32_MAX
#define _MAX 21
using namespace std;
typedef enum{
    DN,UDN
}Graphkind;//带权有向图,带权无向图
typedef struct Arc{
    int weight=0;//带权图记录权重,无权图记录是否链接
}Martix[_MAX][_MAX];//从(1,1)开始存
typedef struct Martrix_Graph{
    char vertex[_MAX];//顶点的值
    Martix Mar;//邻接矩阵
    Graphkind kind;//图的类型
    int _vertex,_arc;//顶点数量,弧数量
}*M_G;
bool visited[_MAX]={0};
inline int _find(M_G graph,char item){//查找当前值对应的序号,用于确定其在邻接矩阵的行或列
    for(int i=1;i<=graph->_vertex;++i){
        if(graph->vertex[i]==item){
            return i;
        }
    }
    return 0;
}
void Create_DN(M_G &graph){//创建带权有向图
    cout<<"顶点数量: ";
    cin>>graph->_vertex;
    cout<<"弧数量: ";
    cin>>graph->_arc;
    cout<<"输入顶点的值:"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        cin>>graph->vertex[i];
    }
    for(int i=0;i<_MAX;++i){
        for(int j=0;j<_MAX;++j){
            graph->Mar[i][j].weight=INF;
        }
    }
    cout<<"输入弧尾,弧头和弧的权重:"<<endl;
    char v1,v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    for(int i=1;i<=graph->_arc;++i){
        cin>>v2>>v1>>weight;
        if(_find(graph,v2)==0||_find(graph,v1)==0){
            exit(-1);
        }
        graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=weight;
    }
    
    return;
}
void Create_UDN(M_G &graph){//创建带权无向图
    cout<<"顶点数量: ";
    cin>>graph->_vertex;
    cout<<"弧数量: ";
    cin>>graph->_arc;
    cout<<"输入顶点的值:"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        cin>>graph->vertex[i];
    }
    for(int i=0;i<_MAX;++i){
        for(int j=0;j<_MAX;++j){
            graph->Mar[i][j].weight=INF;
        }
    }
    cout<<"输入弧尾,弧头和弧的权重:"<<endl;
    char v1,v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    for(int i=1;i<=graph->_arc;++i){
        cin>>v2>>v1>>weight;
        if(_find(graph,v2)==0||_find(graph,v1)==0){
            exit(-1);
        }
        graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=weight;
        graph->Mar[_find(graph,v1)][_find(graph,v2)].weight=weight;
    }
    return;
}
void Create_Graph(M_G &graph){
    cout<<"0:创建带权有向图 1:创建带权无向图"<<endl;
    cout<<"选项: ";
    graph=new Martrix_Graph;
    cin>>(int &)graph->kind;
    switch(graph->kind){
        case DN:
            Create_DN(graph);
            break;
        case UDN:
            Create_UDN(graph);
            break;
        default:
            cout<<"ERROR!"<<endl;
            break;
    }
    return;
}
void Clear_Graph(M_G &graph){//清空
    graph->_arc=0;
    graph->_vertex=0;
    fill(graph->vertex,graph->vertex+_MAX,0);
    return;
}
void Dijkstra(M_G graph,char start,int *final,string *str){
    int mark=_find(graph,start);
    visited[mark]=true;//不对自身查找
    for(int i=1;i<=graph->_vertex;++i){//根据邻接矩阵的起始点所在行的各个权重,初始化起始点到其他顶点的距离
        final[i]=graph->Mar[mark][i].weight;
        str[i]+=graph->vertex[mark];
        str[i]+=graph->vertex[i];
    }
    final[mark]=0;//自身到自身的距离为0
    for(int i=1;i<graph->_vertex;++i){//遍历graph->_vertex-1次,因为已经进行了初始化
        int _min=INF;
        int posi;
        for(int j=1;j<=graph->_vertex;++j){//遍历final数组中没有确定最短路的值,查找新的最短路,并记录其位置
            if(!visited[j]&&final[j]<_min){
                _min=final[j];
                posi=j;
            }
        }
        visited[posi]=true;//标记新遍历得到的最短路
        if(str[posi][str[posi].size()-1]!=graph->vertex[posi]){
            str[posi]+=graph->vertex[posi];
        }
        for(int j=1;j<=graph->_vertex;++j){//更新final数组中的值
            if(graph->Mar[posi][j].weight<INF){
                //依据新的最短路的位置,对其邻接矩阵的所在行进行遍历,寻找对于其他点可能存在的最短路并更新final数组
                if(final[j]<=final[posi]+graph->Mar[posi][j].weight){
                    continue;
                }
                else{
                    final[j]=final[posi]+graph->Mar[posi][j].weight;
                    str[j]=str[posi];
                }
            }
        }
    }
    fill(visited,visited+_MAX,0);
    return;
}
void print(M_G graph){
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(graph->Mar[i][j].weight==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<graph->Mar[i][j].weight<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
}
int main(){
    M_G graph=NULL;
    Create_Graph(graph);
    cout<<"当前图的类型: ";
    switch(graph->kind){
        case DN:
            cout<<"带权有向图"<<endl;
            break;
        case UDN:
            cout<<"带权无向图"<<endl;
            break;
    }
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    int *final=new int[graph->_vertex+1];
    string *str=new string[graph->_vertex+1];
    fill(final,final+graph->_vertex,0);
    Dijkstra(graph,graph->vertex[1],final,str);
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=0;j<str[i].size();++j){
            cout<<str[i][j];
            if(j!=str[i].size()-1){
                cout<<"->";
            }
        }
        if(final[i]==INF){
            cout<<' '<<"∞"<<endl;
            continue;
        }
        cout<<' '<<final[i]<<endl;
    }
    delete graph;
    graph=NULL;
    delete []final;
    final=NULL;
    delete []str;
    str=NULL;
    return 0;
}
```

[参考](https://wiki.jikexueyuan.com/project/easy-learn-algorithm/dijkstra.html)

***Sample***
```
6 8 abcdef
a c 10
a e 30
a f 100
b c 5
c d 50
d f 10
e d 20
e f 60
```

***Out***
```
当前图的类型: 带权有向图
邻接矩阵: 
∞ ∞ 10 ∞ 30 100 
∞ ∞ 5 ∞ ∞ ∞ 
∞ ∞ ∞ 50 ∞ ∞ 
∞ ∞ ∞ ∞ ∞ 10 
∞ ∞ ∞ 20 ∞ 60 
∞ ∞ ∞ ∞ ∞ ∞ 

a->a 0
a->b ∞
a->c 10
a->e->d 50
a->e 30
a->e->d->f 60
```