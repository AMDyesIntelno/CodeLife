#include<iostream>
#include<cstring>
#define MAX_LEN 20000
using namespace std;
void read(int *num){
    char temp[MAX_LEN+1];
    memset(temp,'0',sizeof(temp));
    cin>>temp;
    int len=strlen(temp);
    for(int i=0;i<len;++i){
        num[MAX_LEN-i-1]=temp[len-i-1]-'0';
    }
    return;
}
void print(int *num){
    int i;
    for(i=0;i<MAX_LEN-1;++i){
        if(num[i]){
            break;
        }
    }
    for(;i<MAX_LEN;++i){
        cout<<num[i];
    }
    return;
}
void add(int *a,int *b,int *c){
    int sum=0;
    for(int i=MAX_LEN-1;i>=0;--i){
        sum+=a[i]+b[i];
        c[i]=sum%10;
        sum/=10;
    }
    return;
}
int main(){
    int a[MAX_LEN]={0};
    int b[MAX_LEN]={0};
    int c[MAX_LEN]={0};
    read(a);
    read(b);
    add(a,b,c);
    print(c);
    return 0;
}
