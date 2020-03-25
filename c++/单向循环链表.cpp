/*单向循环链表*/
#include<iostream>
#include<string>
using namespace std;
typedef struct node{
	string name;int data;/*数据域*/
	struct node *next;/*指针域*/
}NODE;
/*增删查改*/
NODE *circlelist_create(NODE *head){/*创建链表*/
	if(head!=NULL){
		cout<<"--------"<<endl;
		cout<<"已存在链表,返回当前节点"<<endl;
		cout<<"--------"<<endl;
		return head;
	}
	NODE *prev=NULL;
	NODE *now=NULL;
	string temp;
	cout<<"input name or quit: ";
	cin>>temp;
	while(temp!="quit"){
		now=new NODE;
		if(head==NULL){
			head=now;
		}
		else{
			prev->next=now;
		}
		now->name=temp;
		cout<<"input data: ";
		cin>>now->data;
		now->next=head;
		prev=now;
		cout<<"input name or quit: ";
		cin>>temp;
	}
	return head;
}
int circlelist_length(NODE *p){/*查询链表长度*/
	if(p==NULL){
		return 0;
	}
	int sum=1;
	NODE *now=p->next;
	while(now!=p){
		sum++;
		now=now->next;
	}
	return sum;
}
NODE *circlelist_find(NODE *p,int kth){/*在链表中查找第kth个元素，返回该元素节点的指针*/
	if(kth<=0){
		return NULL;
	}
	NODE *temp=p;
	while(--kth){
		temp=temp->next;
	}
	return temp;
}
NODE *circlelist_delete(NODE *p,int kth){/*删除链表中的第kth个元素*/
	NODE *now=circlelist_find(p,kth);
	if(now==NULL){
		cout<<"删除失败,返回当前节点"<<endl;
	}
	else{
		NODE *prev=circlelist_find(p,kth-1);
		prev->next=now->next;
		delete now;
	}
	return p;
}
NODE *circlelist_front_insert(NODE *p,int kth){/*将某个元素插入到链表的第kth个元素之前*/
	NODE *now=circlelist_find(p,kth);
	if(now==NULL){
		cout<<"插入失败,返回当前节点"<<endl;
	}
	else{
		NODE *prev=circlelist_find(p,kth-1);
		NODE *new_point=new NODE;
		cout<<"input name: ";
		cin>>new_point->name;
		cout<<"input data: ";
		cin>>new_point->data;
		prev->next=new_point;
		new_point->next=now;
	}
	return p;
}
NODE *circlelist_after_insert(NODE *p,int kth){/*将某个元素插入到链表的第kth个元素之后*/
	NODE *now=circlelist_find(p,kth);
	if(now==NULL){
		cout<<"插入失败,返回当前节点"<<endl;
	}
	else{
		NODE *new_point=new NODE;
		cout<<"input name: ";
		cin>>new_point->name;
		cout<<"input data: ";
		cin>>new_point->data;
		new_point->next=now->next;
		now->next=new_point;
	}
	return p;
}
NODE *circlelist_reverse(NODE *p){/*链表反转*/
	NODE *head=NULL;
	NODE *now=NULL;
	NODE *prev=NULL;
	for(int i=circlelist_length(p);i>0;--i){
		now=new NODE;
		*now=*circlelist_find(p,i);
		if(head==NULL){
			head=now;
		}
		else{
			prev->next=now;
		}
		prev=now;
		now->next=head;
	}
	return head;
}
void circlelist_change(NODE *p,int kth){/*改变某个元素的数据域*/
	NODE *now=circlelist_find(p,kth);
	if(now==NULL){
		cout<<"不存在该元素"<<endl;
	}
	else{
		cout<<"input name: ";
		cin>>now->name;
		cout<<"input data: ";
		cin>>now->data;
	}
	return;
}
void print_circlelist(NODE *p){/*输出链表*/
	if(p==NULL){
		cout<<"--------"<<endl;
		cout<<"NULL!!!"<<endl;
		cout<<"--------"<<endl;
	}
	else{
		cout<<"--------"<<endl;
		NODE *now=p;
		while(now->next!=p){
			cout<<"name: "<<now->name<<" data: "<<now->data<<endl;
			now=now->next;
		}
		cout<<"name: "<<now->name<<" data: "<<now->data<<endl;
		cout<<"--------"<<endl;
	}
	return;
}
NODE *circlelist_destory(NODE *p){/*内存释放*/
	NODE *q;
	while(p!=NULL&&p->next!=p){
		q=p->next->next;
		delete p->next;
		p->next=q;
	}
	if(p!=NULL){
		delete p;
	}
	return NULL;
}
int main(){
	NODE *head=NULL;
	NODE *reverse=NULL;
	int num,kth;
	cout<<"0:quit"<<endl;
	cout<<"1:circlelist_create"<<endl;
	cout<<"2:circlelist_length"<<endl;
	cout<<"3:circlelist_delete"<<endl;
	cout<<"4:circlelist_front_insert"<<endl;
	cout<<"5:circlelist_after_insert"<<endl;
	cout<<"6:circlelist_change"<<endl;
	cout<<"7:circlelist_reverse"<<endl;
	cout<<"8:print_circlelist"<<endl;
	cout<<"9:circlelist_destory"<<endl;
	cout<<"choice: ";
	cin>>num;
	while(num){
		switch (num){
			case 1:
				head=circlelist_create(head);
				break;
			case 2:
				cout<<"--------"<<endl;
				cout<<"length: "<<circlelist_length(head)<<endl;
				cout<<"--------"<<endl;
				break;
			case 3:
				cout<<"the number to delete: ";
				cin>>kth;
				head=circlelist_delete(head,kth);
				break;
			case 4:
				cout<<"the number to insert: ";
				cin>>kth;
				head=circlelist_front_insert(head,kth);
				break;
			case 5:
				cout<<"the number to insert: ";
				cin>>kth;
				head=circlelist_after_insert(head,kth);
				break;
			case 6:
				cout<<"the number to change: ";
				cin>>kth;
				circlelist_change(head,kth);
				break;
			case 7:
				reverse=circlelist_reverse(head);
				print_circlelist(reverse);
				reverse=circlelist_destory(reverse);
				break;
			case 8:
				print_circlelist(head);
				break;
			case 9:
				head=circlelist_destory(head);
				break;
			default:
			break;
		}
		cout<<"0:quit"<<endl;
		cout<<"1:circlelist_create"<<endl;
		cout<<"2:circlelist_length"<<endl;
		cout<<"3:circlelist_delete"<<endl;
		cout<<"4:circlelist_front_insert"<<endl;
		cout<<"5:circlelist_after_insert"<<endl;
		cout<<"6:circlelist_change"<<endl;
		cout<<"7:circlelist_reverse"<<endl;
		cout<<"8:print_circlelist"<<endl;
		cout<<"9:circlelist_destory"<<endl;
		cout<<"choice: ";
		cin>>num;
	}
	head=circlelist_destory(head);
	return 0;
}
