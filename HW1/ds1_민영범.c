#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n;
    FILE* fp;
    fopen_s(&fp, "in.txt", "rt");
    if (fp == NULL) {
        printf("Error");
        return -1;
    }

    printf("컴퓨터학부 2024004937 민영범\n");
    fscanf_s(fp, "%d", &n, sizeof(n));
    printf("n: %d\n", n);

    int* L = (int*)malloc(sizeof(int) * n);
    if (L == NULL) {
        printf("����");
        fclose(fp);
        return -1;
    }

    int val;
    int i = 0;
    while (i < n && fscanf_s(fp, "%d", &val) != EOF) {
        if (val > 0) {
            L[i] = val;
            i++;
        }
    }
    int max = L[0], min = L[0];
    for (int j = 0; j < n; j++) {
        
        if (L[j] > max) {
            max = L[j];
        }
        if (L[j] < min) {
            min = L[j];
        }
    }
    fclose(fp);
    printf("�ּҰ�: %d\n�ִ밪: %d\n", min, max);
    int x;
    
    while (1) {
        fscanf_s(stdin, "%d", &x);                    
        if (x > 0) {
            break;
        }
    }
    FILE* fp1;
    fopen_s(&fp1, "out.txt", "wt");
    if (fp1 == NULL) {
        printf("Error");
        return -1;
    }
    printf("%d�� ���: ",x);
    fprintf(fp1, "%d�� ���: ",x);
    for (int j = 0; j < n; j++) {
        if ((L[j] % x) == 0) {
            printf("%d ", L[j]);
            fprintf(fp1, "%d ",L[j]);
        }
    }
    


    

    free(L);
    return 0;
}
