#include<iostream>
#define MAX_SIZE 5
using namespace std;
typedef struct linear_list{//跳过head[0],从head[1]开始存储
    int *head=NULL;
    int list_length;
    int list_size;//记录当前已分配给head的空间
}list;
inline bool _compare_greater(int a,int b){
    return a>b?1:0;
}
inline bool _compare_smaller(int a,int b){
    return a<b?1:0;
}
inline bool _compare_equal(int a,int b){
    return a==b?1:0;
}
void list_create(list *l){
    l->head=(int *)malloc(MAX_SIZE*sizeof(int));
    if(l->head==NULL){
        exit(-1);//内存不足
    }
    l->list_length=0;
    l->list_size=MAX_SIZE;
}
void list_clear(list *l){//清空linear_list,但不释放内存
    l->list_length=0;
}
void list_destroy(list *l){//销毁linear_list
    free(l->head);
    l->head=NULL;//指针空置
    l->list_length=0;
    l->list_size=0;
}
bool list_isEmpty(list *l){//判断linear_list是否为空
    return l->list_length==0?1:0;
}
int get_listlength(list *l){//获取linear_list的长度
    return l->list_length;
}
int get_listitem(list *l,int posi,int &k){//获取list[posi]的值
    if(posi<=0||posi>l->list_length){
        cout<<"out_of_length"<<endl;
        return 0;//数组越界
    }
    k=l->head[posi];
    return 1;
}
void list_insert(list *l,int posi,const int k){//前插
    if(posi<1||posi>l->list_length+1){
        cout<<"out_of_length"<<endl;
        return;//数组越界
    }
    if(l->list_length+1>=l->list_size){
        int *new_list=NULL;
        new_list=(int *)realloc(l->head,(MAX_SIZE+l->list_size)*sizeof(int));//扩容
        if(new_list==NULL){
            exit(-1);//内存不足
        }
        l->head=new_list;
        l->list_size+=MAX_SIZE;
    }
    for(int i=l->list_length+1;i>posi;--i){
        l->head[i]=l->head[i-1];
    }
    l->head[posi]=k;
    ++l->list_length;
    return;
}
void item_delete(list *l,int posi){//在linear_list中删除某个元素
    if(posi<1||posi>l->list_length){
        cout<<"out_of_length";
        return;//数组越界
    }
    for(int i=posi;i<l->list_length;++i){
        l->head[i]=l->head[i+1];
    }
    l->head[l->list_length]=0;
    l->list_length--;
    return;
}
int list_find(list *l,int e,bool (*com)(int,int)){//依据条件进行查找
    int *q=&l->head[1];
    int i=1;
    while(i<=l->list_length&&!(*com)(*q,e)){
        ++i;
        ++q;
    }
    if(i<l->list_length){
        return i;
    }
    else{
        return -1;//查找失败
    }
}
int find_prev_item(list *l,int now_item,int &prev_item){//返回当前数据元素的前驱
    int i=1;
    if(now_item!=l->head[1]){//第一个元素无前驱
        while(i<=l->list_length&&now_item!=l->head[i]){
            ++i;
        }
        if(i<=l->list_length){
            prev_item=l->head[i-1];
            return 1;
        }
    }
    return 0;//无前驱
}
int find_next_item(list *l,int now_item,int &next_item){//返回当前数据元素的后继
    int i=1;
    while(i<l->list_length&&now_item!=l->head[i]){//最后一个元素无后继
        ++i;
    }
    if(i<l->list_length){
        next_item=l->head[i+1];
        return 1;
    }
    return 0;//无后继
}
void merge_list(list *a,list *b,list *c){//有序线性表合并
    c->head=(int *)malloc((a->list_size+b->list_size)*sizeof(int));
    if(c->head==NULL){
        exit(-1);//内存不足
    }
    int i=1,j=1,k=1;
    while(i<=a->list_length&&j<=b->list_length){
        if(a->head[i]<b->head[j]){
            c->head[k++]=a->head[i++];
            ++c->list_length;
        }
        else{
            c->head[k++]=b->head[j++];
            ++c->list_length;
        }
    }
    for(int t=i;t<=a->list_length;++t){
        c->head[k++]=a->head[t];
        ++c->list_length;
    }
    for(int t=j;t<=b->list_length;++t){
        c->head[k++]=b->head[t];
        ++c->list_length;
    }
    return;
}
void print(list *l){
    for(int i=1;i<=l->list_length;++i){
        cout<<"posi: "<<i<<" value:"<<l->head[i]<<endl;
    }
    return;
}
int main(){
    list a,b,c;
    int item,posi;
    int point;
    list_create(&a);//创建线性表
    list_create(&b);//创建线性表
    for(int i=1;i<=7;++i){
        list_insert(&a,i,i*i);//在线性表中插入元素
    }
    for(int i=1;i<=7;++i){
        list_insert(&b,i,i+i);//在线性表中插入元素
    }
    merge_list(&a,&b,&c);
    print(&c);
    cout<<"length: "<<get_listlength(&a)<<endl;//获取线性表的长度
    get_listitem(&a,6,item)?cout<<"list["<<6<<"]= "<<item<<endl:cout<<"Fail"<<endl;//获取某个元素
    list_insert(&a,6,12345);//在某个元素前面插入数据
    posi=list_find(&a,10,_compare_greater);//寻找第一个满足某个条件的元素的位置
    if(posi==-1){
        cout<<"No_item_match_this_condition"<<endl;
    }
    else{
        cout<<"posi: "<<posi<<endl;
    }
    find_prev_item(&a,16,point)?cout<<point<<endl:cout<<"Fail_to_find_prev_item_of_16"<<endl;//查找前驱
    find_next_item(&a,16,point)?cout<<point<<endl:cout<<"Fail_to_find_next_item_of_16"<<endl;//查找后继
    print(&a);
    list_clear(&a);
    list_isEmpty(&a)?cout<<"Empty"<<endl:cout<<"not_Empty"<<endl;//检测线性表是否为空
    list_destroy(&a);
    return 0;
}
