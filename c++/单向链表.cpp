/*单向链表*/
#include<iostream>
#include<string>
using namespace std;
typedef struct node{
	string name;int data;/*数据域*/
	struct node *next;/*指针域*/
}NODE;
/*增删查改*/
NODE *list_create(NODE *head){/*创建链表*/
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
		now->next=NULL;
		prev=now;
		cout<<"input name or quit: ";
		cin>>temp;
	}
	return head;
}
int list_length(NODE *p){/*查询链表长度*/
	int sum=0;
	while(p!=NULL){
		++sum;
		p=p->next;
	}
	return sum;
}
NODE *list_find(NODE *p,int kth){/*在链表中查找第kth个元素，返回该元素节点的指针*/
	if(kth<=0){
		return NULL;
	}
	if(kth>list_length(p)){
		return NULL;
	}
	NODE *temp=p;
	while(--kth){
		temp=temp->next;
	}
	return temp;
}
NODE *list_delete(NODE *p,int kth){/*删除链表中的第kth个元素*/
	NODE *now=list_find(p,kth);
	if(now==NULL){
		cout<<"删除失败,返回当前节点"<<endl;
		return p;
	}
	else{
		NODE *prev=list_find(p,kth-1);
		if(prev==NULL){
			prev=now;
			now=now->next;
			delete prev;
			return now;
		}
		else{
			prev->next=now->next;
			delete now;
			return p;
		}
	}
}
NODE *list_front_insert(NODE *p,int kth){/*将某个元素插入到链表的第kth个元素之前*/
	NODE *now=list_find(p,kth);
	if(now==NULL){
		cout<<"插入失败,返回当前节点"<<endl;
		return p;
	}
	else{
		NODE *prev=list_find(p,kth-1);
		NODE *new_point=new NODE;
		new_point->next=NULL;
		cout<<"input name: ";
		cin>>new_point->name;
		cout<<"input data: ";
		cin>>new_point->data;
		if(prev==NULL){
			new_point->next=now;
			return new_point;
		}
		else{
			prev->next=new_point;
			new_point->next=now;
			return p;
		}
	}
}
NODE *list_after_insert(NODE *p,int kth){/*将某个元素插入到链表的第kth个元素之后*/
	NODE *now=list_find(p,kth);
	if(now==NULL){
		cout<<"插入失败,返回当前节点"<<endl;
		return p;
	}
	else{
		NODE *after=list_find(p,kth+1);
		NODE *new_point=new NODE;
		new_point->next=NULL;
		cout<<"input name: ";
		cin>>new_point->name;
		cout<<"input data: ";
		cin>>new_point->data;
		if(after==NULL){
			now->next=new_point;
			return p;
		}
		else{
			new_point->next=now->next;
			now->next=new_point;
			return p;
		}
	}
}
void list_change(NODE *p,int kth){/*改变某个元素的数据域*/
	NODE *now=list_find(p,kth);
	if(now==NULL){
		cout<<"不存在该元素"<<endl;
		return;
	}
	cout<<"input name: ";
	cin>>now->name;
	cout<<"input data: ";
	cin>>now->data;
	return;
}
NODE *list_reverse(NODE *p){/*链表反转*/
	NODE *head=NULL;
	NODE *now=NULL;
	NODE *prev=NULL;
	for(int i=list_length(p);i>0;--i){
		now=new NODE;
		*now=*list_find(p,i);
		if(head==NULL){
			head=now;
		}
		else{
			prev->next=now;
		}
		prev=now;
		now->next=NULL;
	}
	return head;
}
void print_list(NODE *p){/*输出链表*/
	if(p==NULL){
		cout<<"--------"<<endl;
		cout<<"NULL!!!"<<endl;
		cout<<"--------"<<endl;
		return;
	}
	cout<<"--------"<<endl;
	while(p!=NULL){
		cout<<"name: "<<p->name<<" data: "<<p->data<<endl;
		p=p->next;
	}
	cout<<"--------"<<endl;
	return;
}
NODE *list_destory(NODE *p){/*内存释放*/
	NODE *q;
	while(p!=NULL){
		q=p->next;
		delete p;
		p=q;
	}
	return p;
}
int main(){
	NODE *head=NULL;
	NODE *reverse=NULL;
	int num,kth;
	cout<<"0:quit"<<endl;
	cout<<"1:list_create"<<endl;
	cout<<"2:list_length"<<endl;
	cout<<"3:list_delete"<<endl;
	cout<<"4:list_front_insert"<<endl;
	cout<<"5:list_after_insert"<<endl;
	cout<<"6:list_change"<<endl;
	cout<<"7:list_reverse"<<endl;
	cout<<"8:print_list"<<endl;
	cout<<"9:list_destory"<<endl;
	cout<<"choice: ";
	cin>>num;
	while (num){
		switch(num){
			case 1:
				head=list_create(head);
				break;
			case 2:
				cout<<"--------"<<endl;
				cout<<"length: "<<list_length(head)<<endl;
				cout<<"--------"<<endl;
				break;
			case 3:
				cout<<"the number to delete: ";
				cin>>kth;
				head=list_delete(head,kth);
				break;
			case 4:
				cout<<"the number to insert: ";
				cin>>kth;
				head=list_front_insert(head,kth);
				break;
			case 5:
				cout<<"the number to insert: ";
				cin>>kth;
				head=list_after_insert(head,kth);
				break;
			case 6:
				cout<<"the number to change: ";
				cin>>kth;
				list_change(head,kth);
				break;
			case 7:
				reverse=list_reverse(head);
				print_list(reverse);
				reverse=list_destory(reverse);
				break;
			case 8:
				print_list(head);
				break;
			case 9:
				head=list_destory(head);
				break;
			default:
				break;
		}
		cout<<"0:quit"<<endl;
		cout<<"1:list_create"<<endl;
		cout<<"2:list_length"<<endl;
		cout<<"3:list_delete"<<endl;
		cout<<"4:list_front_insert"<<endl;
		cout<<"5:list_after_insert"<<endl;
		cout<<"6:list_change"<<endl;
		cout<<"7:list_reverse"<<endl;
		cout<<"8:print_list"<<endl;
		cout<<"9:list_destory"<<endl;
		cout<<"choice: ";
		cin>>num;
	}
	head=list_destory(head);
	return 0;
}
