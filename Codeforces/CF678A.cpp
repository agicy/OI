#include <cstdio>

int n, k;

int main(void)
{
	scanf("%d%d", &n, &k);
	printf("%d\n", n + k - n % k);
	return 0;
}