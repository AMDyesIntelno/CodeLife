```c++
/*带权无向图最小生成树prim算法*/
#include<iostream>
#define INF INT32_MAX
#define _MAX 21
using namespace std;
typedef struct Arc{
    int weight=0;//带权图记录权重,无权图记录是否链接
}Martix[_MAX][_MAX];//从(1,1)开始存
typedef struct Martrix_Graph{
    char vertex[_MAX];//顶点的值
    Martix Mar;//邻接矩阵
    int _vertex,_arc;//顶点数量,弧数量
}*M_G;
typedef struct PRIM{/*存放节点和权重*/
    char data;
    int weight;
}Prim[_MAX];
bool visited[_MAX]={0};/*标记是否已经访问*/
inline int _find(M_G graph,char item){//查找当前值对应的序号,用于确定其在邻接矩阵的行或列
    for(int i=1;i<=graph->_vertex;++i){
        if(graph->vertex[i]==item){
            return i;
        }
    }
    return 0;
}
void Create_UDN(M_G &graph){//创建带权无向图
    graph=new Martrix_Graph;
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
void prim(M_G graph,char start,Prim p){
    fill(visited,visited+_MAX,0);
    int start_posi=_find(graph,start);
    if(start_posi==0){
        return;
    }
    visited[start_posi]=1;
    int _min=INF,_min_posi;
    for(int i=1;i<=graph->_vertex;++i){/*根据给定的根节点进行初始化*/
        p[i].data=graph->vertex[start_posi];
        p[i].weight=graph->Mar[start_posi][i].weight;
        if(graph->Mar[start_posi][i].weight<_min){/*标记最小权重*/
            _min=graph->Mar[start_posi][i].weight;
            _min_posi=i;
        }
    }
    visited[_min_posi]=1;/*标记找到的最小权重点*/
    start_posi=_min_posi;/*从新的最小权重点开始*/
    _min=INF;/*初始化为最大值*/
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(!visited[j]){
                if(graph->Mar[start_posi][j].weight<p[j].weight){/*刷新权重值和权重点*/
                    p[j].weight=graph->Mar[start_posi][j].weight;
                    p[j].data=graph->vertex[start_posi];
                }
                if(p[j].weight<_min){/*标记最小权重*/
                    _min=p[j].weight;
                    _min_posi=j;
                }
            }
        }
        visited[_min_posi]=1;
        start_posi=_min_posi;
        _min=INF;
    }
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
    return;
}
void print_prim(M_G graph,char start,const Prim p){
    int start_posi=_find(graph,start);
    if(start_posi==0){
        return;
    }
    for(int i=1;i<=graph->_vertex;++i){
        if(i==start_posi){
            continue;
        }
        cout<<p[i].data<<"-"<<p[i].weight<<"->"<<graph->vertex[i]<<endl;
    }
    return;
}
int main(){
    M_G graph=NULL;
    Prim p;
    Create_UDN(graph);
    print(graph);
    prim(graph,'A',p);
    print_prim(graph,'A',p);
    delete graph;
    graph=NULL;
    return 0;
}
```

参考图
![](../../images/Prim.png)

***Sample***
```
6 10 ABCDEF
A B 6
A C 1
A D 5
B C 5
B E 3
C D 5
C E 6
C F 4
D F 2
E F 6
```

***Out***
```
∞ 6 1 5 ∞ ∞ 
6 ∞ 5 ∞ 3 ∞ 
1 5 ∞ 5 6 4 
5 ∞ 5 ∞ ∞ 2 
∞ 3 6 ∞ ∞ 6 
∞ ∞ 4 2 6 ∞ 

C-5->B
A-1->C
F-2->D
B-3->E
C-4->F
```