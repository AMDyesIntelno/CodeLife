```c++
void Binary_Search_Insert(SST &table,int num){
    int start=1;
    int end=table->length;
    int mid=(start+end)/2;
    if(table->data[start]<=table->data[end]){
        while(start<end){
            if(table->data[mid]>num){
                end=mid;
            }
            else{
                start=mid;
            }
            if(table->data[end]>=num&&table->data[start]<=num&&end-start==1){
                break;
            }
            mid=(start+end)/2;
        }
        int *temp=(int *)realloc(table->data,(2+table->length)*sizeof(int));
        table->data=temp;
        if(end!=start){
            for(int i=table->length;i>=end;--i){
                table->data[i+1]=table->data[i];
            }
            table->data[end]=num;
            ++table->length;
        }
        else{
            if(table->data[start]>num){
                for(int i=table->length;i>=1;++i){
                    table->data[i+1]=table->data[i];
                }
                table->data[1]=num;
                ++table->length;
                return;
            }
            if(table->data[end]<num){
                ++table->length;
                table->data[table->length]=num;
                return;
            }
        }
    }
    else{
        while(start<end){
            if(table->data[mid]<num){
                end=mid;
            }
            else{
                start=mid;
            }
            if(table->data[end]<=num&&table->data[start]>=num&&end-start==1){
                break;
            }
            mid=(start+end)/2;
        }
        int *temp=(int *)realloc(table->data,(2+table->length)*sizeof(int));
        table->data=temp;
        if(end!=start){
            for(int i=table->length;i>=end;--i){
                table->data[i+1]=table->data[i];
            }
            table->data[end]=num;
            ++table->length;
        }
        else{
            if(table->data[start]<num){
                for(int i=table->length;i>=1;++i){
                    table->data[i+1]=table->data[i];
                }
                table->data[1]=num;
                ++table->length;
                return;
            }
            if(table->data[end]>num){
                ++table->length;
                table->data[table->length]=num;
                return;
            }
        }
    }
    return;
}
```
