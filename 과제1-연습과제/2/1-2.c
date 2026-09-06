#include <stdio.h>
#include <stdlib.h>

#ifndef _MSC_VER
#define fopen_s(pFile, filename, mode) ((*(pFile) = fopen((filename), (mode))) != NULL ? 0 : 1)
#define fscanf_s fscanf
#endif

int main(void){
    int n, min;
    FILE *fp;
    fopen_s(&fp,"in.txt","rt");
    // 단계 1 
    puts("컴퓨터학부 2024004937 민영범");
    // 단계 2
    fscanf_s(fp,"%d",&n);
    // 단계 3
    printf("단계 3: %d\n",n);
    // 단계 4
    int *L = (int *)malloc(sizeof(int)*n);
    // 단계 5
    for(int i = 0; i < n; i++){
        fscanf_s(fp,"%d",&L[i]);
    }
    // 단계 6 & 7
    min = L[0];
    printf("단계 6: ");
    for(int i = 0; i < n; i++){
        if(i == n-1){
            printf("%d\n",L[i]);    
        }
        else    printf("%d ",L[i]);
        if((i>0)&&(L[i]<min))   min = L[i];
    }
    printf("단계 7: %d\n",min);



    // 단계 8
    int min1 = L[0];
    int min2;
    int has_min2 = 0;
    for(int i = 1; i < n; i++){
        int x = L[i];
        if(x < min1){
            min2 = min1;
            min1 = x;
            has_min2 = 1;
        }
        else if(x > min1){    
            if(!has_min2||x < min2){
                min2 = x;
                has_min2 = 1;
            }
        }
    }
    printf("단계 8: %d\n",min2);

    // 단계 9
    printf("단계 9: ");
    int scnt = 0;
    for(int i = 0; i < n-1; i++){
        int Back = 0;
        int front = 0;
        for(int j = i+1; j < n; j++){
            if(L[i] == L[j]){
                Back = 1;
                break;
            }
        }
        if(Back){   // 뒤에 중복이 있는경우
            for(int k = 0; k < i; k++){ // 앞 중복 검사
                if(L[k] == L[i]){
                    front = 1;
                    break;
                }
            }
            if(!front){  
                printf("%d ",L[i]);
                scnt++;
            }
        }
    }
    if(scnt == 0)   printf("중복없음\n");
    else    printf("\n");


    return 0;
}