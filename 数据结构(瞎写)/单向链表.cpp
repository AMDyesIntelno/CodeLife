#include<iostream>
using namespace std;
typedef struct link_list{//头结点的data留空
    int data;
    struct link_list *next=NULL;
}*list;
void list_create(list &l,int n){
    l=new link_list;
    list p=l;
    for(int i=1;i<=n;++i){
        list now=new link_list;
        now->data=i*i;
        p->next=now;
        p=now;
    }
    return;
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
int list_insert(list l,int posi,int value){
    if(posi<1||posi>list_length(l)){
        return 0;//越界
    }
    while(posi>1){
        l=l->next;
        posi--;
    }
    list p=new link_list;
    p->data=value;
    p->next=l->next;
    l->next=p;
    return 1;
}
int item_delete(list l,int posi){//删除某个元素
    if(posi<1||posi>list_length(l)){
        return 0;//越界
    }
    list p=l;
    while(posi>0){
        p=l;
        l=l->next;
        posi--;
    }
    p->next=l->next;
    delete l;
    return 1;
}
int get_item(list l,int posi,int &value){//获取某个元素
    if(posi<1||posi>list_length(l)){
        return 0;//越界
    }
    while(posi>0){
        l=l->next;
        posi--;
    }
    value=l->data;
    return 1;
}
void merge_list(list a,list b,list &c){
    list pa=a->next;
    list pb=b->next;
    c=new link_list;
    list pc=c;
    while(pa&&pb){
        if(pa->data<pb->data){
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else{
            pc->next=pb;
            pc=pc->next;
            pb=pb->next;
        }
    }
    if(pa){
        pc->next=pa;
    }
    if(pb){
        pc->next=pb;
    }
    return;
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
    list b=NULL;
    list c=NULL;
    int value;
    list_create(a,5);
    list_create(b,10);
    print_list(a);
    print_list(b);
    merge_list(a,b,c);
    print_list(c);
    cout<<list_length(a)<<endl;
    list_insert(a,5,10086);
    print_list(a);
    item_delete(a,1);
    print_list(a);
    get_item(a,3,value);
    cout<<value<<endl;
    list_destroy(a);
    list_destroy(b);
    list_destroy(c);
    return 0;
}
