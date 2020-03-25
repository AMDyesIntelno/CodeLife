```c++
void queue_insert(queueptr &rear,int item){
  queueptr temp=new queue;
  temp->data=item;
  temp->next=rear->next;
  rear->next=temp;
  rear=temp;
  return;
}
void queue_pop(queueptr &rear,int &item){
  if(rear->next==rear){
    item=rear->data;
    delete rear;
    rear=NULL;
    return;
  }
  queueptr temp=rear->next;
  rear->next=temp->next;
  item=temp->data;
  delete temp;
  return;
}
```
