```c++
/*邻接矩阵*/
#include<iostream>
#include<queue>
#define INF INT32_MAX
#define _MAX 21
using namespace std;
typedef enum{
    DG,DN,UDG,UDN
}Graphkind;//有向图,带权有向图,无向图,带权无向图
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
void Create_DG(M_G &graph){//创建有向图
    cout<<"顶点数量: ";
    cin>>graph->_vertex;
    cout<<"弧数量: ";
    cin>>graph->_arc;
    cout<<"输入顶点的值:"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        cin>>graph->vertex[i];
    }
    cout<<"输入弧尾和弧头:"<<endl;
    char v1,v2;//v1弧头,v2弧尾,即从v2指向v1,不带权
    for(int i=1;i<=graph->_arc;++i){
        cin>>v2>>v1;
        if(_find(graph,v2)==0||_find(graph,v1)==0){
            exit(-1);
        }
        graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=1;
    }
    return;
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
void Create_UDG(M_G &graph){//创建无向图
    cout<<"顶点数量: ";
    cin>>graph->_vertex;
    cout<<"弧数量: ";
    cin>>graph->_arc;
    cout<<"输入顶点的值:"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        cin>>graph->vertex[i];
    }
    cout<<"输入弧尾和弧头:"<<endl;
    char v1,v2;//v1弧头,v2弧尾,即从v2指向v1,不带权
    for(int i=1;i<=graph->_arc;++i){
        cin>>v2>>v1;
        if(_find(graph,v2)==0||_find(graph,v1)==0){
            exit(-1);
        }
        graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=1;
        graph->Mar[_find(graph,v1)][_find(graph,v2)].weight=1;
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
    cout<<"0:创建有向图 1:创建带权有向图 2:创建无向图 3:创建带权无向图"<<endl;
    cout<<"选项: ";
    graph=new Martrix_Graph;
    cin>>(int &)graph->kind;
    switch(graph->kind){
        case DG:
            Create_DG(graph);
            break;
        case DN:
            Create_DN(graph);
            break;
        case UDG:
            Create_UDG(graph);
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
void Add_vertex(M_G &graph,char item){//添加一个顶点
    graph->_vertex++;
    graph->vertex[graph->_vertex]=item;
    if(graph->kind==DN||graph->kind==UDN){
        for(int i=1;i<=graph->_vertex;++i){
            graph->Mar[i][graph->_vertex].weight=INF;
        }
        for(int i=1;i<=graph->_vertex;++i){
            graph->Mar[graph->_vertex][i].weight=INF;
        }
    }
    return;
}
void Add_arc(M_G &graph,char v2,char v1,int weight=1){//添加一条弧,v1弧头,v2弧尾,即从v2指向v1,不带权的weight默认为1
    if(_find(graph,v2)&&_find(graph,v1)){
        graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=weight;
        if(graph->kind==UDG||graph->kind==UDN){
            graph->Mar[_find(graph,v1)][_find(graph,v2)].weight=weight;
        }
    }
    return;
}
void Delete_vertex(M_G &graph,char item){//删除一个顶点
    int posi=_find(graph,item);
    if(posi){
        for(int i=posi;i<graph->_vertex;++i){
            for(int j=1;j<=graph->_vertex;++j){
                graph->Mar[i][j]=graph->Mar[i+1][j];
            }
        }
        if(graph->kind==DN||graph->kind==UDN){
            for(int j=1;j<=graph->_vertex;++j){
                graph->Mar[graph->_vertex][j].weight=INF;
            }
        }
        else{
            for(int j=1;j<=graph->_vertex;++j){
                graph->Mar[graph->_vertex][j].weight=0;
            }
        }
        for(int i=posi;i<graph->_vertex;++i){
            for(int j=1;j<=graph->_vertex;++j){
                graph->Mar[j][i]=graph->Mar[j][i+1];
            }
        }
        if(graph->kind==DN||graph->kind==UDN){
            for(int j=1;j<=graph->_vertex;++j){
                graph->Mar[j][graph->_vertex].weight=INF;
            }
        }
        else{
            for(int j=1;j<=graph->_vertex;++j){
                graph->Mar[j][graph->_vertex].weight=0;
            }
        }
        for(int i=posi;i<graph->_vertex;++i){
            graph->vertex[i]=graph->vertex[i+1];
        }
        graph->vertex[graph->_vertex]=0;
        graph->_vertex--;
    }
    return;
}
void Delete_arc(M_G &graph,char v2,char v1){//删除一条弧,v1弧头,v2弧尾,即从v2指向v1
    if(_find(graph,v2)&&_find(graph,v1)){
        if(graph->kind==DG){
            graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=0;
        }
        else if(graph->kind==DN){
            graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=INF;
        }
        else if(graph->kind==UDG){
            graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=0;
            graph->Mar[_find(graph,v1)][_find(graph,v2)].weight=0;
        }
        else{
            graph->Mar[_find(graph,v2)][_find(graph,v1)].weight=INF;
            graph->Mar[_find(graph,v1)][_find(graph,v2)].weight=INF;
        }
    }
    return;
}
int Fir_posi(M_G graph,char item){//返回与item链接的第一个邻接顶点序号,即与item链接的第一个弧头(检索邻接矩阵的某一列)
    int check;
    if(graph->kind==DG||graph->kind==UDG){
        check=0;
    }
    else{
        check=INF;
    }
    int posi=_find(graph,item);
    if(posi){
        for(int i=1;i<=graph->_vertex;++i){
            if(graph->Mar[posi][i].weight!=check){
                return i;
            }
        }
    }
    return 0;
}
int Next_posi(M_G graph,char item,char now){//返回与item链接并且在now之后的顶点序号,即与item链接的其他弧头
    int check;
    if(graph->kind==DG||graph->kind==UDG){
        check=0;
    }
    else{
        check=INF;
    }
    int posi1=_find(graph,item);
    int posi2=_find(graph,now);
    if(posi1&&posi2){
        for(int i=posi2+1;i<=graph->_vertex;++i){
            if(graph->Mar[posi1][i].weight!=check){
                return i;
            }
        }
    }
    return 0;
}
void _DFS(M_G graph,int posi){
    visited[posi]=true;
    cout<<graph->vertex[posi];
    for(int i=Fir_posi(graph,graph->vertex[posi]);i>0;i=Next_posi(graph,graph->vertex[posi],graph->vertex[i])){
        if(!visited[i]){
            _DFS(graph,i);
        }
    }
    return;
}
void DFS(M_G graph){
    for(int i=1;i<=graph->_vertex;++i){
        if(!visited[i]){
            _DFS(graph,i);
        }
    }
    cout<<endl;
    fill(visited,visited+_MAX,0);
    return;
}
void BFS(M_G graph){
    fill(visited,visited+_MAX,0);
    queue<int> q;
    int check;
    if(graph->kind==DG||graph->kind==UDG){
        check=0;
    }
    else{
        check=INF;
    }
    for(int i=1;i<=graph->_vertex;++i){
        if(!visited[i]){
            q.push(i);
            visited[i]=true;
            while(!q.empty()){
                int temp=q.front();
                q.pop();
                cout<<graph->vertex[temp];
                for(int j=1;j<=graph->_vertex;++j){
                    if(!visited[j]&&graph->Mar[temp][j].weight!=check){
                        q.push(j);
                        visited[j]=true;
                    }
                }
            }
        }
    }
    cout<<endl;
    fill(visited,visited+_MAX,0);
    return;
}
void print(M_G graph){
    if(graph->kind==DG||graph->kind==UDG){
        for(int i=1;i<=graph->_vertex;++i){
            for(int j=1;j<=graph->_vertex;++j){
                cout<<graph->Mar[i][j].weight<<' ';
            }
            cout<<endl;
        }
    }
    else{
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
    }
}
int main(){
    M_G graph=NULL;
    Create_Graph(graph);
    cout<<"当前图的类型: ";
    switch(graph->kind){
        case DG:
            cout<<"有向图"<<endl;
            break;
        case DN:
            cout<<"带权有向图"<<endl;
            break;
        case UDG:
            cout<<"无向图"<<endl;
            break;
        case UDN:
            cout<<"带权无向图"<<endl;
            break;
    }
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除顶点b"<<endl;
    Delete_vertex(graph,'b');
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除顶点a"<<endl;
    Delete_vertex(graph,'a');
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除弧d->f"<<endl;
    Delete_arc(graph,'d','f');
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除弧d->c"<<endl;
    Delete_arc(graph,'d','c');
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"添加顶点g"<<endl;
    Add_vertex(graph,'g');
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"添加弧g->c";
    if(graph->kind==DG||graph->kind==UDG){
        cout<<endl;
        Add_arc(graph,'g','c');
    }
    else{
        cout<<" weight:6"<<endl;
        Add_arc(graph,'g','c',6);
    }
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"添加弧e->g";
    if(graph->kind==DG||graph->kind==UDG){
        cout<<endl;
        Add_arc(graph,'e','g');
    }
    else{
        cout<<" weight:7"<<endl;
        Add_arc(graph,'e','g',7);
    }
    cout<<"邻接矩阵: "<<endl;
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    delete graph;
    graph=NULL;
    return 0;
}
```

***Sample***
```
6 10 abcdef
a b
a d
b c
c a
c f
d c
d f
e d
f a
f e

6 10 abcdef
a b 5
a d 7
b c 4
c a 8
c f 9
d c 5
d f 6
e d 5
f a 3
f e 1
```

***Out***
```
当前图的类型: 带权有向图
邻接矩阵: 
∞ 5 ∞ 7 ∞ ∞ 
∞ ∞ 4 ∞ ∞ ∞ 
8 ∞ ∞ ∞ ∞ 9 
∞ ∞ 5 ∞ ∞ 6 
∞ ∞ ∞ 5 ∞ ∞ 
3 ∞ ∞ ∞ 1 ∞ 
DFS: abcfed
BFS: abdcfe
----------------
删除顶点b
邻接矩阵: 
∞ ∞ 7 ∞ ∞ 
8 ∞ ∞ ∞ 9 
∞ 5 ∞ ∞ 6 
∞ ∞ 5 ∞ ∞ 
3 ∞ ∞ 1 ∞ 
DFS: adcfe
BFS: adcfe
----------------
删除顶点a
邻接矩阵: 
∞ ∞ ∞ 9 
5 ∞ ∞ 6 
∞ 5 ∞ ∞ 
∞ ∞ 1 ∞ 
DFS: cfed
BFS: cfed
----------------
删除弧d->f
邻接矩阵: 
∞ ∞ ∞ 9 
5 ∞ ∞ ∞ 
∞ 5 ∞ ∞ 
∞ ∞ 1 ∞ 
DFS: cfed
BFS: cfed
----------------
删除弧d->c
邻接矩阵: 
∞ ∞ ∞ 9 
∞ ∞ ∞ ∞ 
∞ 5 ∞ ∞ 
∞ ∞ 1 ∞ 
DFS: cfed
BFS: cfed
----------------
添加顶点g
邻接矩阵: 
∞ ∞ ∞ 9 ∞ 
∞ ∞ ∞ ∞ ∞ 
∞ 5 ∞ ∞ ∞ 
∞ ∞ 1 ∞ ∞ 
∞ ∞ ∞ ∞ ∞ 
DFS: cfedg
BFS: cfedg
----------------
添加弧g->c weight:6
邻接矩阵: 
∞ ∞ ∞ 9 ∞ 
∞ ∞ ∞ ∞ ∞ 
∞ 5 ∞ ∞ ∞ 
∞ ∞ 1 ∞ ∞ 
6 ∞ ∞ ∞ ∞ 
DFS: cfedg
BFS: cfedg
----------------
添加弧e->g weight:7
邻接矩阵: 
∞ ∞ ∞ 9 ∞ 
∞ ∞ ∞ ∞ ∞ 
∞ 5 ∞ ∞ 7 
∞ ∞ 1 ∞ ∞ 
6 ∞ ∞ ∞ ∞ 
DFS: cfedg
BFS: cfedg
```