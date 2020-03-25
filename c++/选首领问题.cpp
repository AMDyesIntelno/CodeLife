/*别名:约瑟夫环*/
#include<iostream>
using namespace std;
typedef struct node
{
    int rank;/*记录编号*/
    struct node *next;
    
}NODE;
int main(){
        NODE *head=NULL;
        NODE *prev=NULL;
        NODE *now=NULL;
        int people;
        cout<<"参与选首领游戏的人数: ";
        cin>>people;
        int num=1;
        while(num<=people){
                now=new NODE;
                if(head==NULL){
                        head=now;
                }
                else{
                        prev->next=now;
                }
                now->rank=num;
                ++num;
                now->next=head;
                prev=now;
        }
        int n;
        cout<<"从编号n的人开始报数: ";
        cin>>n;
        int m;
        cout<<"数到m的人出列: ";
        cin>>m;
        if(!people&&!m){
                return 0;
        }
        now=head;
        for(int i=1;i<n;++i){
                now=now->next;
        }
        while(now->next!=now){/*确保最后只剩下一个人*/
                for(int i=1;i<m;++i){
                        prev=now;
                        now=now->next;
                }
                prev->next=now->next;
                cout<<"编号为"<<now->rank<<"的人出列"<<endl;
                delete now;
                now=prev->next;
        }
        cout<<"编号为"<<now->rank<<"的人胜利"<<endl;
        delete now;
        return 0;
}
