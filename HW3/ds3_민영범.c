#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int seqsearch(int L[], int i, int L_size) {
	for (int j = 0; j < L_size; j++) {
		if (L[j] == i) {
			return j;
		}
	}
	return -1;
}
int iterative(int L[],int i,int L_size) {
	int mid, left = 0, right = L_size - 1;
	while (left <= right) {
		mid = (right + left) / 2;
		if (L[mid] < i) {
			left = mid + 1;
		}
		else if (L[mid] == i) {
			return mid;
		}
		else if (L[mid] > i) {
			right = mid - 1;
		}
	}
	return -1;
}

int recursive(int L[], int i,int left ,int right) {
	int mid;
	if (left <= right) {
		mid = (right + left) / 2;
		if (L[mid] < i) {
			return recursive(L, i, mid + 1, right);
		}
		else if (L[mid] == i) {
			return mid;
		}
		else if (L[mid] > i) {
			return recursive(L, i, left, mid - 1);
		}
	}
	return -1;
}


int main(void) {
	printf("컴퓨터학부 2024004937 민영범\n");

	FILE* fp = fopen("in.txt", "r");

	if (fp == NULL) {
		printf("Error1\n");
		return -1;
	}

	int cnt = 0;
	int num;
	while (1) {
		int result = fscanf_s(fp, "%d", &num);
		if (result == 1) {
			cnt++;
		}
		else {
			if (feof(fp)) {
				break;
			}
			else {
				puts("Error2");
				fclose(fp);
				return -1;
			}
		}
	}

	fseek(fp, 0, SEEK_SET);
	int L_size = cnt;
	int* L = (int*)malloc(sizeof(int) * cnt);
	int freq = 100000;
	for (int i = 0; i < L_size;i++){
		fscanf_s(fp, "%d", &L[i]);
	}

	printf("sequential search:\n");
	time_t start = clock();
	for (int i = 0; i < freq; i++) {
		int res = seqsearch(L, i, L_size);
		if (i < 5) printf("search %d result: %d\n", i, res);
	}
	time_t end = clock();
	printf("computation time: %fms\n\n", 1000 * ((double)end - (double)start) / CLOCKS_PER_SEC);

	printf("iterative binary search:\n");
	start = clock();
	for (int i = 0; i < freq; i++) {
		int res = iterative(L, i, L_size);
		if (i < 5) printf("search %d result: %d\n", i, res);
	}
	end = clock();
	printf("computation time: %fms\n\n", 1000 * ((double)end - (double)start) / CLOCKS_PER_SEC);

	int left = 0;
	int right = L_size - 1;
	printf("recursive binary search:\n");
	start = clock();
	for (int i = 0; i < freq; i++) {
		int res = recursive(L, i,left, right);
		if (i < 5) printf("search %d result: %d\n", i,res);
	}
	end = clock();
	printf("computation time: %fms\n\n", 1000 * ((double)end - (double)start) / CLOCKS_PER_SEC);
	
	return 0;

}