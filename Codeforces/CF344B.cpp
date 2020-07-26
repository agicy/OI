#include <cstdio>

int a, b, c;

int main(void)
{
	register int i;
	scanf("%d%d%d", &a, &b, &c);
	for (i = 0; i <= a && i <= b; ++i)
		if (a + b - (i << 1) == c)
			return printf("%d %d %d\n", i, b - i, a - i), 0;
	puts("Impossible");
	return 0;
}