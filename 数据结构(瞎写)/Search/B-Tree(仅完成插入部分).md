```c++
#include<iostream>
#define MAX 3
#define MIN 2
using namespace std;
typedef struct BTreeNode{
    int data[MAX+1]={0};
    int count=0;
    struct BTreeNode *link[MAX+1]={NULL};
}*BTree;
void CreateNode(int data,BTree &newnode,BTree child,BTree root){//创建新节点
    if(newnode==NULL){
        newnode=new BTreeNode;
        newnode->data[1]=data;
        newnode->count=1;
        newnode->link[0]=root;
        newnode->link[1]=child;
    }
    return;
}
void AddDataToNode(int data,int posi,BTree &node,BTree child){//向节点中插入元素
    int count=node->count;
    while(count>posi){//移动元素,腾出位置
        node->data[count+1]=node->data[count];
        node->link[count+1]=node->link[count];
        count--;
    }
    node->data[count+1]=data;
    node->link[count+1]=child;
    node->count++;
    return;
}
void SplitNode(int &data,int posi,BTree node,BTree child,BTree &newnode){//节点分离
    int mid,j;
    mid=(MAX+MIN)/2;//元素的值的中位数在数组的中间
    /*if(posi>MIN){
        mid=MIN+1;
    }
    else{
        mid=MIN;
    }*/
    j=mid+1;
    newnode=new BTreeNode;
    while(j<=MAX){//将中位数后面的数存入到新的节点的数组中
        newnode->data[j-mid]=node->data[j];
        newnode->link[j-mid]=node->link[j];
        ++j;
    }
    node->count=mid;//原节点剩下mid个元素
    newnode->count=MAX-mid;//新的节点共有MAX-mid个元素
    if(posi<=mid/*MIN*/){//确定将新的元素插入到那个节点中
        AddDataToNode(data,posi,node,child);
    }
    else{
        AddDataToNode(data,posi-mid,newnode,child);
    }
    data=node->data[mid];//data是引用传递,修改data的值为中位数的值,为节点分离做准备
    newnode->link[0]=node->link[mid];//mid元素的后继修改为newnode的前驱,以保持遍历顺序不变
    node->count--;//将中位数从原节点中剔除
    return;
}
int FindPosi(int &data,BTree node,BTree &child){//确定元素的插入位置
    int posi;
    if(node==NULL){//当前节点为空,说明已经确认插入位置
        return 1;
    }
    if(data<node->data[1]){//当前数值小于第一个元素,向前查找
        posi=0;
    }
    else{
        for(posi=node->count;data<node->data[posi]&&posi>1;posi--);//确定插入位置
        if(data==node->data[posi]){
            cout<<"ERROR!!!"<<endl;
            return 0;
        }
    }
    if(FindPosi(data,node->link[posi],child)){
        if(node->count<MAX){//当前节点数量没达到上限,直接插入,插入到posi之后
            AddDataToNode(data,posi,node,child);
        }
        else{//达到上限,将节点分离,分离完成后,还需要检查上层的节点数量是否达到上限
            SplitNode(data,posi,node,child,child);
            return 1;
        }
    }
    return 0;
}
void InsertNode(int data,BTree &root){//插入节点的主函数
    int check;
    BTree child=NULL;
    check=FindPosi(data,root,child);
    if(check){
        BTree newnode=NULL;
        CreateNode(data,newnode,child,root);
        root=newnode;//更新root
    }
}
void search(int data,int &posi,BTree node){//查找是否存在该元素
    if(node){
        if(data<node->data[1]){
            posi=0;
        }
        else{
            for(posi=node->count;data<node->data[posi]&&posi>1;posi--){
                if(data=node->data[posi]){
                    cout<<data<<" found!!!"<<endl;
                    return;
                }
            }
        }
        search(data,posi,node->link[posi]);
    }
    return;
}
void traversal(BTree node){//类似中序遍历
    if(node){
        for(int i=0;i<node->count;++i){
            traversal(node->link[i]);
            cout<<node->data[i+1]<<' ';
        }
        traversal(node->link[node->count]);
    }
    return;
}
int main(){
    BTree root=NULL;
    InsertNode(8,root);
    InsertNode(9,root);
    InsertNode(10,root);
    InsertNode(11,root);
    InsertNode(15,root);
    InsertNode(16,root);
    InsertNode(17,root);
    InsertNode(18,root);
    InsertNode(20,root);
    InsertNode(23,root);
    InsertNode(7,root);
    traversal(root);
    return 0;
}
```

[参考](https://www.programiz.com/dsa/b-tree#code)

[参考](https://www.programiz.com/dsa/insertion-into-a-b-tree)

[参考](https://www.programiz.com/dsa/deletion-from-a-b-tree)

***Out***
```
7 8 9 10 11 15 16 17 18 20 23
```