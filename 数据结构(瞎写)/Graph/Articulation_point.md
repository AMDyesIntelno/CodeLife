```c++
/*查找关节点*/
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
int _count=0;//记录某个节点的第一次被发现的时间
int root[_MAX]={0};//以当前结点为根的树可以直接追溯的最早祖先位置
int _min[_MAX]={0};//临时记录访问时间的最小值
int num[_MAX]={0};//记录节点的访问时间,并用于判断是否已经遍历
bool ap[_MAX]={0};//记录是否为关节点
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
void DFS(M_G graph,int start){
    int children=0;//记录孩子节点个数
    ++_count;
    num[start]=_count;//记录start节点的发现时间
    _min[start]=_count;
    for(int i=Fir_posi(graph,graph->vertex[start]);i>0;i=Next_posi(graph,graph->vertex[start],graph->vertex[i])){
        if(!num[i]){
            ++children;
            root[i]=start;//i的根节点是start
            DFS(graph,i);
            _min[start]=min(_min[start],_min[i]);//尝试对_min[start]刷新,将其替换成_min[i],原因见else if的第二点
            if(!root[start]&&children>1){
                //当start是树的根节点时,若存在右子树,即children>1,说明根节点为关节点
                ap[start]=true;
            }
            if(root[start]&&_min[i]>=num[start]){
                //当start不是树的根节点时,若i能够追溯到的最早的根节点的记录时间仍然比当前DFS的节点的记录时间晚
                //说明i没有回边链接到start的根节点,即说明start为关节点
                ap[start]=true;
            }
        }
        else if(i!=root[start]){
            /*i作为start的邻接点,当i已经被标记时,说明i在start之前已被标记,有两种情况(基于生成树来考虑)
            1.i是start的直接根节点(i<->start,i==root[start]),由于是无向图,start与i连接,i也与start连接,这种情况不进行考虑
            2.i是start的间接根节点(i<->xxx<->start,i!=root[start]),说明i在start之前已经被标记,即存在回边,那么尝试对_min[start]刷新,将其替换成num[i]*/
            _min[start]=min(_min[start],num[i]);
        }
    }
    return;
}
void Search_Articulation_Point(M_G graph){
    for(int i=1;i<=graph->_vertex;++i){
        if(!num[i]){
            DFS(graph,i);
        }
    }
    for(int i=1;i<=graph->_vertex;++i){
        if(ap[i]){
            cout<<graph->vertex[i]<<' ';
        }
    }
    return;
}
int main(){
    M_G graph=NULL;
    Create_UDG(graph);
    Search_Articulation_Point(graph);
    return 0;
}
```

[参考](https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/)

***Sample***
```
13 17 abcdefghijklm
a b
a c
a f
a l
b c
b d
b g
b h
b m
d e
g h
g k
g i
h k
j l
j m
l m
-------------------
5 5 01234
1 0
0 2
2 1
0 3
3 4
-------------------
4 3 0123
0 1
1 2
2 3
-------------------
7 8 0123456
0 1
1 2
2 0
1 3
1 4
1 6
3 5
4 5
```

***Out***
```
a b d g
-------------------
0 3
-------------------
1 2
-------------------
1
```