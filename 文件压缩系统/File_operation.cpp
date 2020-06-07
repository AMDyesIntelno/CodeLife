#ifndef File_operation_cpp
#define File_operation_cpp

#include "File_operation.h"
void tar_convert_file(const string &name,string &text){/*读取要压缩的文件并转换为16进制*/
    ifstream fp(name);
    if(!fp){//当没有该文件时,直接退出
        exit(-1);
    }
    for(int i=0;i<name.size();++i){//文件名转16进制
        if(name[i]/16<10){
            text+=(char)(name[i]/16+'0');
        }
        else{
            text+=(char)(name[i]/16-10+'A');
        }
        if(name[i]%16<10){
            text+=(char)(name[i]%16+'0');
        }
        else{
            text+=(char)(name[i]%16-10+'A');
        }
    }
    text+="0A";//加一个换行符
    int ch,sum=0;//注意ch用int类型表示,sum用来记录长度
    string temp;
    ch=fp.get();
    while(ch!=EOF){//文件内容转16进制
        if(ch/16<10){
            temp+=(char)(ch/16+'0');
        }
        else{
            temp+=(char)(ch/16-10+'A');
        }
        if(ch%16<10){
            temp+=(char)(ch%16+'0');
        }
        else{
            temp+=(char)(ch%16-10+'A');
        }
        ++sum;
        ch=fp.get();
    }
    string str_sum;
    str_sum=to_string(sum);
    if(str_sum.size()%2){//保证stoi转换出的字符串的长度是偶数
        str_sum="0"+str_sum;
    }
    text+=str_sum;//写入文件大小
    text+="0A";//加一个换行符
    text+=temp;//写入文件内容
    text+="0A";//加一个换行符
    fp.close();
    return;
}
void extract_convert_file(const string &name,string &text){/*读取要解压的文件并转换为16进制*/
    ifstream fp(name);
    if(!fp){//当没有该文件时,直接退出
        exit(-1);
    }
    int ch;
    char hex[8];
    ch=fp.get();
    while(ch!=EOF){//文件内容转16进制
        for(int j=7;j>=0;--j){
            hex[j]='0'+ch%2;
            ch>>=1;
        }
        for(int j=0;j<8;++j){
            text+=hex[j];
        }
        ch=fp.get();
    }
    fp.close();
    return;
}
void binary_to_hex(string &text){/*二进制(哈夫曼编码后的文件内容)转16进制*/
    string temp,hex_string;
    int num;
    for(int i=0;i<text.size();i+=8){
        for(int j=0;j<8;++j){
            temp+=text[i+j];
        }
        num=stoi(temp,nullptr,2);
        temp.erase();
        if(num/16<10){
            hex_string+=(char)(num/16+'0');
        }
        else{
            hex_string+=(char)(num/16-10+'A');
        }
        if(num%16<10){
            hex_string+=(char)(num%16+'0');
        }
        else{
            hex_string+=(char)(num%16-10+'A');
        }
    }
    text.erase();
    text=hex_string;
    return;
}
void write_file(const string &name,string &text){/*将16进制的文件内容写到新的文件中*/
    ofstream fp(name,ios_base::binary|ios_base::out);
    char hex_ch[3];
    hex_ch[2]=0;
    stringstream input(text);
    input.flags(ios_base::hex);
    for(int i=0;i<text.size();i+=2){
        hex_ch[0]=text[i];
        hex_ch[1]=text[i+1];
        long data = strtol(hex_ch, nullptr, 16);
        fp<<static_cast<unsigned char>(data&0xff);
    }
    fp.close();
    return;
}
void spilt_and_extract(string &plaintext){/*将哈夫曼解码后的文件内容(16进制)分离并重新写入*/
    string name,text;
    int check=1,num=0;
    string temp;
    for(int i=0;i<plaintext.size();i+=2){
        if(check==1){/*文件名分离*/
            if(plaintext[i]=='0'&&plaintext[i+1]=='A'){
                check=2;
            }
            else{
                int temp1=0,temp2=0;
                if(plaintext[i]>='0'&&plaintext[i]<='9'){
                    temp1=plaintext[i]-'0';
                }
                else{
                    temp1=plaintext[i]-'A'+10;
                }
                if(plaintext[i+1]>='0'&&plaintext[i+1]<='9'){
                    temp2=plaintext[i+1]-'0';
                }
                else{
                    temp2=plaintext[i+1]-'A'+10;
                }
                name+=(char)(temp1*16+temp2);
            }
        }
        else if(check==2){/*文件大小分离*/
            if(plaintext[i]=='0'&&plaintext[i+1]=='A'){
                check=3;
                num=stoi(temp,nullptr,10);
                temp.erase();
            }
            else{
                temp+=plaintext[i];
                temp+=plaintext[i+1];
            }
        }
        else{/*文件内容分离*/
            int j;
            for(j=i;j<num*2+i;j+=2){
                text+=plaintext[j];
                text+=plaintext[j+1];
            }
            write_file(name,text);/*文件写入*/
            i=j;
            check=1;
            name.erase();
            text.erase();
        }
    }
}

#endif