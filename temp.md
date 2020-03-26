```c++
#include<iostream>
#include<iomanip>
#include<algorithm>
#define MAX_SIZE 5
using namespace std;
typedef struct student{
    int number;
    char name[8];
    int a_mark;//数学的成绩
    int b_mark;//英语的成绩
    int c_mark;//数据结构的成绩
}*stu;
typedef struct linear_list{//跳过head[0],从head[1]开始存储
    stu head=NULL;
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
inline bool pd_a(student a,student b){
    if(a.a_mark>b.a_mark){
        return 1;
    }
    return 0;
}
inline bool pd_b(student a,student b){
    if(a.b_mark>b.b_mark){
        return 1;
    }
    return 0;
}
inline bool pd_c(student a,student b){
    if(a.c_mark>b.c_mark){
        return 1;
    }
    return 0;
}
void list_create(list *l){
    l->head=(stu)malloc(MAX_SIZE*sizeof(student));
    if(l->head==NULL){
        exit(-1);//内存不足
    }
    l->list_length=0;
    l->list_size=MAX_SIZE;
}
void list_destroy(list *l){//销毁linear_list
    free(l->head);
    l->head=NULL;//指针空置
    l->list_length=0;
    l->list_size=0;
    return;
}
int get_listlength(list *l){//获取linear_list的长度
    return l->list_length;
}
void list_insert(list *l,int posi,const student k){//前插
    if(posi<1||posi>l->list_length+1){
        cout<<"out_of_length"<<endl;
        return;//数组越界
    }
    if(l->list_length+1>=l->list_size){
        stu new_list=NULL;
        new_list=(stu)realloc(l->head,(MAX_SIZE+l->list_size)*sizeof(student));//扩容
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
int list_find_with_num(list *l,int num){//根据学号返回其在表中的位置
    int posi=1;
    stu temp=l->head+1;
    while(posi<=get_listlength(l)){
        if(temp->number==num){
            return posi;
        }
        ++posi;
        ++temp;
    }
    return -1;//当无法匹配时,返回-1
}
void item_delete(list *l,int num){//在linear_list中删除某个元素
    int posi=list_find_with_num(l,num);
    if(posi==-1){
        cout<<"ERROR";
        return;
    }
    for(int i=posi;i<l->list_length;++i){
        l->head[i]=l->head[i+1];
    }
    l->list_length--;
    return;
}
void item_find(list *l,char ch,int mark,bool (*com)(int,int)){//依据条件进行筛选
    stu s=&l->head[1];
    int i=1;
    if(ch=='a'){
        while(i<=l->list_length){
            if(!(*com)(s->a_mark,mark)){
                ++s;
                ++i;
            }
            else{
                cout<<s->name<<' ';
                ++s;
                ++i;
            }
        }
    }
    else if(ch=='b'){
        while(i<=l->list_length){
            if(!(*com)(s->b_mark,mark)){
                ++s;
                ++i;
            }
            else{
                cout<<s->name<<' ';
                ++s;
                ++i;
            }
        }
    }
    else if(ch=='c'){
        while(i<=l->list_length){
            if(!(*com)(s->c_mark,mark)){
                ++s;
                ++i;
            }
            else{
                cout<<s->name<<' ';
                ++s;
                ++i;
            }
        }
    }
    else{
        cout<<"???????????";
    }
    cout<<endl;
    return;
}
void print_list(list *l){
    cout<<endl<<"成绩表"<<endl;
    cout<<left<<setw(8)<<"name";
    cout<<left<<setw(8)<<"number";
    cout<<left<<setw(8)<<"数学";
    cout<<left<<setw(8)<<"英语";
    cout<<left<<setw(8)<<"数据结构"<<endl<<endl;
    int avg_a=0,avg_b=0,avg_c=0;
    for(int i=1;i<=l->list_length;++i){
        avg_a+=l->head[i].a_mark;
        avg_b+=l->head[i].b_mark;
        avg_c+=l->head[i].c_mark;
        cout<<left<<setw(8)<<l->head[i].name;
        cout<<left<<setw(8)<<l->head[i].number;
        cout<<left<<setw(8)<<l->head[i].a_mark;
        cout<<left<<setw(8)<<l->head[i].b_mark;
        cout<<left<<setw(8)<<l->head[i].c_mark<<endl;
    }
    cout<<left<<setw(12)<<"数学平均分: "<<avg_a/l->list_length;
    cout<<left<<setw(12)<<" 英语平均分: "<<avg_b/l->list_length;
    cout<<left<<setw(12)<<" 数据结构平均分: "<<avg_c/l->list_length<<endl<<endl;
    return;
}
void print_item(list *l,int num){
    int posi=list_find_with_num(l,num);
    if(posi==-1){
        cout<<"ERROR"<<endl;
        return;
    }
    cout<<left<<setw(8)<<l->head[posi].number;
    cout<<left<<setw(8)<<l->head[posi].name;
    cout<<left<<setw(8)<<l->head[posi].a_mark;
    cout<<left<<setw(8)<<l->head[posi].b_mark;
    cout<<left<<setw(8)<<l->head[posi].c_mark<<endl;
    return;
}
void menu(){
    cout<<"0: 退出"<<endl;
    cout<<"1: 录入成绩(输入顺序为学号 名称 数学的成绩 英语的成绩 数据结构的成绩)"<<endl;
    cout<<"2: 打印成绩表"<<endl;
    cout<<"3: 打印某个学生的成绩"<<endl;
    cout<<"4: 在某个位置插入某个学生的成绩(输入顺序同1)"<<endl;
    cout<<"5: 根据学号对学生成绩进行删除"<<endl;
    cout<<"6: 依据某些条件对学生进行筛选"<<endl;
    cout<<"7: 对学生成绩进行降序排列"<<endl;
    cout<<"8: 打印菜单"<<endl;
    return;
}
int main(){
    list a;
    list_create(&a);
    menu();
    cout<<"选项: ";
    int choice;
    int num;
    int posi;
    student temp;
    char ch;
    cin>>choice;
    while(choice){
        switch (choice)
        {
        case 1:
            cout<<"输入学生个数: ";
            cin>>num;
            for(int i=1;i<=num;++i){
                cin>>temp.number>>temp.name>>temp.a_mark>>temp.b_mark>>temp.c_mark;
                list_insert(&a,i,temp);
            }
            break;
        case 2:
            print_list(&a);
            break;
        case 3:
            cout<<"学生的学号: ";
            cin>>num;
            print_item(&a,num);
            break;
        case 4:
            cout<<"位置: ";
            cin>>posi;
            cin>>temp.number>>temp.name>>temp.a_mark>>temp.b_mark>>temp.c_mark;
            list_insert(&a,posi,temp);
            break;
        case 5:
            cout<<"学生的学号: ";
            cin>>num;
            item_delete(&a,num);
            break;
        case 6:
            cout<<"例如,筛选出数据结构成绩高于xx分的学生"<<endl;
            cout<<"a为数学,b为英语,c为数据结构: ";
            cin>>ch;
            cout<<"基准分数: ";
            cin>>num;
            cout<<"1: 筛选出高于 ";
            cout<<"2: 筛选出低于 ";
            cout<<"3: 筛选出等于 ";
            cout<<"选择: ";
            cin>>posi;
            if(posi==1){
                item_find(&a,ch,num,_compare_greater);
            }
            if(posi==2){
                item_find(&a,ch,num,_compare_smaller);
            }
            if(posi==3){
                item_find(&a,ch,num,_compare_equal);
            }
            break;
        case 7:
            cout<<"以某个科目作为基准,a为数学,b为英语,c为数据结构: ";
            cin>>ch;
            if(ch=='a'){
                sort(a.head+1,a.head+1+a.list_length,pd_a);
            }
            if(ch=='b'){
                sort(a.head+1,a.head+1+a.list_length,pd_b);
            }
            if(ch=='c'){
                sort(a.head+1,a.head+1+a.list_length,pd_c);
            }
            break;
        case 8:
            menu();
            break;
        default:
            break;
        }
        cout<<"选项: ";
        cin>>choice;
    }
    list_destroy(&a);
    return 0;
}
```
