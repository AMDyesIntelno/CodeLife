```c++
/*无向图生成树*/
#include<iostream>
#include<queue>
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
typedef struct CSTree{
    char data=0;
    struct CSTree *child=NULL;
    struct CSTree *brother=NULL;
}*cstree;
bool visited[_MAX]={0};
inline int _find(M_G graph,char item){//查找当前值对应的序号,用于确定其在邻接矩阵的行或列
    for(int i=1;i<=graph->_vertex;++i){
        if(graph->vertex[i]==item){
            return i;
        }
    }
    return 0;
}
void Create_UDG(M_G &graph){//创建无向图
    graph=new Martrix_Graph;
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
int Fir_posi(M_G graph,char item){//返回与item链接的第一个邻接顶点序号,即与item链接的第一个弧头(检索邻接矩阵的某一列)
    int check=0;
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
    int check=0;
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
void DFSTree(M_G graph,int posi,cstree &tree){
    int check=0;
    cstree temp=NULL,now=NULL;
    visited[posi]=true;
    for(int i=Fir_posi(graph,graph->vertex[posi]);i>0;i=Next_posi(graph,graph->vertex[posi],graph->vertex[i])){
        if(!visited[i]){
            temp=new CSTree;
            temp->data=graph->vertex[i];
            if(check==0){/*同一层的第一个节点作为上一层的孩子节点*/
                tree->child=temp;
                check=1;
            }
            else{/*同一层的其余节点作为同一层的兄弟节点*/
                now->brother=temp;
            }
            now=temp;
            DFSTree(graph,i,now);
        }
    }
}
void DFSForest(M_G graph,cstree &tree){
    cstree temp=NULL,now=NULL;
    fill(visited,visited+_MAX,0);
    for(int i=1;i<=graph->_vertex;++i){
        if(!visited[i]){
            temp=new CSTree;
            temp->data=graph->vertex[i];
            if(!tree){/*树为空,则赋值给树*/
                tree=temp;
            }
            else{/*树非空,则赋值给树的兄的节点*/
                now->brother=temp;
            }
            now=temp;
            DFSTree(graph,i,now);
        }
    }
    return;
}
void print_graph(M_G graph){
    for(int i=1;i<=graph->_vertex;++i){
        for(int j=1;j<=graph->_vertex;++j){
            cout<<graph->Mar[i][j].weight<<' ';
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}
void print_tree(cstree tree){
    if(tree){
        cout<<tree->data;
        print_tree(tree->child);
        print_tree(tree->brother);
    }
    return;
}
void clear_tree(cstree &tree){
    if(tree){
        clear_tree(tree->child);
        clear_tree(tree->brother);
        delete tree;
        tree=NULL;
    }
    return;
}
int main(){
    M_G graph=NULL;
    cstree tree=NULL;
    Create_UDG(graph);
    print_graph(graph);
    DFSForest(graph,tree);
    print_tree(tree);
    delete graph;
    graph=NULL;
    clear_tree(tree);
    return 0;
}
```

***Sample***
```
13 13 abcdefghijklm
a b
a c
a f
a l
b m
m l
m j
l j
d e
g h
g k
k h
g i
```

***Out***
```
0 1 1 0 0 1 0 0 0 0 0 1 0 
1 0 0 0 0 0 0 0 0 0 0 0 1 
1 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 0 0 0 0 0 
0 0 0 1 0 0 0 0 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 1 1 0 1 0 0 
0 0 0 0 0 0 1 0 0 0 1 0 0 
0 0 0 0 0 0 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 1 1 
0 0 0 0 0 0 1 1 0 0 0 0 0 
1 0 0 0 0 0 0 0 0 1 0 0 1 
0 1 0 0 0 0 0 0 0 1 0 1 0 

abmjlcfdeghki
```