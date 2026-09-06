#include <stdio.h>

#ifndef _MSC_VER
#define fopen_s(pFile, filename, mode) ((*(pFile) = fopen((filename), (mode))) != NULL ? 0 : 1)
#define fscanf_s fscanf
#endif

int main(void){
    FILE *fp;
    fopen_s(&fp,"in.txt","rt");
    int sz = 0;
    int val,max,min;

    puts("컴퓨터학부 2024004937 민영범");
    
    if(fscanf_s(fp,"%d",&val) != EOF){
        max = val;
        min = val;
        sz += 1;
    }
    
    

    while (1)
    {   
        if(fscanf_s(fp,"%d",&val) != EOF){
            if(val<min) min = val;
            if(val>max) max = val;
            sz++;
        }
        else{
            if(feof(fp))    break;
        }
    }
    printf("원소의 개수: %d\n",sz);
    printf("최소값: %d\n",min);
    printf("최대값: %d\n",max);
    
    fclose(fp);

    return 0;
}