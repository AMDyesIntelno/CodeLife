/*decode.cpp*/
#include "huffman.h"
int main(){
    int n;
    string a;
    int *weight=NULL;
    char *ch=NULL;
    H_Tree HT=NULL;
    H_Code HC=NULL;
    Create_Huffman_Tree(HT,weight,ch,n);
    Create_Huffman_Code(HT,HC,n);
    Decode(HT,n);
    freopen("TextFile.txt","r",stdin);
    char temp=getchar();
    while(temp!=EOF){
        a+=temp;
        temp=getchar();
    }
    cout<<"解码得到的文本: "<<endl;
    cout<<a<<endl;
    delete []weight;
    weight=NULL;
    delete []ch;
    ch=NULL;
    delete []HT;
    HT=NULL;
    delete []HC;
    HC=NULL;
    return 0;
}