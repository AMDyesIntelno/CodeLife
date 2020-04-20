```c++
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
    freopen("Huffman/in.txt","r",stdin);
    char temp;
    temp=getchar();
    while(temp!=EOF){
        a+=temp;
        temp=getchar();
    }
    return;
}
void get_weight(string a,int *weight){//统计每个字符的权重
    for(int i=0;i<a.size();++i){
        if(a[i]>='a'&&a[i]<='z'){
            weight[a[i]-'a']++;
        }
        if(a[i]==' '){//单独判断空格以及换行
            weight[26]++;
        }
        if(a[i]=='\n'){
            weight[27]++;
        }
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
void Create_Huffman_Tree(H_Tree &HT,int *weight){//构建哈夫曼树
    int m=2*28-1;
    HT=new Huffman[m+1];//分配空间要+1
    for(int i=1;i<=26;++i){//为哈夫曼树的叶子结点写入权重和字符
        HT[i].ch=(char)('a'+i-1);
        HT[i].weight=weight[i-1];
    }
    HT[27].ch=' ';//为哈夫曼树的叶子结点写入权重和字符
    HT[27].weight=weight[26];
    HT[28].ch='\n';//为哈夫曼树的叶子结点写入权重和字符
    HT[28].weight=weight[27];
    for(int i=29;i<=m;++i){//正式开始构建哈夫曼树,叶子结点的左孩子和右孩子结点置为0,便于译码
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
void Create_Huffman_Code(H_Tree HT,H_Code &HC){//构建哈夫曼编码表,逆序编码
    HC=new char*[29];
    char *temp;
    temp=new char[28];
    temp[27]=0;
    for(int i=1;i<=28;++i){
        int start=27;
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
        HC[i]=new char[28-start];
        strcpy(HC[i],&temp[start]);
    }
    delete []temp;
    return;
}
void Encode(string a,H_Code HC){//将文本转换为哈夫曼编码,并存入encode.data中
    ofstream fp("Huffman/encode.data");
    for(int i=0;i<a.size();++i){
        if(a[i]>='a'&&a[i]<='z'){
            fp<<HC[a[i]-'a'+1];
        }
        if(a[i]==' '){
            fp<<HC[27];
        }
        if(a[i]=='\n'){
            fp<<HC[28];
        }
    }
    fp.close();
    return;
}
void Decode(H_Tree HT){//将哈夫曼编码转换为文本,并存入decode.data中
    freopen("Huffman/encode.data","r",stdin);
    ofstream fp("Huffman/decode.data");
    string a;
    char temp;
    temp=getchar();
    while(temp!=EOF){
        a+=temp;
        temp=getchar();
    }
    int root=2*28-1;
    for(int i=0;i<a.size();++i){
        if(a[i]=='0'){//遇到0向左子树搜索
            root=HT[root].left;
        }
        else if(a[i]=='1'){//遇到1向右子树搜索
            root=HT[root].right;
        }
        if(HT[root].right==0&&HT[root].left==0){//左右子树均为0,说明这是叶子结点
            fp<<HT[root].ch;
            root=2*28-1;//重置根结点
        }
    }
    fp.close();
    return;
}
int main(){
    string a;
    int weight[28]={0};
    H_Tree HT=NULL;
    H_Code HC=NULL;
    read_file(a);
    get_weight(a,weight);
    Create_Huffman_Tree(HT,weight);
    Create_Huffman_Code(HT,HC);
    cout<<"当前读入文本: "<<endl;
    cout<<a<<endl;
    cout<<"当前各个字符权重: "<<endl;
    for(int i=1;i<=26;++i){
        cout<<left<<setw(2)<<HT[i].ch<<left<<setw(3)<<HT[i].weight;
        if(i%4==0){
            cout<<endl;
        }
    }
    cout<<left<<setw(2)<<'_'<<left<<setw(3)<<HT[27].weight;
    cout<<left<<setw(2)<<'\\'<<left<<setw(3)<<HT[28].weight<<endl;
    cout<<"当前各个字符的哈夫曼编码: "<<endl;
    for(int i=1;i<=26;++i){
        cout<<left<<setw(2)<<HT[i].ch<<left<<setw(8)<<HC[i];
        if(i%4==0){
            cout<<endl;
        }
    }
    cout<<left<<setw(2)<<'_'<<left<<setw(8)<<HC[27];
    cout<<left<<setw(2)<<'\\'<<left<<setw(8)<<HC[28]<<endl;
    Encode(a,HC);
    Decode(HT);
    return 0;
}
```

```
当前读入文本: 
the quick brown fox jumps over the lazy dog
a quick movement of the enemy will jeopardize six gunboats
all questions asked by five watch experts amazed the judge
big july earthquakes confound zany experimental vow
当前各个字符权重: 
a 13 b 4  c 4  d 6  
e 23 f 4  g 4  h 6  
i 9  j 4  k 4  l 7  
m 6  n 9  o 12 p 4  
q 4  r 6  s 8  t 11 
u 9  v 4  w 4  x 4  
y 5  z 4  _ 32 \ 3  
当前各个字符的哈夫曼编码: 
a 1000    b 100111  c 110010  d 01100   
e 001     f 110011  g 110100  h 01101   
i 11110   j 110101  k 110110  l 10010   
m 01110   n 11111   o 0101    p 110111  
q 111000  r 01111   s 11000   t 0100    
u 0000    v 111001  w 111010  x 111011  
y 00011   z 00010   _ 101     \ 100110
```