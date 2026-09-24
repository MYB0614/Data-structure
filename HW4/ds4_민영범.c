#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

typedef struct {
    float coef;  // 계수
    int expon;   // 지수
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

int COMPARE(int a, int b) {
    if (a > b) return 1;
    else if (a == b) return 0;
    else return -1;
}

void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
    float coefficient;
    *startD = avail;
    while (startA <= finishA && startB <= finishB) {
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
        case -1:
            attach(terms[startB].coef, terms[startB].expon);
            startB++;
            break;
        case 0:
            coefficient = terms[startA].coef + terms[startB].coef;
            if (coefficient) attach(coefficient, terms[startA].expon);
            startA++;
            startB++;
            break;
        case 1:
            attach(terms[startA].coef, terms[startA].expon);
            startA++;
            break;
        }
    }
    for (; startA <= finishA; startA++) {
        attach(terms[startA].coef, terms[startA].expon);
    }
    for (; startB <= finishB; startB++) {
        attach(terms[startB].coef, terms[startB].expon);
    }
    *finishD = avail - 1;
}

int main() {
    int startA, finishA;
    int startB, finishB;
    int startD, finishD;

    // 1. a.txt 읽기
    FILE* fp_a = NULL;
    fopen_s(&fp_a, "a.txt", "r");
    if (fp_a == NULL) {
        printf("a.txt 파일을 읽을 수 없음\n");
        return 1;
    }
    int numA;
    fscanf_s(fp_a, "%d", &numA);
    startA = avail;
    for (int i = 0; i < numA; i++) {
        float c;
        int e;
        fscanf_s(fp_a, "%f %d", &c, &e);
        attach(c, e);
    }
    finishA = avail - 1;
    fclose(fp_a);

    // 2. b.txt 읽기
    FILE* fp_b = NULL;
    fopen_s(&fp_b, "b.txt", "r"); 
    if (fp_b == NULL) {
        printf("b.txt 파일을 읽을 수 없음\n");
        return 1;
    }
    int numB;
    fscanf_s(fp_b, "%d", &numB); 
    startB = avail;
    for (int i = 0; i < numB; i++) {
        float c;
        int e;
        fscanf_s(fp_b, "%f %d", &c, &e); 
        attach(c, e);
    }
    finishB = avail - 1;
    fclose(fp_b);

    // 3. 다항식 연산
    padd(startA, finishA, startB, finishB, &startD, &finishD);

    // 4. c.txt 저장
    FILE* fp_c = NULL;
    fopen_s(&fp_c, "c.txt", "w"); 
    if (fp_c == NULL) {
        printf("c.txt 파일을 생성/열 수 없음\n");
        return 1;
    }
    fprintf(fp_c, "학부: 컴퓨터학부, 학번: 2024004937 이름: 민영범\n"); 

    int numC = (startD <= finishD) ? (finishD - startD + 1) : 0;
    fprintf(fp_c, "%d\n", numC);

    for (int i = startD; i <= finishD; i++) {
        fprintf_s(fp_c, "%.0f %d", terms[i].coef, terms[i].expon);
        if (i < finishD) fprintf(fp_c, " ");
    }
    fprintf(fp_c, "\n");

    fclose(fp_c);
    return 0;
}