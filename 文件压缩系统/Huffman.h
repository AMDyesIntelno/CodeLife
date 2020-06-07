#ifndef Huffman_h
#define Huffman_h

#include<iostream>
#include<string>
#include<fstream>
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
void get_weight(string text,int *weight,string &plaintext);
void min_2(H_Tree HT,int _size,int &posi1,int &posi2);
void Create_Huffman_Tree(H_Tree &HT,int *weight);
void Create_Huffman_Code(H_Tree HT,H_Code &HC);
void encode(string &plaintext,string text,H_Code HC);
void decode(string &plaintext,H_Tree HT,int sum);
int recover(int *weight,string &plaintext);

#endif