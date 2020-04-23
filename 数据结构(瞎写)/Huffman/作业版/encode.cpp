/*encode.cpp*/
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
    read_file(a);
    cout<<"当前读入文本: "<<endl;
    cout<<a<<endl;
    Encode(a,HC,n,ch);
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