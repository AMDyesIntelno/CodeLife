#include<iostream>
#include<cstring>
#define MAX_LEN 20000
using namespace std;
void read(int *num){//读入，将字符转换为数字并调整位置
    char temp[MAX_LEN+1];
    memset(temp,'0',sizeof(temp));
    cin>>temp;
    int len=strlen(temp);
    for(int i=0;i<len;++i){
        num[MAX_LEN-i-1]=temp[len-i-1]-'0';//位置调整
    }
    return;
}
void print(int *num){//找到第一个非零的数，特殊情况为结果为0，所以最后一位直接输出，不进行判断
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
void add(int *a,int *b,int *c){//竖式加法模拟，满十进一
    int sum=0;
    for(int i=MAX_LEN-1;i>=0;--i){
        sum+=a[i]+b[i];
        c[i]=sum%10;
        sum/=10;
    }
    return;
}
inline bool is_able(int *a,int *b){//判断能否进行相减
    for(int i=0;i<MAX_LEN;++i){
        if((a[i]||b[i])&&a[i]!=b[i]){//其中一个不为零且两者不相等
            if(a[i]-b[i]>0){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    return 1;//两者完全相等
}
void sub(int *a,int *b,int *c){//竖式减法模拟
    if(is_able(a,b)==false){//无法直接相减时对换a，b
        swap(a,b);
        cout<<'-';
    }
    int sum=0;
    for(int i=MAX_LEN-1;i>=0;--i){
        sum+=a[i]-b[i];
        if(sum<0){//借位
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
void mul(int *a,int *b,int *c){//竖式乘法模拟
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
void div(int *a,int *b,int *c,int *d){//竖式除法模拟并生成余数
    int la,lb;
    for(la=0;la<MAX_LEN;++la){//确定位数
        if(a[la]!=0){
            break;
        }
    }
    for(lb=0;lb<MAX_LEN;++lb){//确定位数
        if(b[lb]!=0){
            break;
        }
    }
    if(lb==MAX_LEN){//被除数不能为0
        cout<<"ERROR";
        exit(0);
    }
    la=MAX_LEN-la;//确定位数
    lb=MAX_LEN-lb;//确定位数
    if(is_able(a,b)){//除法本质是多次减法
        for(int i=MAX_LEN-lb;i<MAX_LEN;++i){//b向前移位并补零
            b[i-la+lb]=b[i];
        }
        for(int i=MAX_LEN-la+lb;i<MAX_LEN;++i){
            b[i]=0;
        }
    }
    for(int i=la-lb;i>=0;--i){//最多需处理的位数
        while(is_able(a,b)){
            int sum=0;
            for(int j=MAX_LEN-1;j>=0;--j){
                sum+=a[j]-b[j];
                if(sum<0){
                    d[j]+=sum+10;
                    a[j-1]--;
                }
                else{
                    d[j]=sum;
                }
                sum=0;
            }
            for(int j=0;j<MAX_LEN;++j){
                a[j]=d[j];//余数成为除数
            }
            fill(d,d+MAX_LEN,0);
            c[MAX_LEN-i-1]++;//商的对应位置+1
        }
        for(int j=MAX_LEN-1;j>=MAX_LEN-la;--j){
            b[j]=b[j-1];
        }
    }
    return;
}
int main(){
    int a[MAX_LEN]={0};
    int b[MAX_LEN]={0};
    int c[MAX_LEN]={0};
    int d[MAX_LEN]={0};
    cout<<"Sample: "<<endl<<"a"<<endl<<"<op>"<<endl<<"b"<<endl;
    read(a);
    char temp;
    cin>>temp;
    read(b);
    switch (temp)
    {
    case '+':
        add(a,b,c);
        print(c);
        break;
    case '-':
        sub(a,b,c);
        print(c);
        break;
    case '*':
        mul(a,b,c);
        print(c);
        break;
    case '/':
        div(a,b,c,d);
        cout<<"商: ";
        print(c);
        cout<<endl;
        cout<<"余: ";
        print(a);
        break;
    default:
        cout<<">-<";
        break;
    }
    return 0;
}
