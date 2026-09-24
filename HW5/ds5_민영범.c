#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define MAX_COL 100
typedef struct 
{
	int row;
	int col;
	int value;
} term;

term a[MAX_TERMS];

void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL];	//a 기준 한 열에 몇 행이 있는지 
	int startingPos[MAX_COL];	//b 기준 시작 위치 (계산법 : stratingPos[i] = startingPos[i-1] + rowTerms[i-1])
	int numTerms = a[0].value;
	int i, j, numCols = a[0].col;
	/*
	numTerms => nomzero 갯수
	numCols => a 기준 col 갯수 
	*/
	b[0].row = a[0].col;
	b[0].col = a[0].row;
	b[0].value = a[0].value;
	if (numTerms > 0) {	//nonzero matrix일때
		for (i = 0; i < numCols; i++) {	//rowTerms 초기화
			rowTerms[i] = 0;
		}
		for (i = 1; i <= numTerms; i++) {	//rowTerms에 각각 입력
			rowTerms[a[i].col]++;
		}
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
	numTerms = b[0].value;
	printf("fastTranspose 실행 결과:\n");
	for (i = 0; i <= numTerms; i++) {
		printf("%d %d %d\n",b[i].row,b[i].col,b[i].value);
	}
	// 단계4) out.txt 넣기
	FILE* fp = fopen("out.txt", "w");
	int m = b[0].row, n = b[0].col;
	fprintf(fp, "학부 : 컴퓨터학부 학번 : 2024004937 이름 : 민영범\n");
	fprintf(fp, "%d %d\n", m, n);
	int** M = (int**)calloc(m, sizeof(int*));
	for (int i = 0; i < m; i++) {
		M[i] = (int*)calloc(n, sizeof(int));
	}

	for (i = 1; i <= numTerms; i++) {
		M[b[i].row][b[i].col] = b[i].value;
	}
	for (int i = 0; i < m;i++) {
		for (int j = 0; j < n; j++) {
			if (j == (n - 1))	fprintf(fp, "%d", M[i][j]);
			else fprintf(fp, "%d ", M[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	for (int i = 0; i < m; i++) {
		free(M[i]);
	}
	free(M);

}

int main(void) {
	printf("학부 : 컴퓨터학부 학번 : 2024004937 이름 : 민영범\n");
	//단계1) 원소값 저장
	FILE* fp = fopen("in.txt", "r");
	int m, n;
	fscanf_s(fp, "%d %d", &m, &n);	
	int** M = (int**)malloc(sizeof(int*) * m);
	
	for (int i = 0; i < m; i++) {
		M[i] = (int*)malloc(sizeof(int) * n);
	}
	
	for (int i = 0; i < m;i++) {
		for (int j = 0; j < n; j++) {
			fscanf_s(fp, "%1d", &M[i][j]);
		}
	}
	fclose(fp);
	//단계2) row-major order방식의 sparse matrix 3-tuple 형식으로 저장
	a[0].row = m;
	a[0].col = n;
	int step = 1;	//a는 1부터 입력하니
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (M[i][j]) {
				a[step].row = i;
				a[step].col = j;
				a[step].value = M[i][j];
				step++;
			}
		}
	}
	a[0].value = step-1;
	for (int i = 0; i < step; i++) {
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	}
	for (int i = 0; i < m; i++) {
		free(M[i]);
	}
	free(M);
	//단계3) fastTranspose 수행결과를 3-tuple로 출력
	term b[MAX_TERMS];
	fastTranspose(a, b);
	
	
	
	return 0;
}
