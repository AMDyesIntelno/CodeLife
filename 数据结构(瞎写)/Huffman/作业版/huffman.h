/*huffman.h*/
#ifndef huffman
#define huffman
#include<iostream>
#include<fstream>//文件操作
#include<iomanip>
#include<string>
#include<cstring>
using namespace std;
typedef struct Huffman{
    char ch=0;
    int weight=0;
    int root=0;
    int left=0;
    int right=0;
}*H_Tree;
typedef char **H_Code;
void read_file(string &a){//读取待编码的文件,假定仅包含小写字母,空格和换行符
    //此处的文件为全字母句,不是全字母句也可以,但是会造成编码冗长
    freopen("in.txt","r",stdin);
    char temp;
    temp=getchar();
    while(temp!=EOF){
        a+=temp;
        temp=getchar();
    }
    return;
}
void min_2(H_Tree HT,int _size,int &posi1,int &posi2){//获取权重最小的两个结点
    //先获取两个根结点为零的结点,然后进行权重比较
    int i=1;
    for(i;i<=_size;++i){
        if(HT[i].root==0){
            posi1=i;
            ++i;
            break;
        }
    }
    for(i;i<=_size;++i){
        if(HT[i].root==0){
            posi2=i;
            ++i;
            break;
        }
    }
    if(HT[posi1].weight>=HT[posi2].weight){//使posi1的权重小于posi2的权重
        swap(posi1,posi2);
    }
    for(i;i<=_size;++i){
        if(HT[i].root==0){
            if(HT[i].weight<HT[posi2].weight){
                if(HT[i].weight<HT[posi1].weight){
                    posi2=posi1;
                    posi1=i;
                }
                else{
                    posi2=i;
                }
            }
        }
    }
    return;
}
void Create_Huffman_Tree(H_Tree &HT,int* &weight,char* &ch,int &n){//构建哈夫曼树
    ifstream fp("hfmtree.txt");
    if(!fp){
        ofstream fp("hfmtree.txt");
        cout<<"输入字符集大小: ";
        cin>>n;
        fp<<n<<endl;
        weight=new int[n+1];
        ch=new char[n+1];
        char temp;
        for(int i=1;i<=n;++i){//仅读入小写字符,并以_代表空格,\代表换行符
            cin>>temp;
            cin>>weight[i];
            fp<<temp<<' '<<weight[i]<<endl;
            if(temp<='z'&&temp>='a'){
                ch[i]=temp;
            }
            else if(temp=='_'){
                ch[i]=' ';
            }
            else if(temp=='\\'){
                ch[i]='\n';
            }
        }
    }
    else{
        fp>>n;
        weight=new int[n+1];
        ch=new char[n+1];
        char temp;
        for(int i=1;i<=n;++i){
            fp>>temp;
            fp>>weight[i];
            if(temp<='z'&&temp>='a'){
                ch[i]=temp;
            }
            else if(temp=='_'){
                ch[i]=' ';
            }
            else if(temp=='\\'){
                ch[i]='\n';
            }
        }
    }
    fp.close();
    int m=2*n-1;
    HT=new Huffman[m+1];
    for(int i=1;i<=n;++i){
        HT[i].ch=ch[i];
        HT[i].weight=weight[i];
    }
    for(int i=n+1;i<=m;++i){
        int posi1,posi2;
        min_2(HT,i-1,posi1,posi2);
        HT[posi1].root=i;
        HT[posi2].root=i;
        HT[i].left=posi1;
        HT[i].right=posi2;
        HT[i].weight=HT[posi1].weight+HT[posi2].weight;//叠加权重
    }
    return;
}
void Create_Huffman_Code(H_Tree HT,H_Code &HC,int n){//构建哈夫曼编码表,逆序编码
    HC=new char*[n+1];
    char *temp;
    temp=new char[n];
    temp[n-1]=0;
    for(int i=1;i<=n;++i){
        int start=n-1;
        for(int j=i,root=HT[i].root;root!=0;j=root,root=HT[root].root){
            //从叶子结点开始,向前回溯,若该结点是前一个结点的左孩子,则记为0,否则,记为1
            //当回溯到哈夫曼树的根结点时,回溯结束,将当前所得字符串复制到哈夫曼编码表中,开始新的一轮编码
            if(HT[root].left==j){//约定左分支为0,右分支为1,注意此时为逆序编码
                temp[--start]='0';
            }
            else{
                temp[--start]='1';
            }
        }
        HC[i]=new char[n-start];
        strcpy(HC[i],&temp[start]);
    }
    delete []temp;
    return;
}
void Encode(string a,H_Code HC,int n,char *ch){//将文本转换为哈夫曼编码,并存入encode.data中
    ofstream fp("CodeFile.txt");
    for(int i=0;i<a.size();++i){
        for(int j=1;j<=n;++j){
            if(a[i]==ch[j]){
                fp<<HC[j];
                break;
            }
        }
    }
    fp.close();
    return;
}
void Decode(H_Tree HT,int n){//将哈夫曼编码转换为文本,并存入decode.data中
    freopen("CodeFile.txt","r",stdin);//直接将整个文件作为string读入
    ofstream fp("TextFile.txt");
    string a;
    char temp;
    temp=getchar();
    while(temp!=EOF){
        a+=temp;
        temp=getchar();
    }
    int root=2*n-1;
    for(int i=0;i<a.size();++i){
        if(a[i]=='0'){//遇到0向左子树搜索
            root=HT[root].left;
        }
        else if(a[i]=='1'){//遇到1向右子树搜索
            root=HT[root].right;
        }
        if(HT[root].right==0&&HT[root].left==0){//左右子树均为0,说明这是叶子结点
            fp<<HT[root].ch;
            root=2*n-1;//重置根结点
        }
    }
    fp.close();
    return;
}
#endif