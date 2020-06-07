#ifndef File_operation_h
#define File_operation_h

#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<sstream>
#include<ios>
using namespace std;
void tar_convert_file(const string &name,string &text);
void extract_convert_file(const string &name,string &text);
void spilt_and_extract(string &plaintext);
void binary_to_hex(string &text);
void write_file(const string &name,string &text);

#endif