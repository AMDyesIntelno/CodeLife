#include "Encrypt_decrypt.cpp"
#include "Huffman.cpp"
#include "File_operation.cpp"
int main(int argc,char *argv[]){
    string name,text,key,plaintext,ciphertext;
    int sum;
    int weight[16]={0};
    H_Tree HT=NULL;
    H_Code HC=NULL;
    if(strcmp(argv[1],"-h")==0){//help
        cout<<"tar: ./xxxx -t file1 file2 file3 [-p password] -o file_out"<<endl;
        cout<<"extract: ./xxxx -e file [-p password]"<<endl;
    }
    else if(strcmp(argv[1],"-t")==0){//压缩
        int i=2;
        while(i<argc&&strcmp(argv[i],"-p")!=0&&strcmp(argv[i],"-o")!=0){
            name=argv[i];
            tar_convert_file(name,text);
            ++i;
        }
        if(i<argc&&strcmp(argv[i],"-p")==0){
            key=argv[i+1];
            i+=2;
        }
        if(i<argc&&strcmp(argv[i],"-o")==0){
            name=argv[i+1];
        }
        get_weight(text,weight,plaintext);
        Create_Huffman_Tree(HT,weight);
        Create_Huffman_Code(HT,HC);
        encode(plaintext,text,HC);
        if(key.size()>0){
            encrypt(key,plaintext,ciphertext);
        }
        else{
            ciphertext.erase();
            ciphertext=plaintext;
        }
        binary_to_hex(ciphertext);
        write_file(name,ciphertext);
    }
    else if(strcmp(argv[1],"-e")==0){//解压
        name=argv[2];
        if(argc>3){
            if(strcmp(argv[3],"-p")==0){
                if(argc>4){
                    key=argv[4];
                }
            }
        }
        if(key.size()>0){
            extract_convert_file(name,ciphertext);
            decrypt(key,plaintext,ciphertext);
        }
        else{
            extract_convert_file(name,plaintext);
        }
        sum=recover(weight,plaintext);
        Create_Huffman_Tree(HT,weight);
        decode(plaintext,HT,sum);
        spilt_and_extract(plaintext);
    }
    delete HT;
    HT=NULL;
    delete HC;
    HC=NULL;
    return 0;
}