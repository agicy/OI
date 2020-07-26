#include <cstdio>

int n, a, b;

int main(void){
	scanf("%d%d%d", &n, &a, &b);
	if(a+b>n)
		printf("%d\n", a + b - n);
	else
		puts("0");
	return 0;
}