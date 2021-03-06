```c++
/*求拓扑排序和关键路径*/
#include<iostream>
#include<algorithm>
#include<stack>
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
bool visited[_MAX]={0};
int Indegree[_MAX]={0};//记录入度
int Earliest[_MAX]={0};//记录节点的最早出现时间
int Latest[_MAX]={0};//记录节点的最迟出现时间
stack<int> path;
inline int _find(M_G graph,char item){//查找当前值对应的序号,用于确定其在邻接矩阵的行或列
    for(int i=1;i<=graph->_vertex;++i){
        if(graph->vertex[i]==item){
            return i;
        }
    }
    return 0;
}
void Create_DG(M_G &graph){//创建有向图
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
        Indegree[_find(graph,v1)]++;
    }
    return;
}
int Fir_posi(M_G graph,char item){//返回与item链接的第一个邻接顶点序号,即与item链接的第一个弧头(检索邻接矩阵的某一列)
    int check=INF;
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
    int check=INF;
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
int TopologicalSort(M_G graph){
    stack<int> topology;
    for(int i=1;i<=graph->_vertex;++i){
        if(!Indegree[i]){//将入度为0的点压入栈中
            topology.push(i);
        }
    }
    int count=0;//记录顶点个数,若有向图中含有环,则count小于图的顶点个数
    int now;
    cout<<"拓扑排序: ";
    while(!topology.empty()){
        now=topology.top();
        path.push(now);
        topology.pop();
        cout<<graph->vertex[now]<<" ";
        ++count;
        for(int i=Fir_posi(graph,graph->vertex[now]);i>0;i=Next_posi(graph,graph->vertex[now],graph->vertex[i])){//将以now为弧尾的弧去除
            if(!(--Indegree[i])){//若入度减为0,则入栈
                topology.push(i);
            }
            Earliest[i]=max(Earliest[i],Earliest[now]+graph->Mar[now][i].weight);//按最大的权重计算
            /*例子
            1->2 a1=6 2->4 a3=1
            1->3 a2=4 3->4 a4=1
            4->....
            对于节点4来说,要开始4之后的状态,必须要完成1->2->4以及1->3->4
            1->2->4所花费的时间为7
            1->3->4所花费的时间为5
            若以1->3->4计算,完成1->3->4时,1->2->4尚未完成,此时4之后的状态无法开始
            因此求出到达各个状态的最早时间必须按最大值来计算
            */
        }
    }
    cout<<endl;
    if(count<graph->_vertex){//含有环
        return -1;
    }
    else{
        return 0;
    }
}
int CriticalPath(M_G graph){
    if(TopologicalSort(graph)==-1){
        return -1;
    }
    fill(Latest,Latest+1+graph->_vertex,Earliest[graph->_vertex]);
    int now;
    while(!path.empty()){
        now=path.top();
        path.pop();
        for(int i=Fir_posi(graph,graph->vertex[now]);i>0;i=Next_posi(graph,graph->vertex[now],graph->vertex[i])){
            Latest[now]=min(Latest[now],Latest[i]-graph->Mar[now][i].weight);
            /*例子
            假定汇点为9
            Earliest[9]=18
            5->7 weight=5 7->9 weight=2
            5->8 weight=7 8->9 weight=4
            则节点7的最迟开始时间为18-2=16
            则节点8的最迟开始时间为18-4=14
            则节点5的最迟开始时间为16-5=11或者14-7=7
            如果取11,那么要完成5->8->9这段路径的时间将超出预期
            所以只能取7,保证两条路径都能顺利完成,即取最小值
            */
        }
    }
    cout<<"关键路径: ";
    int i,sum=0;
    for(i=1;i<=graph->_vertex;++i){
        if(Latest[i]==Earliest[i]){
            cout<<graph->vertex[i];
            sum+=Latest[i];
            break;
        }
    }
    for(++i;i<=graph->_vertex;++i){
        if(Latest[i]==Earliest[i]){
            cout<<"->"<<graph->vertex[i];
            sum+=Latest[i];
        }
    }
    cout<<" "<<sum;
    return 0;
}
int main(){
    M_G graph=NULL;
    Create_DG(graph);
    CriticalPath(graph);
    delete graph;
    graph=NULL;
    return 0;
}
```

[参考](https://www.jianshu.com/p/1857ed4d8128)

***Sample***
```
9 11 123456789
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4
```

***Out***
```
拓扑排序: 1 4 6 3 2 5 8 7 9 
关键路径: 1->2->5->7->8->9 61
```