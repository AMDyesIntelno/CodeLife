```c++
/*十字链表*/
#include<iostream>
#include<queue>
#define _MAX 21
using namespace std;
typedef enum{
    DG,DN
}Graphkind;//有向图,带权有向图
struct ARC{//记录弧
    int head,tail;//记录当前弧的弧头和弧尾
    struct ARC *head_node=NULL;//弧头相同的下一条弧
    struct ARC *tail_node=NULL;//弧尾相同的下一条弧
    int weight;
};
typedef struct VERTEX{//记录顶点
    char data;//记录顶点的值
    ARC *first_in=NULL;//记录该顶点的第一条入弧
    ARC *first_out=NULL;//记录该顶点的第一条出弧
}vertex[_MAX];
typedef struct OL_Graph{
    vertex v;
    Graphkind kind;//图的类型
    int _vertex,_arc;//顶点数量,弧数量
}*OL_G;
bool visited[_MAX]={0};
inline int _find(OL_G graph,char item){//查找当前值对应的序号
    for(int i=1;i<=graph->_vertex;++i){
        if(graph->v[i].data==item){
            return i;
        }
    }
    return 0;   
}
void Create_DG(OL_G &graph){//创建有向图
    cout<<"顶点数量: ";
    cin>>graph->_vertex;
    cout<<"弧数量: ";
    cin>>graph->_arc;
    cout<<"输入顶点的值:"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        cin>>graph->v[i].data;
    }
    cout<<"输入弧尾和弧头:"<<endl;
    char v1,v2;//v1弧头,v2弧尾,即从v2指向v1,不带权
    ARC *temp=NULL;
    for(int i=1;i<=graph->_arc;++i){
        cin>>v2>>v1;
        int posi1=_find(graph,v1);
        int posi2=_find(graph,v2);
        if(posi1==0||posi2==0){
            exit(-1);
        }
        temp=new ARC;
        temp->head=posi1;
        temp->tail=posi2;
        temp->weight=1;
        temp->head_node=graph->v[posi1].first_in;
        temp->tail_node=graph->v[posi2].first_out;
        graph->v[posi1].first_in=temp;
        graph->v[posi2].first_out=temp;
    }
    return;
}
void Create_DN(OL_G &graph){//创建带权有向图
    cout<<"顶点数量: ";
    cin>>graph->_vertex;
    cout<<"弧数量: ";
    cin>>graph->_arc;
    cout<<"输入顶点的值:"<<endl;
    for(int i=1;i<=graph->_vertex;++i){
        cin>>graph->v[i].data;
    }
    cout<<"输入弧尾,弧头和弧的权重:"<<endl;
    char v1,v2;
    int weight;//v1弧头,v2弧尾,即从v2指向v1,带权
    ARC *temp=NULL;
    for(int i=1;i<=graph->_arc;++i){
        cin>>v2>>v1>>weight;
        int posi1=_find(graph,v1);
        int posi2=_find(graph,v2);
        if(posi1==0||posi2==0){
            exit(-1);
        }
        temp=new ARC;
        temp->head=posi1;
        temp->tail=posi2;
        temp->weight=weight;
        temp->head_node=graph->v[posi1].first_in;
        temp->tail_node=graph->v[posi2].first_out;
        graph->v[posi1].first_in=temp;
        graph->v[posi2].first_out=temp;
    }
    return;
}
void Create_Graph(OL_G &graph){
    cout<<"0:创建有向图 1:创建带权有向图"<<endl;
    cout<<"选项: ";
    graph=new OL_Graph;
    cin>>(int &)graph->kind;
    switch(graph->kind){
        case DG:
            Create_DG(graph);
            break;
        case DN:
            Create_DN(graph);
            break;
        default:
            cout<<"ERROR!"<<endl;
            break;
    }
    return;
}
void Add_vertex(OL_G &graph,char item){//添加一个顶点
    graph->_vertex++;
    graph->v[graph->_vertex].data=item;
    return;
}
void Add_arc(OL_G &graph,char v2,char v1,int weight=1){//添加一条弧,v1弧头,v2弧尾,即从v2指向v1,不带权的weight默认为1
    if(_find(graph,v2)&&_find(graph,v1)){
        ARC *temp=new ARC;
        temp->head=_find(graph,v1);
        temp->tail=_find(graph,v2);
        temp->weight=weight;
        temp->head_node=graph->v[_find(graph,v1)].first_in;
        temp->tail_node=graph->v[_find(graph,v2)].first_out;
        graph->v[_find(graph,v1)].first_in=temp;
        graph->v[_find(graph,v2)].first_out=temp;
        graph->_arc++;
    }
    return;
}
void Delete_arc(OL_G &graph,char v2,char v1){//删除一条弧,v1弧头,v2弧尾,即从v2指向v1
    if(_find(graph,v2)&&_find(graph,v1)){
        int posi1=_find(graph,v1);
        int posi2=_find(graph,v2);
        ARC *posi1_now=graph->v[posi1].first_in;
        ARC *posi1_prev=NULL;
        if(posi1_now){
            if(posi1_now->head==posi1&&posi1_now->tail==posi2){
                posi1_prev=posi1_now;
                posi1_now=posi1_now->head_node;
                graph->v[posi1].first_in=posi1_now;
            }
            else{
                while(posi1_now&&(posi1_now->head!=posi1||posi1_now->tail!=posi2)){
                    posi1_prev=posi1_now;
                    posi1_now=posi1_now->head_node;
                }
                if(posi1_now){
                    posi1_prev->head_node=posi1_now->head_node;
                }
            }
        }
        ARC *posi2_now=graph->v[posi2].first_out;
        ARC *posi2_prev=NULL;
        if(posi2_now){
            if(posi2_now->head==posi1&&posi2_now->tail==posi2){
                posi2_prev=posi2_now;
                posi2_now=posi2_now->tail_node;
                delete posi2_prev;
                graph->v[posi2].first_out=posi2_now;
                graph->_arc--;
            }
            else{
                while(posi2_now&&(posi2_now->head!=posi1||posi2_now->tail!=posi2)){
                    posi2_prev=posi2_now;
                    posi2_now=posi2_now->tail_node;
                }
                if(posi2_now){
                    posi2_prev->tail_node=posi2_now->tail_node;
                    delete posi2_now;
                    graph->_arc--;
                }
            }
        }
    }
    return;
}
void Delete_vertex(OL_G &graph,char item){//删除一个顶点
    int posi=_find(graph,item);
    if(posi){
        for(int i=1;i<=graph->_vertex;++i){
            Delete_arc(graph,item,graph->v[i].data);
        }
        for(int i=1;i<=graph->_vertex;++i){
            Delete_arc(graph,graph->v[i].data,item);
        }
        for(int i=1;i<=graph->_vertex;++i){
            ARC *temp=graph->v[i].first_in;
            while(temp){
                if(temp->head>posi){
                    temp->head--;
                }
                if(temp->tail>posi){
                    temp->tail--;
                }
                temp=temp->head_node;
            }
        }
        for(int i=posi;i<graph->_vertex;++i){
            graph->v[i]=graph->v[i+1];
        }
        graph->v[graph->_vertex].data=0;
        graph->v[graph->_vertex].first_in=NULL;
        graph->v[graph->_vertex].first_out=NULL;
        --graph->_vertex;
    }
    return;
}
void _DFS(OL_G graph,int posi){
    visited[posi]=true;
    cout<<graph->v[posi].data;
    ARC *temp=graph->v[posi].first_out;
    while(temp){
        if(!visited[temp->head]){
            _DFS(graph,temp->head);
        }
        temp=temp->tail_node;
    }
    return;
}
void DFS(OL_G graph){
    fill(visited,visited+_MAX,0);
    for(int i=1;i<=graph->_vertex;++i){
        if(!visited[i]){
            _DFS(graph,i);
        }
    }
    cout<<endl;
    return;
}
void BFS(OL_G graph){
    fill(visited,visited+_MAX,0);
    queue<int> q;
    for(int i=1;i<=graph->_vertex;++i){
        if(!visited[i]){
            q.push(i);
            visited[i]=true;
            while(!q.empty()){
                int posi=q.front();
                q.pop();
                cout<<graph->v[posi].data;
                ARC *temp=graph->v[posi].first_out;
                while(temp){
                    if(!visited[temp->head]){
                        q.push(temp->head);
                        visited[temp->head]=true;
                    }
                    temp=temp->tail_node;
                }
            }
        }
    }
    cout<<endl;
    return;
}
void print(OL_G graph){
    if(graph->kind==DG){
        for(int i=1;i<=graph->_vertex;++i){
            ARC *temp=graph->v[i].first_out;
            while(temp){
                cout<<graph->v[temp->tail].data<<"->"<<graph->v[temp->head].data<<endl;
                temp=temp->tail_node;
            }
        }
    }
    else{
        for(int i=1;i<=graph->_vertex;++i){
            ARC *temp=graph->v[i].first_out;
            while(temp){
                cout<<graph->v[temp->tail].data<<"->"<<graph->v[temp->head].data<<" "<<temp->weight<<endl;
                temp=temp->tail_node;
            }
        }
    }
    return;
}
int main(){
    OL_G graph=NULL;
    Create_Graph(graph);
    cout<<"当前图的类型: ";
    switch(graph->kind){
        case DG:
            cout<<"有向图"<<endl;
            break;
        case DN:
            cout<<"带权有向图"<<endl;
            break;
    }
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除顶点b"<<endl;
    Delete_vertex(graph,'b');
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除顶点a"<<endl;
    Delete_vertex(graph,'a');
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除弧d->f"<<endl;
    Delete_arc(graph,'d','f');
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"删除弧d->c"<<endl;
    Delete_arc(graph,'d','c');
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"添加顶点g"<<endl;
    Add_vertex(graph,'g');
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"添加弧g->c";
    if(graph->kind==DG){
        cout<<endl;
        Add_arc(graph,'g','c');
    }
    else{
        cout<<" weight:6"<<endl;
        Add_arc(graph,'g','c',6);
    }
    print(graph);
    cout<<"DFS: ";
    DFS(graph);
    cout<<"BFS: ";
    BFS(graph);
    cout<<"----------------"<<endl;
    cout<<"添加弧e->g";
    if(graph->kind==DG){
        cout<<endl;
        Add_arc(graph,'e','g');
    }
    else{
        cout<<" weight:7"<<endl;
        Add_arc(graph,'e','g',7);
    }
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
a->d 7
a->b 5
b->c 4
c->f 9
c->a 8
d->f 6
d->c 5
e->d 5
f->e 1
f->a 3
DFS: adfecb
BFS: adbfce
----------------
删除顶点b
a->d 7
c->f 9
c->a 8
d->f 6
d->c 5
e->d 5
f->e 1
f->a 3
DFS: adfec
BFS: adfce
----------------
删除顶点a
c->f 9
d->f 6
d->c 5
e->d 5
f->e 1
DFS: cfed
BFS: cfed
----------------
删除弧d->f
c->f 9
d->c 5
e->d 5
f->e 1
DFS: cfed
BFS: cfed
----------------
删除弧d->c
c->f 9
e->d 5
f->e 1
DFS: cfed
BFS: cfed
----------------
添加顶点g
c->f 9
e->d 5
f->e 1
DFS: cfedg
BFS: cfedg
----------------
添加弧g->c weight:6
c->f 9
e->d 5
f->e 1
g->c 6
DFS: cfedg
BFS: cfedg
----------------
添加弧e->g weight:7
c->f 9
e->g 7
e->d 5
f->e 1
g->c 6
DFS: cfegd
BFS: cfegd
```