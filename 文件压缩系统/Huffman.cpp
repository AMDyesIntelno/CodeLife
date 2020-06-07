#ifndef Huffman_cpp
#define Huffman_cpp

#include "Huffman.h"
void get_weight(string text,int *weight,string &plaintext){/*统计每个字符的权重*/
    int temp[16]={0};
    for(int i=0;i<text.size();++i){
        if(text[i]>='0'&&text[i]<='9'){
            weight[text[i]-'0']++;
            temp[text[i]-'0']++;
        }
        if(text[i]>='A'&&text[i]<='F'){
            weight[text[i]-'A'+10]++;
            temp[text[i]-'A'+10]++;
        }
    }
    char hex[32];
    for(int i=0;i<16;++i){/*将字符权重写入明文*/
        for(int j=31;j>=0;--j){
            hex[j]='0'+temp[i]%2;
            temp[i]>>=1;
        }
        for(int j=0;j<32;++j){
            plaintext+=hex[j];
        }
        memset(hex,0,32);
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
    int m=2*16-1;
    HT=new Huffman[m+1];//分配空间要+1
    for(int i=1;i<=16;++i){//为哈夫曼树的叶子结点写入权重和字符
        if(i<=10){
            HT[i].ch=(char)('0'+i-1);
            HT[i].weight=weight[i-1];
        }
        else{
            HT[i].ch=(char)('A'+i-11);
            HT[i].weight=weight[i-1];
        }
    }
    for(int i=17;i<=m;++i){//正式开始构建哈夫曼树,叶子结点的左孩子和右孩子结点置为0,便于译码
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
    HC=new char*[17];
    char *temp;
    temp=new char[16];
    temp[15]=0;
    for(int i=1;i<=16;++i){
        int start=15;
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
        HC[i]=new char[16-start];
        strcpy(HC[i],&temp[start]);
    }
    delete []temp;
    return;
}
void encode(string &plaintext,string text,H_Code HC){//编码
    for(int i=0;i<text.size();++i){
        if(text[i]>='0'&&text[i]<='9'){
            plaintext+=HC[text[i]-'0'+1];
        }
        if(text[i]>='A'&&text[i]<='F'){
            plaintext+=HC[text[i]-'A'+11];
        }
    }
    for(int i=0;i<plaintext.size()%8;++i){//保证2进制能够顺利转换为16进制,对哈夫曼编码后的文件内容进行补零
        plaintext+='0';
    }
    return;
}
void decode(string &plaintext,H_Tree HT,int sum){//解码
    int root=2*16-1;
    string temp;
    for(int i=0;i<plaintext.size();++i){
        if(sum<=0){//权重部分记录的sum
            break;
        }
        if(plaintext[i]=='0'){//遇到0向左子树搜索
            root=HT[root].left;
        }
        else if(plaintext[i]=='1'){//遇到1向右子树搜索
            root=HT[root].right;
        }
        if(HT[root].right==0&&HT[root].left==0){//左右子树均为0,说明这是叶子结点
            temp+=HT[root].ch;
            root=2*16-1;//重置根结点
            --sum;
        }
    }
    plaintext.erase();
    plaintext=temp;
    return;
}
int recover(int *weight,string &plaintext){/*文件解密后(二进制形式),读取字符权重*/
    fill(weight,weight+16,0);
    int sum=0;//sum用于在进行解码时剔除在保存字符权重时额外添加的0
    string temp;
    for(int i=0,j=0;i<512;++i){
        if(i&&i%32==0){
            weight[j]=stoi(temp,nullptr,2);
            sum+=weight[j++];
            temp.erase();
        }
        temp+=plaintext[i];
    }
    weight[15]=stoi(temp,nullptr,2);//最后一个权重在循环中没有读取
    sum+=weight[15];
    plaintext.erase(0,512);//清除明文中的权重记录
    return sum;
}

#endif