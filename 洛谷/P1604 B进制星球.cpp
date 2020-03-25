#include<iostream>
#include<cstring>
#define MAX_LEN 2000
using namespace std;
void read(int *n){
    char temp[MAX_LEN+1];
    memset(temp,'0',sizeof(temp));
    cin>>temp;
    int len=strlen(temp);
    for(int i=0;i<len;++i){
        if(temp[len-i-1]>='A'&&temp[len-i-1]<='Z'){
            n[MAX_LEN-i-1]=temp[len-i-1]-'A'+10;
        }
        else{
            n[MAX_LEN-i-1]=temp[len-i-1]-'0';
        }
    }
    return;
}
void add(int *a,int *b,int *c,int base){
    int sum=0;
    for(int i=MAX_LEN-1;i>=0;--i){
        sum+=a[i]+b[i];
        c[i]=sum%base;
        sum/=base;
    }
    return;
}
int main(){
    int base;
    cin>>base;
    int a[MAX_LEN]={0};
    int b[MAX_LEN]={0};
    int c[MAX_LEN]={0};
    read(a);
    read(b);
    add(a,b,c,base);
    int i;
    for(i=0;i<MAX_LEN;++i){
        if(c[i]){
            break;
        }
    }
    for(;i<MAX_LEN;++i){
        if(c[i]>=10){
            cout<<(char)(c[i]-10+'A');
        }
        else{
            cout<<c[i];
        }
    }
    return 0;
}
