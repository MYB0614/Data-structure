#include <stdio.h>

void prime(int x, int y) {
	if ((x == 1) || (y == 1))	printf("true\n");
	else if ((x != 1) && (y != 1) && (x == y))	printf("false\n");
	else if ((x != 1) && (y != 1) && (x < y))	return prime(x,y-x);
	else if ((x != 1) && (y != 1) && (x > y))	return prime(x-y, y);
}
int Fibonacci(int n) {
	if (n == 0)	return 0;
	else if (n == 1)	return 1;
	else return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int binary(int n) {
	if (n % 2 == 0) return binary(n / 2);
	else if (n == 1)	return 1;
	else return binary(n / 2) + 1;
}
int main(void) {
	puts("학부: 컴퓨터학부 학번: 2024004937 이름: 민영범\n문제 1:");
	int x, y, n1,n2;
	scanf_s("%d %d", &x, &y);
	prime(x, y);
	printf("문제 2:\n");
	scanf_s("%d", &n1);
	printf("%d\n",Fibonacci(n1));
	printf("문제 3:\n");
	scanf_s("%d", &n2);
	printf("%d", binary(n2));

	return 0;
}