```c++
#include<iostream>
#define OK 1
#define ERROR 0
using namespace std;
typedef int status;
typedef int elemtype;
typedef struct link_list{//头结点的data留空
    elemtype data;
    struct link_list *next=NULL;
}*list;
status list_create(list &l,int n){
    l=new link_list;
    list p=l;
    for(int i=1;i<=n;++i){
        list now=new link_list;
        now->data=i+1;
        p->next=now;
        p=now;
    }
    return OK;
}
int list_length(list l){
    list p=l->next;
    int k=0;
    while(p){
        ++k;
        p=p->next;
    }
    return k;
}
status list_insert(list l,int posi,elemtype value){
    if(posi<1||posi>list_length(l)){
        return ERROR;//越界
    }
    while(posi>1){
        l=l->next;
        posi--;
    }
    list p=new link_list;
    p->data=value;
    p->next=l->next;
    l->next=p;
    return OK;
}
status item_delete(list l,int posi){//删除某个元素
    if(posi<1||posi>list_length(l)){
        return ERROR;//越界
    }
    list p=l;
    while(posi>0){
        p=l;
        l=l->next;
        posi--;
    }
    p->next=l->next;
    delete l;
    return OK;
}
void print_list(list l){
    list p=l->next;
    while(p){
        cout<<p->data<<' ';
        p=p->next;
    }
    cout<<endl;
    return;
}
void list_destroy(list l){//销毁链表
    list p=l;
    while(l){
        p=l->next;
        delete l;
        l=p;
    }
    return;
}
int main(){
    list a=NULL;
    list_create(a,4);
    print_list(a);
    list_insert(a,4,9);
    print_list(a);
    item_delete(a,3);
    print_list(a);
    list_destroy(a);
    return 0;
}
```
