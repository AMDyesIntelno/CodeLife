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
void sub(int *a,int *b,int *c){
    for(int i=0;i<MAX_LEN;++i){
        if((a[i]||b[i])&&a[i]!=b[i]){
            if(a[i]-b[i]>0){
            break;
        }
        else{
            swap(a,b);
            cout<<"-";
            break;
        }
        }
    }
    int sum=0;
    for(int i=MAX_LEN-1;i>=0;--i){
        sum+=a[i]-b[i];
        if(sum<0){
            c[i]+=sum+10;
            a[i-1]--;
        }
        else{
            c[i]=sum;
        }
        sum=0;
    }
    return;
}
void mul(int *a,int *b,int *c){
    for(int i=MAX_LEN-1;i>=0;--i){
        for(int j=MAX_LEN-1;j>=i;--j){
            c[i]+=a[j]*b[i-j+MAX_LEN-1];
        }
        if(c[i]>=10){
            c[i-1]+=c[i]/10;
            c[i]%=10;
        }
    }
}
int main(){
    int a[MAX_LEN]={0};
    int b[MAX_LEN]={0};
    int c[MAX_LEN]={0};
    read(a);
    read(b);
    mul(a,b,c);
    print(c);
    return 0;
}
