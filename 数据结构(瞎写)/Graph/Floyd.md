```c++
#include<iostream>
#define INF INT32_MAX/2
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
void Floyd(M_G graph,int path[][_MAX]){
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(i==j){
                path[i][j]=0;
                continue;
            }
            path[i][j]=graph->Mar[i][j].weight;
        }
    }
    cout<<"初始化..."<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(path[i][j]==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<path[i][j]<<' ';
        }
        cout<<endl;
    }
    /*cout<<endl<<"经过顶点3进行中转"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            path[i][j]=min(path[i][j],path[i][3]+path[3][j]);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(path[i][j]==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<path[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<endl<<"经过顶点3,4进行中转"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            path[i][j]=min(path[i][j],path[i][3]+path[3][j]);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            path[i][j]=min(path[i][j],path[i][4]+path[4][j]);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(path[i][j]==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<path[i][j]<<' ';
        }
        cout<<endl;
    }*/
    cout<<endl<<"结果"<<endl;
    for(int i=1;i<=graph->_vertex;++i){//在第i次循环中,path数组中所有与i有关的值都不会改变
        for(int j=1;j<=graph->_vertex;++j){
            for(int k=1;k<=graph->_vertex;++k){
                path[k][j]=min(path[k][j],path[k][i]+path[i][j]);
            }
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            if(path[i][j]==INF){
                cout<<"∞"<<' ';
                continue;
            }
            cout<<path[i][j]<<' ';
        }
        cout<<endl;
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
    int path[_MAX][_MAX]={0};
    Floyd(graph,path);
    delete graph;
    graph=NULL;
    return 0;
}
```

[参考](https://wiki.jikexueyuan.com/project/easy-learn-algorithm/floyd.html)

***Sample***
```
4 8 1234
1 2 2
1 3 6
1 4 4
2 3 3
3 1 7
3 4 1
4 1 5
4 3 12
```

***Out***
```
当前图的类型: 带权有向图
邻接矩阵: 
∞ 2 6 4 
∞ ∞ 3 ∞ 
7 ∞ ∞ 1 
5 ∞ 12 ∞ 

初始化...
0 2 6 4 
∞ 0 3 ∞ 
7 ∞ 0 1 
5 ∞ 12 0 

结果
0 2 5 4 
9 0 3 4 
6 8 0 1 
5 7 10 0
```