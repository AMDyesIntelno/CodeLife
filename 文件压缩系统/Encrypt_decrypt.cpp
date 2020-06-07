#ifndef Encrypt_decrypt_cpp
#define Encrypt_decrypt_cpp

#include "Encrypt_decrypt.h"
void encrypt(string &key,string &plaintext,string &ciphertext){/*异或加密*/
    string temp;
    temp=key;
    key.erase();
    char hex[8];
    for(int i=0;i<temp.size();++i){/*将key转换为二进制*/
        for(int j=7;j>=0;--j){
            hex[j]='0'+temp[i]%2;
            temp[i]>>=1;
        }
        for(int j=0;j<8;++j){
            key+=hex[j];
        }
    }
    for(int i=0,j=0;i<plaintext.size();++i){/*加密*/
        ciphertext+=(char)((key[j]-'0')^(plaintext[i]-'0')+48);
        ++j;
        if(j==key.size()){
            j=0;
        }
    }
    return;
}
void decrypt(string &key,string &plaintext,string &ciphertext){/*异或解密*/
    string temp;
    temp=key;
    key.erase();
    char hex[8];
    for(int i=0;i<temp.size();++i){/*将key转换为二进制*/
        for(int j=7;j>=0;--j){
            hex[j]='0'+temp[i]%2;
            temp[i]>>=1;
        }
        for(int j=0;j<8;++j){
            key+=hex[j];
        }
    }
    for(int i=0,j=0;i<ciphertext.size();++i){/*解密*/
        plaintext+=(char)((ciphertext[i]-'0')^(key[j]-'0')+48);
        ++j;
        if(j==key.size()){
            j=0;
        }
    }
    return;
}

#endif