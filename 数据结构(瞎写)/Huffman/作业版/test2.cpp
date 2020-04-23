#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ifstream fp("wdnmdadsf");
    int a,n;
    char b;
    if(!fp){
        ofstream fp("wdnmdadsf");
        fp<<3<<endl;
        fp<<'a'<<' '<<987<<endl;
        fp<<'b'<<' '<<9874<<endl;
        fp<<'c'<<' '<<984984;
    }
    else{
        fp>>n;
        cout<<n<<endl;
        for(int i=1;i<=n;++i){
            fp>>b;
            fp>>a;
            cout<<b<<' '<<a<<endl;
        }
    }
    fp.close();
    return 0;
}