```c++
/*带权无向图最小生成树kruskal算法*/
#include<iostream>
#include<algorithm>
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
typedef struct KRUSKAL{
    int arc_tail;/*弧尾*/
    int arc_head;/*弧头*/
    int weight;
}*Kruskal;
bool visited[_MAX]={0};/*标记是否已经访问*/
inline int _find(M_G graph,char item){//查找当前值对应的序号,用于确定其在邻接矩阵的行或列
    for(int i=1;i<=graph->_vertex;++i){
        if(graph->vertex[i]==item){
            return i;
        }
    }
    return 0;
}
inline bool cmp(KRUSKAL a,KRUSKAL b){
    if(a.weight<b.weight){
        return true;
    }
    return false;
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
void Read_arc(M_G graph,Kruskal &k){/*读入所有的弧并对弧长进行排序*/
    int temp=1;
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=i;j<=graph->_vertex;++j){
            if(graph->Mar[i][j].weight!=INF){
                k[temp].arc_tail=i;
                k[temp].arc_head=j;
                k[temp].weight=graph->Mar[i][j].weight;
                ++temp;
            }
        }
    }
    sort(k+1,k+1+graph->_arc,cmp);
    return;
}
void Init(M_G graph,int *parent){
    for(int i=0;i<=graph->_arc;++i){
        parent[i]=i;/*初始化自身为自身的根*/
    }
    return;
}
int _find_parent(int *parent,int root){
    if(parent[root]!=root){
        parent[root]=_find_parent(parent,parent[root]);/*路径压缩*/
    }
    return parent[root];
}
void _union(int *parent,int rootx,int rooty){
    int x=_find_parent(parent,rootx);
    int y=_find_parent(parent,rooty);
    if(x==y){
        return;
    }
    parent[x]=y;/*根合并*/
}
void kruskal(M_G graph,Kruskal k,int *parent){
    int count=1;/*计数器*/
    for(int i=1;i<=graph->_arc;++i){
        if(_find_parent(parent,k[i].arc_head)!=_find_parent(parent,k[i].arc_tail)){/*弧头和弧尾的根不同,说明弧头和弧尾不在一个集合中,将这两个根合并*/
            _union(parent,k[i].arc_head,k[i].arc_tail);
            ++count;
            cout<<graph->vertex[k[i].arc_tail]<<"-"<<graph->Mar[k[i].arc_tail][k[i].arc_head].weight<<"->"<<graph->vertex[k[i].arc_head]<<endl;
            if(count==graph->_vertex){/*最小生成树的条件*/
                return;
            }
        }
    }
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
int main(){
    M_G graph=NULL;
    Create_UDN(graph);
    Kruskal k=new KRUSKAL[graph->_arc+1];
    Read_arc(graph,k);
    int *parent=new int[graph->_arc+1];
    Init(graph,parent);
    print(graph);
    kruskal(graph,k,parent);
    delete k;
    k=NULL;
    delete parent;
    parent=NULL;
    delete graph;
    graph=NULL;
    return 0;
}
```

参考图
![](../../images/Kruskal.png)

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

A-1->C
D-2->F
B-3->E
C-4->F
B-5->C
```